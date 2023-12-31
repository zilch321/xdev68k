/* Cmaga X68000 Game by Yohino (C) 1992 03 05 */

#include "game.h"

#ifdef USE_XC_LIB
static struct {
 int flag;                  /* エラー種別フラグ */
 unsigned short sr_reg;     /* エラー時の SR    */
 int pc_reg;                /* エラー時の PC    */
 char *mes;                 /* メッセージ       */
} trapbuf;

static void (*trap_14)();   /* 元の trap 14 ベクタを保存 */
#endif


volatile void
game_abort (char *mes)
{
  VDISPST (0, 0, 1);
  CRTCRAS (0, 0);
  CRTMOD (16);
  B_CURON ();
  printf ("\n%s\n", mes);
  printf ("  異常終了します\n");
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
    game_abort ("メモリ不足です");
  return ret;
}

static GAME_PCG *
PCGロード (char *fname)
{
  FILE *fp = fopen (fname, "rb");
  char mes[64];
  if (!fp)
    {
      sprintf (mes, "ファイル %s が見付かりません",fname);
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
              sprintf (mes, "ファイル %s が異常です", fname);
              game_abort (mes);
            }
        }
      return retval;
    }
}

static void
ダミー初期化 (void)
{
  自機 = def_sprite (DOT16,
                     &(load_files[C_自機].pcg->pcg_ptr_ptr),
                     load_files[C_自機].pcg->num_p);
  move_sprite_abs (自機, 128, 220);
  select_sprite_pcg (自機, 0);
  select_sprite_color (自機, 1);
  display_sprite (自機, 表示);
  SPD_WORK1 (自機) = 0;
  SPD_REGIST (自機) = 3;

  蓄積sp = def_sprite (DOT16,
                       &(load_files[C_蓄積].pcg->pcg_ptr_ptr),
                         load_files[C_蓄積].pcg->num_p);
  move_sprite_abs (蓄積sp, 128, 220 - 10);
  select_sprite_pcg (蓄積sp, 0);
  select_sprite_color (蓄積sp, 3);
  display_sprite (蓄積sp, 非表示);

  弾ダミー = def_sprite_dummy (DOT16,
                               &(load_files[C_弾].pcg->pcg_ptr_ptr),
                               load_files[C_弾].pcg->num_p);
  select_sprite_pcg (弾ダミー, 0);

  タイプA = def_sprite_dummy (DOT16,
                              &(load_files[C_敵0].pcg->pcg_ptr_ptr),
                              load_files[C_敵0].pcg->num_p);
  select_sprite_pcg (タイプA, 0);

  タイプB = def_sprite_dummy (DOT16,
                              &(load_files[C_敵1].pcg->pcg_ptr_ptr),
                              load_files[C_敵1].pcg->num_p);
  select_sprite_pcg (タイプB, 0);
  爆発0ダミー = def_sprite_dummy (DOT16,
                                  &(load_files[C_爆発0].pcg->pcg_ptr_ptr),
                                  load_files[C_爆発0].pcg->num_p);
  select_sprite_pcg (爆発0ダミー, 0);

  ゲージ = def_sprite_dummy (DOT16,
                             &(load_files[C_ゲージ].pcg->pcg_ptr_ptr),
                             load_files[C_ゲージ].pcg->num_p);
  select_sprite_pcg (ゲージ, 0);

  数字 = def_sprite_dummy (DOT16,
                           &(load_files[C_数字].pcg->pcg_ptr_ptr),
                           load_files[C_数字].pcg->num_p);
  select_sprite_pcg (数字, 0);
}

/* PCG データをロードする */
void
ロードデータ (void)
{
  char fname[64];
  /* 自機 */
  strcpy (fname, LOAD_DIR);
  strcat (fname, load_files[C_自機].file_name);
  load_files[C_自機].pcg = PCGロード(fname);
  strcpy (fname, LOAD_DIR);
  strcat (fname, load_files[C_蓄積].file_name);
  load_files[C_蓄積].pcg = PCGロード(fname);

  /* 弾 */
  strcpy (fname, LOAD_DIR);
  strcat (fname, load_files[C_弾].file_name);
  load_files[C_弾].pcg = PCGロード(fname);

  /* 敵キャラクタ */
  strcpy (fname, LOAD_DIR);
  strcat (fname, load_files[C_敵0].file_name);
  load_files[C_敵0].pcg = PCGロード(fname);
  strcpy (fname, LOAD_DIR);
  strcat (fname, load_files[C_敵1].file_name);
  load_files[C_敵1].pcg = PCGロード(fname);

  /* 爆発 */
  strcpy (fname, LOAD_DIR);
  strcat (fname, load_files[C_爆発0].file_name);
  load_files[C_爆発0].pcg = PCGロード(fname);

  /* ゲージ */
  strcpy (fname, LOAD_DIR);
  strcat (fname, load_files[C_ゲージ].file_name);
  load_files[C_ゲージ].pcg = PCGロード(fname);

  /* 数字 */
  strcpy (fname, LOAD_DIR);
  strcat (fname, load_files[C_数字].file_name);
  load_files[C_数字].pcg = PCGロード(fname);

  ダミー初期化 ();
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
画面初期化 (void)
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
    FILE *fp = fopen (LOAD_DIR "パレット.PAL", "rb");
    if (!fp)
      game_abort ("パレットファイルが読めません");
    for (j = 1; j < 4; j++)
      for (i = 0; i < 16; i++)
	SPALET (0x80 + i, j, getl (fp));
  }
  VDISPST (vsync_disp, 0, 1);
  CRTCRAS (raster_scroll, 1);
}

void
画面終了処理 (void)
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
  PRAMREG (code, d7);       /* パラメータレジスタ d7 */
  PRAMREG (add,  a6);       /* パラメータレジスタ a6 */
  SET_FRAME (a5);           /* フレームポインタを a5 に指定 */
  char *p =(char *)add;

  /* code からエラーを分析 */
  switch (code&0xffff)
    {
    case 2:
      /* バスエラー */
      trapbuf.flag = code;
      trapbuf.mes = "バスエラーが発生しました";
      break;
    case 3:
      /* アドレスエラー */
      trapbuf.flag = code;
      trapbuf.mes = "アドレスエラーが発生しました";
      break;
    case 4:
      /* おかしな命令 */
      trapbuf.flag = code;
      trapbuf.mes = "おかしな命令を実行しました";
      break;
    }
 if ((code &0xff00))
   {
     if ((code &0xff) == 2)
       {
         trapbuf.flag = -1;
         trapbuf.mes  = "ドライブの準備ができていません";
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
      game_abort ("バスエラー発生");
      break;
    case SIGBUS:
      game_abort ("アドレスエラー発生");
      break;
    case SIGILL:
      game_abort ("おかしな命令実行");
      break;
    default:
      game_abort ("なぜ？なぜ？");
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

