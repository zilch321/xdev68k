#include <stdio.h>
#include <iocslib.h>
#include <interrupt.h>

#ifndef SCR_UNIT
#define SCR_UNIT 1
#endif

/* �X�N���[���}�b�v�f�[�^ */
static char *map_data[] = {
  "                ",
  "                ",
  "                ",
  "                ",
  "                ",
  "                ",
  "                ",
  "                ",
  "                ",
  "                ",
  "                ",
  "                ",
  "                ",
  "                ",
  "                ",
  "                "
  "                ",
  "                ",
  "      08888881  ",
  "      67    67  ",
  "      67    67  ",
  "      67    67  ",
  "      67    67  ",
  "      67    67  ",
  "      67    67  ",
  "      67    67  ",
  "      23    23  ",
  "                ",
  "  041           ",
  "  687  01  01   ",
  "  687  23  23   ",
  "  687           ",
  "  687    01     ",
  "  687    23     ",
  "  687           ",
  "  687           ",
  "  687  01   01  ",
  "  687  23   67  ",
  "  687       67  ",
  "  687       67  ",
  "  6884441   67  ",
  "  2555553   67  ",
  "            67  ",
  "       041  67  ",
  "       687  67  ",
  "       687  67  ",
  "       687  67  ",
  "       687  67  ",
  "       687  67  ",
  "       687  67  ",
  "       687  23  ",
  "       687      ",
  "  01   687  01  ",
  "  67   687  23  ",
  "  67   687      ",
  "  67   687  01  ",
  "  67   687  23  ",
  "  67   687      ",
  "  67   687      ",
  "  67   687      ",
  "  67   687      ",
  "  67   6884441  ",
  "  67   2555553  ",
  "  67            ",
  "  67   044441   ",
  "  23   688887   ",
  "      0888883   ",
  "     0888883    ",
  "    0888883     ",
  "   0888883      ",
  "   688883       ",
  "   25553        ",
  "                ",
  "  01        01  ",
  "  23   01   23  ",
  "       23       ",
  "  01        01  ",
  "  23   01   23  ",
  "       23       ",
  "  01        01  ",
  "  23   01   23  ",
  "       23       ",
  "  01        01  ",
  "  23        23  ",
  "                ",
  "                ",
  "   01  01  01   ",
  "   67  67  67   ",
  "   67  67  67   ",
  "   67  67  67   ",
  "   67  67  67   ",
  "   67  67  67   ",
  "   67  67  67   ",
  "   67  67  67   ",
  "   67  67  67   ",
  "   67  67  67   ",
  "   67  67  67   ",
  "   23  23  23   ",
  "                ",
  "   04444441     ",
  "   68888887  01 ",
  "   68888887  23 ",
  "   68888887     ",
  "   68888887  01 ",
  "   25555553  23 ",
  "                ",
  "      08888881  ",
  "      67    67  ",
  "      67    67  ",
  "      67    67  ",
  "      67    67  ",
  "      67    67  ",
  "      67    67  ",
  "      67    67  ",
  "      23    23  ",
  "                ",
  "          01    ",
  "          67    ",
  "          67    ",
  "          67    ",
  "          67    ",
  "          67    ",
  "  04441   67    ",
  "  68887   67    ",
  "  68887   67    ",
  "  68887   67    ",
  "  68887   67    ",
  "  68887   67    ",
  "  68887   67    ",
  "  68887   67    ",
  "  68887   67    ",
  "  68887   67    ",
  "  68887   23    ",
  "  25553         ",
  "                ",
  "                ",
  "      08888881  ",
  "      67    67  ",
  "      67    67  ",
  "      67    67  ",
  "      67    67  ",
  "      67    67  ",
  "      67    67  ",
  "      67    67  ",
  "      23    23  ",
  "                ",
  "          01    ",
  "  01      23    ",
  "  23   01       ",
  "       23       ",
  "  01        01  ",
  "  23        23  ",
  "        01      ",
  "        23      ",
  " 01             ",
  " 23       01    ",
  "          23    ",
  "                ",
  "*"
  };

/* �O���t�B�b�N�f�[�^���[�h�o�b�t�@ */
struct {
  int pal[256];
  unsigned char g_data[11][256];
} gdata;

/* ���݂̏������݃f�[�^�Ǘ��p�J�E���^ */

int map_line;

/* Vram �������݃A�h���X */

unsigned short *vram = (unsigned short *) (0xc80000 - 0x400*16);

/* 16*16 ��`���w�肳�ꂽ Vram �A�h���X�ɏ������� */

static void write_vram (unsigned short *vr, unsigned char *dat)
{
  int i;
  for (i = 0; i < 16; i++)
    {
      unsigned short *p = vr;
      *p++ = *dat++;
      *p++ = *dat++;
      *p++ = *dat++;
      *p++ = *dat++;
      *p++ = *dat++;
      *p++ = *dat++;
      *p++ = *dat++;
      *p++ = *dat++;
      *p++ = *dat++;
      *p++ = *dat++;
      *p++ = *dat++;
      *p++ = *dat++;
      *p++ = *dat++;
      *p++ = *dat++;
      *p++ = *dat++;
      *p++ = *dat++;
      vr += 0x200;
    }
}

/* �w���` vram ���N���A */

static void clr_vram (unsigned short *vr)
{
  int i;
  for (i = 0; i < 16; i++)
    {
      unsigned short *p = vr;
      *p++ = 0;
      *p++ = 0;
      *p++ = 0;
      *p++ = 0;
      *p++ = 0;
      *p++ = 0;
      *p++ = 0;
      *p++ = 0;
      *p++ = 0;
      *p++ = 0;
      *p++ = 0;
      *p++ = 0;
      *p++ = 0;
      *p++ = 0;
      *p++ = 0;
      *p++ = 0;
      vr += 0x200;
    }
}

/* �}�b�v�f�[�^�Ɋ�Â��Ăf�q�`�l�Ƀf�[�^���������� */
static
void write_graph (char *dat)
{
  unsigned short *vr = vram;
  while (*dat)
    {
      if (*dat == ' ')
	clr_vram (vr);
      else
	{
	  int i = *dat - '0';
	  write_vram (vr, gdata.g_data[i]);
	}
      dat++;
      vr += 16;
    }
  vram -= 0x200 * 16;
  if (vram < (unsigned short *) 0xc00000)
    vram =  (unsigned short *) (0xc80000 - 0x400*16); 
}

/* �}�b�v�J�E���^������������ */
/* ���ł�screen 2 ���w�i�Ŗ��߂Ă��� */
static
void init_map_line (void)
{
  int i,j;
  unsigned short *vr = (unsigned short *) 0xc80000;
  for (i = 0; map_data[i][0] != '*'; i++)
    ;
  map_line = i - 1;
  for (i = 0; i < 16; i++)
    {
      unsigned short *var = vr;
      for (j = 0; j< 16; j++)
	{
	  write_vram (var, gdata.g_data[9]);
	  var += 16;
	}
      vr += 0x200 * 16;
    }
}

/* �p���b�g��ݒ肷�� */
static void
init_palet ()
{
  int i;
  int *dat = (int *)&gdata;
  for (i = 0; i < 256; i++)
    GPALET (i, *dat ++);
}

/* �f�[�^�����[�h���ď��������� */
static void
load_data_and_init ()
{
  FILE *fp = fopen ("pattern.dat","rb");
  if (fp == NULL)
    {
      printf ("File can't open\n");
      exit (1);
    }

  if (fread ((void *)&gdata, sizeof (char), sizeof (gdata), fp) != sizeof (gdata))
    {
      printf ("File read error\n");
      fclose (fp);
      exit (1);
    }
  fclose (fp);
  CRTMOD (10);
  G_CLR_ON ();
  B_CUROFF ();
  init_palet ();
  init_map_line ();
}


/* �X�N���[�����W�X�^�Ɠ����̍\���� */

typedef struct {
  short sc0_x_reg;
  short sc0_y_reg;
  short sc1_x_reg;
  short sc1_y_reg;
  short sc2_x_reg;
  short sc2_y_reg;
  short sc3_x_reg;
  short sc3_y_reg;
} CRTC_REG;

/* �X�N���[���p�f�[�^ */
static CRTC_REG scroll_data;

/* �X�N���[���\�t���O */
static volatile int scroll_flag;

/* vsync �J�E���^ */
static volatile int vsync_counter;

/* ���荞�ݏ������[�`�� */
static void
scroll ()
{
  /* �X�N���[�����W�X�^�A�h���X */
  CRTC_REG *crtc = (CRTC_REG *) 0xe80018;

#ifdef HALF
  static int half_flag;
  if (half_flag > 0)
    {
      half_flag -= 1;
      goto ret;
    }
  else
    half_flag = HALF;
#endif

  vsync_counter += 1;
  if (scroll_flag)
    {
      scroll_data.sc0_y_reg -= SCR_UNIT;
      scroll_data.sc1_y_reg -= SCR_UNIT;
      *crtc = scroll_data;
    }

#ifdef HALF
ret:	;
#endif

}

/* main start */
main()
{
  extern void scroll();

  /* �{���� user �ɖ߂��ׂ����� exit ����Ɩ߂�̂�
     �������Ė߂��Ȃ��i�蔲���j */
  B_SUPER (0);

  /* �f�[�^�����[�h */
  load_data_and_init ();
  
  /* �ŏ��̃f�[�^���������݂��ăX�N���[�������� */
  write_graph (map_data[map_line]);
  scroll_flag = 1;

#ifdef OFFSET
  scroll_data.sc0_y_reg -= 64;
  scroll_data.sc1_y_reg -= 64;
#endif
  while (map_line > 0)
    {
      int wait;
      wait = ONTIME();
      if (vsync_counter > (16 - 4)/ SCR_UNIT)
	{
	  if (vsync_counter > (16 - 1)/ SCR_UNIT)
	    scroll_flag = 0;
	  map_line --;
	  write_graph (map_data[map_line]);
	  vsync_counter -= 16/SCR_UNIT;
	  if (!scroll_flag)
	    scroll_flag = 1;
	}
      scroll ();
      while (ONTIME() - wait < 3)
        ;
    }
  B_CURON ();
  exit (0);
}
