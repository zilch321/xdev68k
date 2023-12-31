
#include <interrupt.h>
#include <stdlib.h>
#include <iocslib.h>

/* �p�^�[����`�̃w�b�_ */
#include "sp_test.h"

/* ���ۂ̃X�v���C�g���͂��̒l�̂U�{ */
#define MAX_SP 20

/* �X�v���C�g�Ԃ̃h�b�g�� */
#define STEP   3

/* �@��A�R���p�C���Ɋ��S�Ɉˑ�����L�q */
/* PCG ���W�X�^�̍\���� */
typedef  union  {
    unsigned short dummy;
    struct {
      unsigned pos0: 4;
      unsigned pos1: 4;
      unsigned pos2: 4;
      unsigned pos3: 4;
    } sp;
} SP_REG_U;

/* �X�v���C�g�X�N���[�����W�X�^�\���� */
typedef struct {
  short int sp_x;
  short int sp_y;
  union {
    short int dummy;
    struct {
      unsigned v_invert : 1;
      unsigned h_invert : 1;
      unsigned dummy    : 2;
      unsigned color    : 4;
      unsigned sp_code  : 8;
    } sp;
  } sp_ctrl;
  union {
    short int dummy;
    struct {
      unsigned dummy   : 13;
      unsigned ext     :  1;
      unsigned pwr     :  2;
    } sp;
  } sp_pwr;
} SP_CTRL;

/* �X�v���C�g�������z�� */
static SP_CTRL sp_disp[128];
static short int this_sp_is_active[128];
static short int life_of_this_sp[128];

/* ����ړ��p�^�[���̃e�[�u�� */
static short *move_tbl_x;
static short *move_tbl_y;

static void
make_move_tbl (void)
{
  extern double sin (double);
  int i;
  move_tbl_x = (short *) malloc (sizeof (short) * (256 + 33));
  move_tbl_y = (short *) malloc (sizeof (short) * (256 + 33));
  for (i = -16; i < 256 + 16; i++)
    {
      move_tbl_x[i] = i;
      move_tbl_y[i] = 128 +
	(int)(100.0 * sin (3.1415 * (((double) i)/64.0))); 
    }
}

/* �X�v���C�g�p�^�[���̒�` */
static void
def_sp (int pat_no, unsigned char *sp_dat)
{
   SP_REG_U *sp_reg0 = (SP_REG_U *) 0xeb8000 + (128/sizeof (SP_REG_U)) * pat_no;
   SP_REG_U *sp_reg1 = (SP_REG_U *) 0xeb8040 + (128/sizeof (SP_REG_U)) * pat_no;
   int i;
   /* SP �X�N���[�����W�X�^��CPU�ɊJ�� */
   *(short *)0xeb0808 &= 0xfdfc;
   for (i = 0; i < 16; i++)
     {
     	SP_REG_U tem;
     	tem.sp.pos0 = *sp_dat ++;
     	tem.sp.pos1 = *sp_dat ++;
     	tem.sp.pos2 = *sp_dat ++;
     	tem.sp.pos3 = *sp_dat ++;
     	*sp_reg0 ++ = tem;
     	tem.sp.pos0 = *sp_dat ++;
     	tem.sp.pos1 = *sp_dat ++;
     	tem.sp.pos2 = *sp_dat ++;
     	tem.sp.pos3 = *sp_dat ++;
     	*sp_reg0 ++ = tem;

     	tem.sp.pos0 = *sp_dat ++;
     	tem.sp.pos1 = *sp_dat ++;
     	tem.sp.pos2 = *sp_dat ++;
     	tem.sp.pos3 = *sp_dat ++;
     	*sp_reg1 ++ = tem;
     	tem.sp.pos0 = *sp_dat ++;
     	tem.sp.pos1 = *sp_dat ++;
     	tem.sp.pos2 = *sp_dat ++;
     	tem.sp.pos3 = *sp_dat ++;
     	*sp_reg1 ++ = tem;
     }
  /* SP �\�� */
  *(short *)0xeb0808 |= 0x0200;
}


/* inline �A�Z���u���T���v���ɂȂ�܂� */

static void
init_screen (void)
{
  {
    /* screen , 256*256 256 color,high freq */
    register int trapNo asm ("d0");
    register int mode   asm ("d1");
    trapNo = 0x10;
    mode   = 10;
    asm ("trap #15":: "d"(trapNo),"d"(mode):"d0");
  }

  {
    /* �J�[�\�� off */
    register int trapNo asm ("d0");
    trapNo = 0x1f;
    asm ("trap #15":: "d"(trapNo):"d0");
  }

  {
    /* �X�v���C�g�ʏ����� */
    register int trapNo asm ("d0");
    trapNo = 0xc0;
    asm ("trap #15":: "d"(trapNo):"d0");
  }

  {
    /* PCG �N���A */
    register int trapNo asm ("d0");
    register int pcg asm ("d1");
    for (pcg = 0; pcg < 256; pcg ++)
      {
	trapNo = 0xc3;
	asm ("trap #15"::"d"(trapNo), "d"(pcg): "d0");
      }
  }

  {
    /* �X�v���C�g�p���b�g�ݒ� */
    register int trapNo    asm ("d0");
    register int pal_code  asm ("d1");
    register int block     asm ("d2");
    register int col_code  asm ("d3");
    int i;
    for (i = 0; i < 16; i++)
      {
	trapNo = 0xcf;
	pal_code = 0x80000000 | i;
	block = 1;
	col_code = sp_pal[i];
	asm ("trap #15"::"d"(trapNo),"d"(pal_code),"d"(block), "d"(col_code));
      }
  }

  {
    /* �X�v���C�g�\�� on */
    register int trapNo asm ("d0");
    trapNo = 0xc1;
    asm ("trap #15":: "d"(trapNo):"d0");
  }
  /* PCG ��` */
  def_sp (0, pat_X);
  def_sp (1, pat_6);
  def_sp (2, pat_8);
  def_sp (3, pat_0);
  def_sp (4, pat_C);
}

static volatile int vsync_counter;
static volatile int sp_is_ready;

static void
sp_display ()
{
   /* MPF ���W�X�^�A�h���X */
   char volatile *mpf = (char *)0xe88001;

   /* �����A�����ԂȂ�\�����Ԃ�҂� */
   while (!((*mpf) & 0x10))
     ;
   /* �����A�����Ԃ�҂� */
   while ((*mpf) & 0x10)
     ;
  if (sp_is_ready)
    {
      int i;
      SP_CTRL *sp_scr_reg = (SP_CTRL *)0xeb0000;
      /* SP �X�N���[�����W�X�^��CPU�ɊJ�� */
      *(short *)0xeb0808 &= 0xfdfc;
      /* �X�v���C�g�X�N���[�����W�X�^�������� */
      for (i = 0; i < 128; i++)
	if (this_sp_is_active[i])
	    *sp_scr_reg ++ = sp_disp[i];
      /* SP �\�� */
      *(short *)0xeb0808 |= 0x0200;
      vsync_counter++;
      sp_is_ready = 0;
    }
}

void
main()
{
  B_SUPER (0);
  make_move_tbl ();
  init_screen ();
  vsync_counter = 0;
  sp_is_ready = 0;

  {
    int i;
    for (i = 0; i < 6*MAX_SP; i++)
      {
	life_of_this_sp[i] = - STEP * (i + 1);
	sp_disp[i].sp_ctrl.sp.color = 1;
	sp_disp[i].sp_pwr.sp.pwr = 3;
      }
  }

  {
    int i;
    for (i = 0; i < 6*MAX_SP; i += 6)
      {
        sp_disp[0 + i].sp_ctrl.sp.sp_code = 3; /* '0' */
        sp_disp[1 + i].sp_ctrl.sp.sp_code = 3; /* '0' */
	sp_disp[2 + i].sp_ctrl.sp.sp_code = 3; /* '0' */
	sp_disp[3 + i].sp_ctrl.sp.sp_code = 2; /* '8' */
	sp_disp[4 + i].sp_ctrl.sp.sp_code = 1; /* '6' */
	sp_disp[5 + i].sp_ctrl.sp.sp_code = 0; /* 'X' */
      }
  }

  while (1)
    {
      if (!sp_is_ready)
	{
	  int i;
	  for (i = 0; i < 6*MAX_SP; i++)
	    {
	      life_of_this_sp [i] ++;
	      if (life_of_this_sp[i] >= 256 + 16)
		life_of_this_sp[i] = -16;
	      if (life_of_this_sp[i] >= -16)
		{
		  sp_disp[i].sp_x = move_tbl_x[life_of_this_sp[i]];
		  sp_disp[i].sp_y = move_tbl_y[life_of_this_sp[i]];
		  this_sp_is_active[i] = 1;
		}
	    }
	  sp_is_ready = 1;
	}
      sp_display ();
      while (BITSNS (0xe) & 1)
	;
      if (BITSNS (0) & 2)
        break;
    }

  {
    /* screen 0,0 */
    register int trapNo asm ("d0");
    register int mode   asm ("d1");
    trapNo = 0x10;
    mode   = 16;
    asm ("trap #15":: "d"(trapNo),"d"(mode):"d0");
  }

  {
    /* �J�[�\�� on */
    register int trapNo asm ("d0");
    trapNo = 0x1e;
    asm ("trap #15":: "d"(trapNo):"d0");
  }
  exit (0);
}
