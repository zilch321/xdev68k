/* Cmaga X68000 Game by Yohino (C) 1992 03 05 */

#include "game.h"

#ifdef USE_XC_LIB
static struct {
 int flag;                  /* �G���[��ʃt���O */
 unsigned short sr_reg;     /* �G���[���� SR    */
 int pc_reg;                /* �G���[���� PC    */
 char *mes;                 /* ���b�Z�[�W       */
} trapbuf;

static void (*trap_14)();   /* ���� trap 14 �x�N�^��ۑ� */
#endif


volatile void
game_abort (char *mes)
{
  VDISPST (0, 0, 1);
  CRTCRAS (0, 0);
  CRTMOD (16);
  B_CURON ();
  printf ("\n%s\n", mes);
  printf ("  �ُ�I�����܂�\n");
#ifdef USE_XC_LIB
  INTVCS(0x2e,trap_14);
#endif
  longjmp (err_buf, 1);
}

void *
xmalloc (int size)
{
  void *ret = malloc (size);
  if (!ret)
    game_abort ("�������s���ł�");
  return ret;
}

static GAME_PCG *
PCG���[�h (char *fname)
{
  FILE *fp = fopen (fname, "rb");
  char mes[64];
  if (!fp)
    {
      sprintf (mes, "�t�@�C�� %s �����t����܂���",fname);
      game_abort (mes);
    }
  else
    {
      int num = filelength (fileno (fp))/ sizeof (PCG);
      GAME_PCG *retval = xmalloc (sizeof (GAME_PCG));
      PCG **ret = xmalloc (sizeof (PCG *) * num);
      int i;
      retval -> num_p = num -1;   /* Dubug 05 09 from Pekin */
      retval -> pcg_ptr_ptr = ret;
      for (i = 0; i < num; i++)
        ret[i] = xmalloc (sizeof (PCG));
      for (i = 0; i < num; i++)
        {
          int size = fread (ret[i], sizeof (char), sizeof (PCG), fp);
          if (size != sizeof (PCG))
            {
              sprintf (mes, "�t�@�C�� %s ���ُ�ł�", fname);
              game_abort (mes);
            }
        }
      return retval;
    }
}

static void
�_�~�[������ (void)
{
  ���@ = def_sprite (DOT16,
                     &(load_files[C_���@].pcg->pcg_ptr_ptr),
                     load_files[C_���@].pcg->num_p);
  move_sprite_abs (���@, 128, 220);
  select_sprite_pcg (���@, 0);
  select_sprite_color (���@, 1);
  display_sprite (���@, �\��);
  SPD_WORK1 (���@) = 0;
  SPD_REGIST (���@) = 3;

  �~��sp = def_sprite (DOT16,
                       &(load_files[C_�~��].pcg->pcg_ptr_ptr),
                         load_files[C_�~��].pcg->num_p);
  move_sprite_abs (�~��sp, 128, 220 - 10);
  select_sprite_pcg (�~��sp, 0);
  select_sprite_color (�~��sp, 3);
  display_sprite (�~��sp, ��\��);

  �e�_�~�[ = def_sprite_dummy (DOT16,
                               &(load_files[C_�e].pcg->pcg_ptr_ptr),
                               load_files[C_�e].pcg->num_p);
  select_sprite_pcg (�e�_�~�[, 0);

  �^�C�vA = def_sprite_dummy (DOT16,
                              &(load_files[C_�G0].pcg->pcg_ptr_ptr),
                              load_files[C_�G0].pcg->num_p);
  select_sprite_pcg (�^�C�vA, 0);

  �^�C�vB = def_sprite_dummy (DOT16,
                              &(load_files[C_�G1].pcg->pcg_ptr_ptr),
                              load_files[C_�G1].pcg->num_p);
  select_sprite_pcg (�^�C�vB, 0);
  ����0�_�~�[ = def_sprite_dummy (DOT16,
                                  &(load_files[C_����0].pcg->pcg_ptr_ptr),
                                  load_files[C_����0].pcg->num_p);
  select_sprite_pcg (����0�_�~�[, 0);

  �Q�[�W = def_sprite_dummy (DOT16,
                             &(load_files[C_�Q�[�W].pcg->pcg_ptr_ptr),
                             load_files[C_�Q�[�W].pcg->num_p);
  select_sprite_pcg (�Q�[�W, 0);

  ���� = def_sprite_dummy (DOT16,
                           &(load_files[C_����].pcg->pcg_ptr_ptr),
                           load_files[C_����].pcg->num_p);
  select_sprite_pcg (����, 0);
}

/* PCG �f�[�^�����[�h���� */
void
���[�h�f�[�^ (void)
{
  char fname[64];
  /* ���@ */
  strcpy (fname, LOAD_DIR);
  strcat (fname, load_files[C_���@].file_name);
  load_files[C_���@].pcg = PCG���[�h(fname);
  strcpy (fname, LOAD_DIR);
  strcat (fname, load_files[C_�~��].file_name);
  load_files[C_�~��].pcg = PCG���[�h(fname);

  /* �e */
  strcpy (fname, LOAD_DIR);
  strcat (fname, load_files[C_�e].file_name);
  load_files[C_�e].pcg = PCG���[�h(fname);

  /* �G�L�����N�^ */
  strcpy (fname, LOAD_DIR);
  strcat (fname, load_files[C_�G0].file_name);
  load_files[C_�G0].pcg = PCG���[�h(fname);
  strcpy (fname, LOAD_DIR);
  strcat (fname, load_files[C_�G1].file_name);
  load_files[C_�G1].pcg = PCG���[�h(fname);

  /* ���� */
  strcpy (fname, LOAD_DIR);
  strcat (fname, load_files[C_����0].file_name);
  load_files[C_����0].pcg = PCG���[�h(fname);

  /* �Q�[�W */
  strcpy (fname, LOAD_DIR);
  strcat (fname, load_files[C_�Q�[�W].file_name);
  load_files[C_�Q�[�W].pcg = PCG���[�h(fname);

  /* ���� */
  strcpy (fname, LOAD_DIR);
  strcat (fname, load_files[C_����].file_name);
  load_files[C_����].pcg = PCG���[�h(fname);

  �_�~�[������ ();
}

#ifndef USE_XC_LIB
static int
getl (FILE *fp)
{
  int i = fgetc (fp);
  i = ((i << 8) | fgetc (fp));
  i = ((i << 8) | fgetc (fp));
  i = ((i << 8) | fgetc (fp));
  return i;
}
#endif

void
��ʏ����� (void)
{
  int i;
  CRTMOD (10);
  G_CLR_ON ();
  B_CUROFF ();
  for (i = 0; i < 128; i++)
    SP_REGST (i, -1, 0, 0, 0, 0);
  SP_INIT ();
  SP_ON ();
  {
    int j;
    FILE *fp = fopen (LOAD_DIR "�p���b�g.PAL", "rb");
    if (!fp)
      game_abort ("�p���b�g�t�@�C�����ǂ߂܂���");
    for (j = 1; j < 4; j++)
      for (i = 0; i < 16; i++)
	SPALET (0x80 + i, j, getl (fp));
  }
  VDISPST (vsync_disp, 0, 1);
  CRTCRAS (raster_scroll, 1);
}

void
��ʏI������ (void)
{
  VDISPST (0, 0, 1);
  CRTCRAS (0, 0);
  CRTMOD (16);
  B_CURON ();
  while (B_KEYSNS ())
    B_KEYINP ();
}

#ifdef USE_XC_LIB
static void
trap14(void)
{
  PRAMREG (code, d7);       /* �p�����[�^���W�X�^ d7 */
  PRAMREG (add,  a6);       /* �p�����[�^���W�X�^ a6 */
  SET_FRAME (a5);           /* �t���[���|�C���^�� a5 �Ɏw�� */
  char *p =(char *)add;

  /* code ����G���[�𕪐� */
  switch (code&0xffff)
    {
    case 2:
      /* �o�X�G���[ */
      trapbuf.flag = code;
      trapbuf.mes = "�o�X�G���[���������܂���";
      break;
    case 3:
      /* �A�h���X�G���[ */
      trapbuf.flag = code;
      trapbuf.mes = "�A�h���X�G���[���������܂���";
      break;
    case 4:
      /* �������Ȗ��� */
      trapbuf.flag = code;
      trapbuf.mes = "�������Ȗ��߂����s���܂���";
      break;
    }
 if ((code &0xff00))
   {
     if ((code &0xff) == 2)
       {
         trapbuf.flag = -1;
         trapbuf.mes  = "�h���C�u�̏������ł��Ă��܂���";
       }
    }
 if (trapbuf.flag || (code&0xffff) == 0x1f || (code&0xffff) == 0x301f)
    {
      trapbuf.sr_reg = *(short *)p;
      p+=2;
      trapbuf.pc_reg = *(int *)p;
      asm ("\tmove.w #$ff,d0\n\ttrap #15\n");
      IJUMP_RTE();
    }
  else
    IJUMP(trap_14);
}
#endif

static void
my_abort(int val)
{
#ifdef USE_XC_LIB
  INTVCS(0x2e,trap_14);
  VDISPST (0, 0, 1);
  CRTCRAS (0, 0);
  CRTMOD (16);
  B_CURON ();
  if (trapbuf.flag > 0)
    {
      extern (*_main)();
      extern int _SSTA;
      extern int _PSTA;
      trapbuf.flag = 0;
      fprintf (stderr,"%s\r\n",trapbuf.mes);
      fprintf (stderr," pc=%X",trapbuf.pc_reg);
      fprintf (stderr," offset=%X\r\n",trapbuf.pc_reg - (int) &_main);
    }
  else
    {
      fprintf (stderr,"%s\r\n",trapbuf.mes);
      game_abort ("");
    }
  exit (1);
#else
  switch (val)
    {
    case SIGSEGV:
      game_abort ("�o�X�G���[����");
      break;
    case SIGBUS:
      game_abort ("�A�h���X�G���[����");
      break;
    case SIGILL:
      game_abort ("�������Ȗ��ߎ��s");
      break;
    default:
      game_abort ("�Ȃ��H�Ȃ��H");
      break;
    }
#endif
}

void
init_trap14 (void)
{
#ifdef USE_XC_LIB
  trap_14 = (void *)INTVCG (0x2e);
  INTVCS (0x2e, trap14);
  INTVCS (0xfff2, my_abort);
  INTVCS (0xfff1, my_abort);
#else
  signal (SIGILL, my_abort);
  signal (SIGBUS, my_abort);
  signal (SIGSEGV, my_abort);
#endif
}

