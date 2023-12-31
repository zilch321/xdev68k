/* C Maga X68000 Game 自機処理 */

#include "game.h"

/* 自機の移動方向と弾の発射を読み取る。*/
enum 移動方向
方向読取 ()
{
  unsigned char data;
  static short アニメ;
  {
    /* GCC asm 文を使って trapを発行する */
    register int d0 asm ("d0");
    register int d1 asm ("d1");
    d1 = 0;
    d0 = 0x3b;
    asm ("trap #15": "=d" (d0):"0" (d0), "d" (d1));
    data = ~d0;
  }
  if (data & 0b01000000)
    終 = 1;

  if (やられ自機)
    {
      display_sprite (蓄積sp, 非表示);
      蓄積 = 0;
      return 静止;
    }

  /* 自機の弾発射処理 */
  if (data & 0b00100000)
    {
      if (弾発射 == 0)
	弾発射 = 2;
      else if (蓄積 < 30 * 5)
        {
          蓄積 += 4;
        }
      if (蓄積)
        {
          short sel = (アニメ >> 2) % 5;
          if (sel)
            {
              display_sprite (蓄積sp, 表示);
              select_sprite_pcg (蓄積sp, sel - 1);
            }
          else
            display_sprite (蓄積sp, 非表示);
          アニメ++;
        }
    }
  else if (弾発射 == 2)
    {
      アニメ = 0;
      弾発射 = 1;
    }

  /* 移動方向の決定 */
  switch (data & 0b00001111)
    {
    case 0b1000:
      return 右;
    case 0b0100:
      return 左;
    case 0b0001:
      return 上;
    case 0b0010:
      return 下;
    case 0b0101:
      return 左上;
    case 0b0110:
      return 左下;
    case 0b1001:
      return 右上;
    case 0b1010:
      return 右下;
    }
  return 静止;
}

/* 自機の移動処理を行う。
  1ドット移動を可能にするため少し処理を加えておく */
void
自機移動処理 (void)
{
  static enum 移動方向 前回移動方向 = 静止;
  static int 同一方向カウンタ;
  static int 傾斜カウンタ;
  enum 移動方向 移動方向 = 方向読取 ();

  if (SPD_WORK1 (自機))
    if ((--SPD_WORK1 (自機)) == 0)
      select_sprite_color (自機, 1);

  if (移動方向 == 静止)
    {
      同一方向カウンタ--;
      if (同一方向カウンタ > 2)
	select_sprite_pcg (自機, 1);
      else
	{
	  select_sprite_pcg (自機, 0);
	  select_sprite_h_invert (自機, 0);
	}
      前回移動方向 = 静止;
      return;
    }
  else
    {
      int 移動量;
      /* 前回同じ方向に動いていれば加速して動く */
      if (移動方向 == 前回移動方向)
	{
	  if (同一方向カウンタ < 4)
	    {
	      移動量 = 1;
	      同一方向カウンタ++;
	    }
	  else
	    移動量 = 2;
	}
      else
	{
	  同一方向カウンタ = 0;
	  移動量 = 1;
	}

      switch (移動方向)
        {
        case 上:
	  if (SPD_POS_Y (自機) > 32)
	    {
	      move_sprite_diff (自機, 0, -移動量);
	      move_sprite_diff (蓄積sp, 0, -移動量);
	    }
	  select_sprite_pcg (自機, 0);
	  select_sprite_h_invert (自機, 0);
	  break;
        case 下:
	  if (SPD_POS_Y (自機) < 256- 16)
	    {
	      move_sprite_diff (自機, 0, 移動量);
	      move_sprite_diff (蓄積sp, 0, 移動量);
	    }
	  select_sprite_pcg (自機, 0);
	  select_sprite_h_invert (自機, 0);
	  break;
        case 右:
	  if (SPD_POS_X (自機) < 256 - 16)
	    {
	      move_sprite_diff (自機, 移動量, 0);
	      move_sprite_diff (蓄積sp, 移動量, 0);
	    }
	  if (移動量 == 1)
	    select_sprite_pcg (自機, 1);
	  else
	    select_sprite_pcg (自機, 2);
	  select_sprite_h_invert (自機, 1);
	  break;
        case 左:
	  if (SPD_POS_X (自機) > 32)
	    {
	      move_sprite_diff (自機, -移動量, 0);
	      move_sprite_diff (蓄積sp, -移動量, 0);
	    }
	  if (移動量 == 1)
	    select_sprite_pcg (自機, 1);
	  else
	    select_sprite_pcg (自機, 2);
	  select_sprite_h_invert (自機, 0);
          break;
        case 左上:
          if (前回移動方向 == 移動方向)
            傾斜カウンタ++;
          else
            傾斜カウンタ = 0;
	  if (移動量 == 1)
	    select_sprite_pcg (自機, 1);
	  else
	    select_sprite_pcg (自機, 2);
          if (傾斜カウンタ % 3 == 2)
            移動量 /= 2;
	  if (SPD_POS_X (自機) > 32 && SPD_POS_Y (自機) > 32)
	    {
	      move_sprite_diff (自機, -移動量, -移動量);
	      move_sprite_diff (蓄積sp, -移動量, -移動量);
	    }
	  select_sprite_h_invert (自機, 0);
	  break;
        case 左下:
	  if (移動量 == 1)
	    select_sprite_pcg (自機, 1);
	  else
	    select_sprite_pcg (自機, 2);
          if (前回移動方向 == 移動方向)
            傾斜カウンタ++;
          else
            傾斜カウンタ = 0;
          if (傾斜カウンタ % 3 == 2)
            移動量 /= 2;
	  if (SPD_POS_X (自機) > 32 && SPD_POS_Y (自機) < 256- 16)
	    {
	      move_sprite_diff (自機, -移動量, 移動量);
	      move_sprite_diff (蓄積sp, -移動量, 移動量);
	    }
	  select_sprite_h_invert (自機, 0);
	  break;
        case 右上:
	  if (移動量 == 1)
	    select_sprite_pcg (自機, 1);
	  else
	    select_sprite_pcg (自機, 2);
          if (前回移動方向 == 移動方向)
            傾斜カウンタ++;
          else
            傾斜カウンタ = 0;
          if (傾斜カウンタ % 3 == 2)
            移動量 /= 2;
	  if (SPD_POS_X (自機) < 256 - 16 && SPD_POS_Y (自機) > 32)
	    {
	      move_sprite_diff (自機, 移動量, -移動量);
	      move_sprite_diff (蓄積sp, 移動量, -移動量);
	    }
	  select_sprite_h_invert (自機, 1);
	  break;
        case 右下:
	  if (移動量 == 1)
	    select_sprite_pcg (自機, 1);
	  else
	    select_sprite_pcg (自機, 2);
          if (前回移動方向 == 移動方向)
            傾斜カウンタ++;
          else
            傾斜カウンタ = 0;
          if (傾斜カウンタ % 3 == 2)
            移動量 /= 2;
	  if (SPD_POS_X (自機) < 256 - 16 && SPD_POS_Y (自機) < 256- 16)
	    {
	      move_sprite_diff (自機, 移動量, 移動量);
	      move_sprite_diff (蓄積sp, 移動量, 移動量);
	    }
	  select_sprite_h_invert (自機, 1);
	  break;
        case 静止:
          game_abort ("自機移動処理異常");
          break;
        }
      前回移動方向 = 移動方向;
    }
}

/* 弾キャラクターの移動処理を行う。もし消去されたら 1 を返す。 */
static int
弾移動処理 (Sprite 対象)
{
  move_sprite_diff (対象, 0, -6);
  if (SPD_POS_Y (対象) < 12)
    return 1;
  else
    return 0;
}

/* 弾の発生と移動を行う */
void
弾発射移動 (void)
{
  int 弾数local;

  if (弾発射 == 1)
    {
      Sprite 発生キャラ;
      /* Debug 05 09 */
      弾発射 = 0;
      /* 弾の数がMax以下ならキャラを発生させる */
      if (弾数 < MAX_BOM && !やられ自機)
	{
	  int 空き;
	  for (空き = 0; 空き < MAX_BOM; 空き++)
	    if (!弾[空き])
	      break;
	  弾[空き] = 発生キャラ = dup_sprite (弾ダミー);
	  move_sprite_abs (発生キャラ, SPD_POS_X (自機), SPD_POS_Y (自機) - 6);

	  select_sprite_pcg (発生キャラ, 蓄積/30);
	  SPD_REGIST (発生キャラ) = 蓄積/3 + 1;
	  弾発射 = 蓄積 = 0;
          display_sprite (蓄積sp, 非表示);
	  select_sprite_color (発生キャラ, 3);
	  /* 表示を行う */
	  display_sprite (発生キャラ, 表示);
          /* 寿命を初期化しておく */
          SPD_WORK0 (発生キャラ) = C_弾;
	  弾数++;
	}
    }
  for (弾数local = 0; 弾数local < MAX_BOM; 弾数local++)
    if (弾[弾数local] && 弾移動処理 (弾[弾数local]))
      消去記録 (弾[弾数local], 弾数local);
}

