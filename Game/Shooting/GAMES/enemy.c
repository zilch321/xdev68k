
#include "game.h"

/*
  敵キャラクターの移動処理を行う。
  もし消去されたら 1 を返す。
*/

static int
敵移動処理 (Sprite 対象)
{
  switch (SPD_WORK0 (対象))
    {
    case C_敵0:
      SPD_WORK2 (対象)++;
      if (SPD_WORK2 (対象) == 16)
        select_sprite_pcg (対象, 1);
      else if (SPD_WORK2 (対象) == 32)
        select_sprite_pcg (対象, 2);
      else if (SPD_WORK2 (対象) == 48)
        {
          SPD_WORK2 (対象) = 0;
          select_sprite_pcg (対象, 0);
        }
      SPD_WORK3 (対象)++;
      if (SPD_WORK3 (対象) == 6)
        {
          SPD_WORK3 (対象) = 0;
          if (SPD_POS_X (自機) == SPD_POS_X (対象))
            move_sprite_diff (対象, 0, 1);
          else if (SPD_POS_X (自機) > SPD_POS_X (対象))
            move_sprite_diff (対象, 1, 1);
          else
            move_sprite_diff (対象, -1, 1);
        }
      else
        move_sprite_diff (対象, 0, 1);
      if (SPD_POS_Y (対象) > 273)
        return 1;
      else
        return 0;
      break;

    case C_敵1:
      if (SPD_WORK2 (対象) == 0)
        if (SPD_POS_X (自機) == SPD_POS_X (対象))
           move_sprite_diff (対象, 0, 2);
        else if (SPD_POS_X (自機) > SPD_POS_X (対象))
          move_sprite_diff (対象, 1, 2);
        else
          move_sprite_diff (対象, -1, 2);
      else if (SPD_WORK2 (対象) > 4 * 8)
         move_sprite_diff (対象, 0, 6);
      else
        select_sprite_pcg (対象, (++SPD_WORK2 (対象)) / 8);

      if (SPD_WORK2 (対象) == 0
          && 絶対値 (SPD_POS_X (対象), SPD_POS_X (自機)) < 8)
        select_sprite_pcg (対象, (++SPD_WORK2 (対象)) / 8);

      if (SPD_POS_Y (対象) > 273)
        return 1;
      else
        return 0;
      break;
    default:
      game_abort ("スプライトタイプ異常");
      break;
    }
}

/*
  敵キャラクタをランダムX位置に発生させ移動も行う
*/
void
敵キャラ発生移動 (void)
{
  static int 前回時間;
  Sprite 発生キャラ;
  int キャラ数;

  /* 敵の発生時間間隔をランクに応じて変える */
  if (経過時間 - 前回時間 > MAX_NUM + 2 - ランク)
    {
      前回時間 = 経過時間;

      /* 敵の数が現在のランク以下ならキャラを発生させる */
      if (敵数 < ランク)
	{

	  int 空き;
	  Sprite type;
	  for (空き = 0; 空き < MAX_NUM; 空き++)
	    if (敵[空き] == 0)
	      break;
	  if (空き == MAX_NUM)
	    game_abort ("異常発生　キャラクタ発生");

	  敵[空き] = 発生キャラ =
	    dup_sprite (type = (unsigned) rand ()< 0x2000 ? タイプB : タイプA);

	  /* いい加減なランダム位置に初期化する */
	  move_sprite_abs (発生キャラ, (rand ()% 200) + 16, 0);

	  /* 敵キャラパターンをセレクト */
	  select_sprite_pcg (発生キャラ, 0);

	  /* パレットを選ぶ  */
	  select_sprite_color (発生キャラ, 3);

	  /* 表示を行う */
	  display_sprite (発生キャラ, 表示);

	  /* カタサを設定する。大きくするとカタくなる */
	  SPD_REGIST (発生キャラ) = type == タイプA ? 20 : 40;

	  /* 寿命を初期化しておく */
	  SPD_LIFE (発生キャラ) = 256;

	  SPD_WORK0 (発生キャラ) = type == タイプA ? (int) C_敵0 : (int) C_敵1;
	  SPD_WORK1 (発生キャラ) = 0;
	  SPD_WORK2 (発生キャラ) = 0;
	  SPD_WORK3 (発生キャラ) = 0;

	  敵数++;
	}
    }

  /* 各敵について移動処理を行う */
  for (キャラ数 = 0; キャラ数 < MAX_NUM; キャラ数++)
    {
      Sprite 対象;
      if (対象 = 敵[キャラ数])
	{
	  if (SPD_WORK1 (対象))
	    if (--SPD_WORK1 (対象) == 0)
	      select_sprite_color (対象, 3);
	  if (敵移動処理 (対象))
	    消去記録 (対象, キャラ数);
	}
    }
}

