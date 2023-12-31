
#include "game.h"

static SP_CTRL  disp_sp[128];
static char this_no_is_use[128];
static char pcg_is_use[128];

static void
active_sprite (sprite sp)
{
  register int ch_no = SP_CHAR_NO (sp);
  this_no_is_use[ch_no] = DISP;
  SP_PRIORITY (sp) = 1;
}

static void
suspend_sprite (sprite sp)
{
  register int ch_no = SP_CHAR_NO (sp);
  this_no_is_use[ch_no] = USE;
  SP_PRIORITY (sp) = 0;
}

static void
free_sprite (sprite sp)
{
  int c_no = SP_CHAR_NO (sp);
  int anime = SP_ANIME (sp);
  if (c_no < 128)
    {
      /* スクロールレジスタ割り当てを解除 */
      this_no_is_use[c_no] = NO_USE;

      /* PCGの使用カウントを減らす */
      do {
        pcg_is_use[SP_PCG_NO (sp, anime)] --;
      } while (--anime >= 0);
      free (sp);
    }
  else if (c_no == 128)
    {
      /* PCGの使用カウントを減らす */
      do {
        pcg_is_use[SP_PCG_NO (sp, anime)] --;
      } while (--anime >= 0);
      free (SP_SP_PTR (sp));
      free (sp);
    }
  else
   game_abort ("free_sprite:スクロールレジスタ番号異常");
}

static sprite
alloc_sprite(void)
{
  register int c_no;
  /* 空きのスクロールレジスタを捜す */
  for (c_no = 0; c_no < 128; c_no ++)
    if (!this_no_is_use[c_no])
      break;
  if (c_no < 128)
    {
      /* データを作成する */
      sprite sp = (sprite) xmalloc (sizeof (SPRITE));
      PCG **pcg;

      /* 各種ポインタの初期化 */
      SP_SP_PTR (sp) = &disp_sp[c_no];
      SP_CHAR_NO(sp) = c_no;
      pcg = SP_PCG_DATA_PTR(sp);
      *pcg ++ = 0;
      *pcg ++ = 0;
      *pcg ++ = 0;
      *pcg ++ = 0;
      *pcg ++ = 0;
      *pcg ++ = 0;
      *pcg ++ = 0;
      *pcg ++ = 0;
      /* 割り当ては行うが表示はしない */
      suspend_sprite (sp);
      return sp;
    }
  else
    game_abort ("alloc_sprite:定義キャラクタ過剰");
}

static sprite
alloc_sprite_dummy (void)
{
  /* データを作成する */
  sprite sp = (sprite) xmalloc (sizeof (SPRITE));
  PCG **pcg;

  /* 各種ポインタの初期化 */
  SP_SP_PTR (sp) = xmalloc (sizeof (SP_CTRL));
  SP_CHAR_NO(sp) = 128;

  pcg = SP_PCG_DATA_PTR(sp);
  *pcg ++ = 0;
  *pcg ++ = 0;
  *pcg ++ = 0;
  *pcg ++ = 0;
  *pcg ++ = 0;
  *pcg ++ = 0;
  *pcg ++ = 0;
  *pcg ++ = 0;
  return sp;
}

static sprite
make_sprite (int anime, PCG **pcg_data, int sc_alloc)
{
  register PCG **pcg;
  register sprite sp = sc_alloc ? alloc_sprite () : alloc_sprite_dummy ();
  SP_ANIME(sp) = anime;
  pcg = SP_PCG_DATA_PTR (sp);
  do {
    *pcg ++ = *pcg_data++;
  } while (--anime >= 0);
  SP_DEFINED (sp) = 0;
  return sp;
}

static sprite
copy_sprite (sprite sp)
{
  register int anime;
  register sprite ret = alloc_sprite ();
  anime = SP_ANIME (ret) = SP_ANIME (sp);

  if (!SP_DEFINED (sp))
    {
      request_def = sp;
      while (request_def)
	;
    }
  SP_DEFINED (ret) = 1;
  do {
    int pcg_no;
    pcg_no = SP_PCG_NO (ret, anime) = SP_PCG_NO (sp, anime);
    SP_PCG_DATA (ret, anime) = SP_PCG_DATA (sp, anime);
    pcg_is_use[pcg_no] ++;
  } while (--anime >= 0);
  return ret;
}

void
display_sprite (Sprite sp, int sw)
{
   int x,y;
   int end_x,end_y;
   void (*func)(sprite) = sw ? active_sprite : suspend_sprite;

   switch (SPD_TYPE (sp))
     {
     case DOT16:
       end_x = 1;
       end_y = 1;
       break;
     case DOT32_1_2:
       end_x = 1;
       end_y = 2;
       break;
     case DOT32_2_1:
       end_x = 2;
       end_y = 1;
       break;
     case DOT32_2_2:
       end_x = 2;
       end_y = 2;
       break;
     case DOT48_1_3:
       end_x = 1;
       end_y = 3;
       break;
     case DOT48_2_3:
       end_x = 2;
       end_y = 3;
       break;
     case DOT48_3_3:
       end_x = 3;
       end_y = 3;
       break;
     case DOT48_3_1:
       end_x = 3;
       end_y = 1;
       break;
     case DOT48_3_2:
       end_x = 3;
       end_y = 2;
       break;
     default:
       game_abort ("delete_sprite:未知のスプライトタイプ");
       break;
     }

   for (y = 0; y < end_y; y++)
     for (x = 0; x < end_x; x++)
       func (SPD_BODY (sp, x, y));
}


void
delete_sprite (Sprite sp)
{
   int x,y;
   int end_x,end_y;
   switch (SPD_TYPE (sp))
     {
     case DOT16:
       end_x = 1;
       end_y = 1;
       break;
     case DOT32_1_2:
       end_x = 1;
       end_y = 2;
       break;
     case DOT32_2_1:
       end_x = 2;
       end_y = 1;
       break;
     case DOT32_2_2:
       end_x = 2;
       end_y = 2;
       break;
     case DOT48_1_3:
       end_x = 1;
       end_y = 3;
       break;
     case DOT48_2_3:
       end_x = 2;
       end_y = 3;
       break;
     case DOT48_3_3:
       end_x = 3;
       end_y = 3;
       break;
     case DOT48_3_1:
       end_x = 3;
       end_y = 1;
       break;
     case DOT48_3_2:
       end_x = 3;
       end_y = 2;
       break;
     default:
       game_abort ("delete_sprite:未知のスプライトタイプ");
       break;
     }

   for (y = 0; y < end_y; y++)
     for (x = 0; x < end_x; x++)
       free_sprite (SPD_BODY (sp, x, y));
}

Sprite
dup_sprite (Sprite sp)
{
  int x,y;
  int end_x,end_y;
  Sprite ret_val;

  switch (SPD_TYPE (sp))
     {
     case DOT16:
       end_x = 1;
       end_y = 1;
       break;
     case DOT32_1_2:
       end_x = 1;
       end_y = 2;
       break;
     case DOT32_2_1:
       end_x = 2;
       end_y = 1;
       break;
     case DOT32_2_2:
       end_x = 2;
       end_y = 2;
       break;
     case DOT48_1_3:
       end_x = 1;
       end_y = 3;
       break;
     case DOT48_2_3:
       end_x = 2;
       end_y = 3;
       break;
     case DOT48_3_3:
       end_x = 3;
       end_y = 3;
       break;
     case DOT48_3_1:
       end_x = 3;
       end_y = 1;
       break;
     case DOT48_3_2:
       end_x = 3;
       end_y = 2;
       break;
     default:
       game_abort ("def_sprite_file:未知のスプライトタイプ");
       break;
     }

   ret_val = (Sprite) xmalloc (sizeof (struct SP_DATA));

   SPD_TYPE (ret_val) = SPD_TYPE (sp);
   SPD_MOVE_FUNC (ret_val) = 0;
   SPD_LIFE (ret_val) = 0;
   SPD_REGIST (ret_val) = 0;
   SPD_ANIME_PTR (ret_val) = 0;

   for (y = 0; y < 3; y++)
     for (x = 0; x < 3; x++)
       SPD_BODY (ret_val, x, y) = 0;

   for (y = 0; y < end_y; y++)
     for (x = 0; x < end_x; x++)
       SPD_BODY (ret_val, x, y) = copy_sprite (SPD_BODY (sp, x, y));

   return ret_val;
}


Sprite
def_sprite (enum sp_type type, PCG ***pcg, int anime)
{
  int x,y;
  int end_x,end_y;
  Sprite ret_val;
  int pcg_index;

  switch (type)
     {
     case DOT16:
       end_x = 1;
       end_y = 1;
       break;
     case DOT32_1_2:
       end_x = 1;
       end_y = 2;
       break;
     case DOT32_2_1:
       end_x = 2;
       end_y = 1;
       break;
     case DOT32_2_2:
       end_x = 2;
       end_y = 2;
       break;
     case DOT48_1_3:
       end_x = 1;
       end_y = 3;
       break;
     case DOT48_2_3:
       end_x = 2;
       end_y = 3;
       break;
     case DOT48_3_3:
       end_x = 3;
       end_y = 3;
       break;
     case DOT48_3_1:
       end_x = 3;
       end_y = 1;
       break;
     case DOT48_3_2:
       end_x = 3;
       end_y = 2;
       break;
     default:
       game_abort ("def_sprite:未知のスプライトタイプ");
       break;
     }

   ret_val = (Sprite) xmalloc (sizeof (struct SP_DATA));

   SPD_TYPE (ret_val) = type;
   SPD_MOVE_FUNC (ret_val) = 0;
   SPD_LIFE (ret_val) = 0;
   SPD_REGIST (ret_val) = 0;
   SPD_ANIME_PTR (ret_val) = 0;

   for (y = 0; y < 3; y++)
     for (x = 0; x < 3; x++)
       SPD_BODY (ret_val, x, y) = 0;
   pcg_index = 0;
   for (y = 0; y < end_y; y++)
     for (x = 0; x < end_x; x++)
       SPD_BODY (ret_val, x, y) = make_sprite (anime, pcg[pcg_index ++], 1);

   return ret_val;
}

Sprite
def_sprite_dummy (enum sp_type type, PCG ***pcg, int anime)
{
  int x,y;
  int end_x,end_y;
  Sprite ret_val;
  int pcg_index;

  switch (type)
     {
     case DOT16:
       end_x = 1;
       end_y = 1;
       break;
     case DOT32_1_2:
       end_x = 1;
       end_y = 2;
       break;
     case DOT32_2_1:
       end_x = 2;
       end_y = 1;
       break;
     case DOT32_2_2:
       end_x = 2;
       end_y = 2;
       break;
     case DOT48_1_3:
       end_x = 1;
       end_y = 3;
       break;
     case DOT48_2_3:
       end_x = 2;
       end_y = 3;
       break;
     case DOT48_3_3:
       end_x = 3;
       end_y = 3;
       break;
     case DOT48_3_1:
       end_x = 3;
       end_y = 1;
       break;
     case DOT48_3_2:
       end_x = 3;
       end_y = 2;
       break;
     default:
       game_abort ("def_sprite:未知のスプライトタイプ");
       break;
     }

   ret_val = (Sprite) xmalloc (sizeof (struct SP_DATA));

   SPD_TYPE (ret_val) = type;
   SPD_MOVE_FUNC (ret_val) = 0;
   SPD_LIFE (ret_val) = 0;
   SPD_REGIST (ret_val) = 0;
   SPD_ANIME_PTR (ret_val) = 0;

   for (y = 0; y < 3; y++)
     for (x = 0; x < 3; x++)
       SPD_BODY (ret_val, x, y) = 0;
   pcg_index = 0;
   for (y = 0; y < end_y; y++)
     for (x = 0; x < end_x; x++)
       SPD_BODY (ret_val, x, y) = make_sprite (anime, pcg[pcg_index ++], 0);

   return ret_val;
}

void
move_sprite_diff (Sprite sp, int dx, int dy)
{
   int x,y;
   int end_x,end_y;
   switch (SPD_TYPE (sp))
     {
     case DOT16:
       end_x = 1;
       end_y = 1;
       break;
     case DOT32_1_2:
       end_x = 1;
       end_y = 2;
       break;
     case DOT32_2_1:
       end_x = 2;
       end_y = 1;
       break;
     case DOT32_2_2:
       end_x = 2;
       end_y = 2;
       break;
     case DOT48_1_3:
       end_x = 1;
       end_y = 3;
       break;
     case DOT48_2_3:
       end_x = 2;
       end_y = 3;
       break;
     case DOT48_3_3:
       end_x = 3;
       end_y = 3;
       break;
     case DOT48_3_1:
       end_x = 3;
       end_y = 1;
       break;
     case DOT48_3_2:
       end_x = 3;
       end_y = 2;
       break;
     default:
       game_abort ("move_sprite_dif:未知のスプライトタイプ");
       break;
     }

   for (y = 0; y < end_y; y++)
     for (x = 0; x < end_x; x++)
       {
       	 SP_POS_X (SPD_BODY (sp, x, y)) += dx;
       	 SP_POS_Y (SPD_BODY (sp, x, y)) += dy;
       }
}

void
move_sprite_abs (Sprite sp, int ax, int ay)
{
   int x,y;
   int end_x,end_y;
   switch (SPD_TYPE (sp))
     {
     case DOT16:
       end_x = 1;
       end_y = 1;
       break;
     case DOT32_1_2:
       end_x = 1;
       end_y = 2;
       break;
     case DOT32_2_1:
       end_x = 2;
       end_y = 1;
       break;
     case DOT32_2_2:
       end_x = 2;
       end_y = 2;
       break;
     case DOT48_1_3:
       end_x = 1;
       end_y = 3;
       break;
     case DOT48_2_3:
       end_x = 2;
       end_y = 3;
       break;
     case DOT48_3_3:
       end_x = 3;
       end_y = 3;
       break;
     case DOT48_3_1:
       end_x = 3;
       end_y = 1;
       break;
     case DOT48_3_2:
       end_x = 3;
       end_y = 2;
       break;
     default:
       game_abort ("move_sprite_dif:未知のスプライトタイプ");
       break;
     }

   for (y = 0; y < end_y; y++)
     for (x = 0; x < end_x; x++)
       {
       	 SP_POS_X (SPD_BODY (sp, x, y)) = ax + x * 16;
       	 SP_POS_Y (SPD_BODY (sp, x, y)) = ay + y * 16;
       }
}

void
select_sprite_pcg (Sprite sp, int sel)
{
   int x,y;
   int end_x,end_y;
   switch (SPD_TYPE (sp))
     {
     case DOT16:
       end_x = 1;
       end_y = 1;
       break;
     case DOT32_1_2:
       end_x = 1;
       end_y = 2;
       break;
     case DOT32_2_1:
       end_x = 2;
       end_y = 1;
       break;
     case DOT32_2_2:
       end_x = 2;
       end_y = 2;
       break;
     case DOT48_1_3:
       end_x = 1;
       end_y = 3;
       break;
     case DOT48_2_3:
       end_x = 2;
       end_y = 3;
       break;
     case DOT48_3_3:
       end_x = 3;
       end_y = 3;
       break;
     case DOT48_3_1:
       end_x = 3;
       end_y = 1;
       break;
     case DOT48_3_2:
       end_x = 3;
       end_y = 2;
       break;
     default:
       game_abort ("select_sprite_pcg:未知のスプライトタイプ");
       break;
     }

   for (y = 0; y < end_y; y++)
     for (x = 0; x < end_x; x++)
       {
       	 if (SP_DEFINED (SPD_BODY (sp, x, y)))
       	   SP_CODE (SPD_BODY (sp, x, y)) = SP_PCG_NO (SPD_BODY (sp, x, y),sel);
       	 else
       	   {
       	     request_def = SPD_BODY (sp, x, y);
       	     while (request_def)
       	       ;
       	     SP_CODE (SPD_BODY (sp, x, y)) = SP_PCG_NO (SPD_BODY (sp, x, y),sel);
       	   }
       }
}

void
select_sprite_color (Sprite sp, int col)
{
   int x,y;
   int end_x,end_y;
   switch (SPD_TYPE (sp))
     {
     case DOT16:
       end_x = 1;
       end_y = 1;
       break;
     case DOT32_1_2:
       end_x = 1;
       end_y = 2;
       break;
     case DOT32_2_1:
       end_x = 2;
       end_y = 1;
       break;
     case DOT32_2_2:
       end_x = 2;
       end_y = 2;
       break;
     case DOT48_1_3:
       end_x = 1;
       end_y = 3;
       break;
     case DOT48_2_3:
       end_x = 2;
       end_y = 3;
       break;
     case DOT48_3_3:
       end_x = 3;
       end_y = 3;
       break;
     case DOT48_3_1:
       end_x = 3;
       end_y = 1;
       break;
     case DOT48_3_2:
       end_x = 3;
       end_y = 2;
       break;
     default:
       game_abort ("select_sprite_color:未知のスプライトタイプ");
       break;
     }

   for (y = 0; y < end_y; y++)
     for (x = 0; x < end_x; x++)
       SP_PALET (SPD_BODY (sp, x, y)) = col;
}

void
select_sprite_h_invert (Sprite sp, int inv)
{
   int x,y;
   int end_x,end_y;
   switch (SPD_TYPE (sp))
     {
     case DOT16:
       end_x = 1;
       end_y = 1;
       break;
     case DOT32_1_2:
       end_x = 1;
       end_y = 2;
       break;
     case DOT32_2_1:
       end_x = 2;
       end_y = 1;
       break;
     case DOT32_2_2:
       end_x = 2;
       end_y = 2;
       break;
     case DOT48_1_3:
       end_x = 1;
       end_y = 3;
       break;
     case DOT48_2_3:
       end_x = 2;
       end_y = 3;
       break;
     case DOT48_3_3:
       end_x = 3;
       end_y = 3;
       break;
     case DOT48_3_1:
       end_x = 3;
       end_y = 1;
       break;
     case DOT48_3_2:
       end_x = 3;
       end_y = 2;
       break;
     default:
       game_abort ("select_sprite_color:未知のスプライトタイプ");
       break;
     }

   for (y = 0; y < end_y; y++)
     for (x = 0; x < end_x; x++)
       SP_H_INV (SPD_BODY (sp, x, y)) = inv;
}

void
select_sprite_v_invert (Sprite sp, int inv)
{
   int x,y;
   int end_x,end_y;
   switch (SPD_TYPE (sp))
     {
     case DOT16:
       end_x = 1;
       end_y = 1;
       break;
     case DOT32_1_2:
       end_x = 1;
       end_y = 2;
       break;
     case DOT32_2_1:
       end_x = 2;
       end_y = 1;
       break;
     case DOT32_2_2:
       end_x = 2;
       end_y = 2;
       break;
     case DOT48_1_3:
       end_x = 1;
       end_y = 3;
       break;
     case DOT48_2_3:
       end_x = 2;
       end_y = 3;
       break;
     case DOT48_3_3:
       end_x = 3;
       end_y = 3;
       break;
     case DOT48_3_1:
       end_x = 3;
       end_y = 1;
       break;
     case DOT48_3_2:
       end_x = 3;
       end_y = 2;
       break;
     default:
       game_abort ("select_sprite_color:未知のスプライトタイプ");
       break;
     }

   for (y = 0; y < end_y; y++)
     for (x = 0; x < end_x; x++)
       SP_V_INV (SPD_BODY (sp, x, y)) = inv;
}

/* スプライトパターンの定義 */
/* 巨大なマクロ */
#define DEF_SP(pat_no,sp_dat)                                     \
{                                                                 \
  int *sp_reg = (int *)(0xeb8000 + 0x80 * (pat_no));              \
  int *dat = (int *)(sp_dat);                                     \
  /* 0 */                                                         \
  *sp_reg ++ = *dat ++;                                           \
  *sp_reg ++ = *dat ++;                                           \
  *sp_reg ++ = *dat ++;                                           \
  *sp_reg ++ = *dat ++;                                           \
  *sp_reg ++ = *dat ++;                                           \
  *sp_reg ++ = *dat ++;                                           \
  *sp_reg ++ = *dat ++;                                           \
  *sp_reg ++ = *dat ++;                                           \
  *sp_reg ++ = *dat ++;                                           \
  *sp_reg ++ = *dat ++;                                           \
  *sp_reg ++ = *dat ++;                                           \
  *sp_reg ++ = *dat ++;                                           \
  *sp_reg ++ = *dat ++;                                           \
  *sp_reg ++ = *dat ++;                                           \
  *sp_reg ++ = *dat ++;                                           \
  *sp_reg ++ = *dat ++;                                           \
  /* 1 */                                                         \
  *sp_reg ++ = *dat ++;                                           \
  *sp_reg ++ = *dat ++;                                           \
  *sp_reg ++ = *dat ++;                                           \
  *sp_reg ++ = *dat ++;                                           \
  *sp_reg ++ = *dat ++;                                           \
  *sp_reg ++ = *dat ++;                                           \
  *sp_reg ++ = *dat ++;                                           \
  *sp_reg ++ = *dat ++;                                           \
  *sp_reg ++ = *dat ++;                                           \
  *sp_reg ++ = *dat ++;                                           \
  *sp_reg ++ = *dat ++;                                           \
  *sp_reg ++ = *dat ++;                                           \
  *sp_reg ++ = *dat ++;                                           \
  *sp_reg ++ = *dat ++;                                           \
  *sp_reg ++ = *dat ++;                                           \
  *sp_reg ++ = *dat ++;                                           \
}

/* 割り込み処理関数 */

static  CRTC_REG *const crtc = (CRTC_REG *) 0xe80018;

void
vsync_disp (void)
{

  *(short *)0xe82500 = 0x09e4;
  if (sp_is_ready || request_def)
    {
      /* SP スクロールレジスタをCPUに開放 */
      *(short *)0xeb0808 &= 0xfdfc;

      /* PCGの定義を行う。1/60秒に4PCG最大とする。間に合うのか？ */
      if (request_def)
        {
	  sprite def_req;
	  if (def_req = request_def)
	    {
	      int anime = SP_ANIME (def_req);
	      do {
	        int i;
	        for (i = 1; i < 128; i++)
		  if (!pcg_is_use[i])
		    break;
	        if (i < 128)
		  {
		    pcg_is_use[i] = 1;
		    SP_PCG_NO (def_req, anime) = i;
		    DEF_SP (i, SP_PCG_DATA (def_req, anime));
		  }
	      } while (--anime >= 0);
	      SP_DEFINED (def_req) = 1;
	      request_def = 0;
	    }
        }
     if (sp_is_ready)
       {
	  int i;
	  SP_CTRL *sp = disp_sp;
	  SP_CTRL *sp_scr_reg = (SP_CTRL *)0xeb0000;
	  /* スプライトスクロールレジスタ書き込み */
	  for (i = 0; i < 128; i++,sp_scr_reg ++)
	    if (this_no_is_use[i] != NO_USE)
	      *sp_scr_reg  = sp[i];
          ++vsync_counter;
          sp_is_ready = 0;
        }
      {
        BG_REG *bg_top = (BG_REG *) 0xebe000;
        int i;
        for (i = 0; i < 32; i++)
          *bg_top++ = bg_array[i];
        *(short *)0xeb0800 = -2;
        *(short *)0xeb0802 = -2;
        *(short *)0xeb0804 = -2;
        *(short *)0xeb0806 = -2;
      }

      /* SP,BG 表示 */
      *(short *)0xeb0808 |= 0x0203;

      /* グラフィック画面スクロール */
      *crtc = scroll_data;
      /* パレットを設定 */
      if (palet_def)
        {
          unsigned short *pal = (unsigned short *) 0xe82000;
          unsigned short *p = palet_buf;
          int i;
          for (i = 0; i < 256; i++)
            *pal ++ = *p++;
          palet_def = 0;
        }
       else
        {
          unsigned short *pal =
           (unsigned short *) (0xe82000 + (PAL_C_MIN * sizeof (short)));
          unsigned short *p = c_palet;
          int i;
          for (i = 0; i < PAL_C_MAX - PAL_C_MIN; i++)
            *pal ++ = *p++;
        }
       if (use_half_tone)
         *(unsigned short *) 0xe82600 = half_def_data;
       else
         *(unsigned short *) 0xe82600 = 0b1_0_0_0_0_0_0_0_010_0_1111;
    }
  IRTE ();
}

