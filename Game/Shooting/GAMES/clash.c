
#include "game.h"

static Sprite 消去バッファ[128];
static int 消去カウンタ;

void 消去記録 (Sprite 対象, int 番号)
{
  display_sprite (対象, 非表示);
  switch (SPD_WORK0 (対象))
    {
    case C_自機:
      game_abort ("自機を消去しています");
      break;
    case C_弾:
      if (対象 == 弾[番号])
        {
          弾[番号] = 0;
          弾数--;
        }
      else
        game_abort ("消去キャラクタ異常 弾");
      break;
    case C_敵0:
    case C_敵1:
      if (対象 == 敵[番号])
        {
          敵[番号] = 0;
          敵数--;
        }
      else
        game_abort ("消去キャラクタ異常 敵");
      break;
    case C_爆発0:
      if (対象 == 爆発[番号])
        {
          爆発[番号] = 0;
          爆発数--;
        }
      else
        game_abort ("消去キャラクタ異常 爆発");
      break;
    }
  消去バッファ[消去カウンタ++] = 対象;
}

void 消去実行 (void)
{
  int i;
  for (i = 0; i < 消去カウンタ; i++)
    delete_sprite (消去バッファ[i]);
  消去カウンタ = 0;
}

/* 爆発パターンを生成する */
static void
クラッシュ (Sprite 対象)
{
  int 空き;
  Sprite 発生キャラ;
  for (空き = 0; 空き < MAX_NUM; 空き++)
    if (爆発[空き] == 0)
      break;
  if (空き == MAX_NUM)
    game_abort ("異常 爆発キャラクタ発生");
  爆発[空き] = 発生キャラ = dup_sprite (爆発0ダミー);
  move_sprite_abs (発生キャラ, SPD_POS_X (対象), SPD_POS_Y (対象));
  select_sprite_pcg (発生キャラ, 0);
  select_sprite_color (発生キャラ, 3);
  display_sprite (発生キャラ, 表示);
  SPD_WORK0 (発生キャラ) = C_爆発0;
  SPD_LIFE (発生キャラ) = 0;
  爆発数++;
}

static void
爆発処理 (void)
{
  int i;
  for (i = 0; i < MAX_NUM; i++)
    if (爆発[i])
      {
      	if (++SPD_LIFE (爆発[i]) > 23)
      	  消去記録 (爆発[i], i);
      	else
      	  {
            select_sprite_pcg (爆発[i], SPD_LIFE (爆発[i]) / 8);
            select_sprite_h_invert (爆発[i], 1 & SPD_LIFE (爆発[i]));
            select_sprite_v_invert (爆発[i], 2 & SPD_LIFE (爆発[i]));
	  }
      }
}

/* 弾と敵との当たり判定を行う かなり手抜きかも知れない
   弾を消去すべき時には1を返す */

static int
当たり判定サブ0 (Sprite 弾)
{
  int 敵番号;
  int 座標x = SPD_POS_X (弾);
  int 座標y = SPD_POS_Y (弾);

  for (敵番号 = 0; 敵番号 < MAX_NUM; 敵番号++)
    {
      Sprite 対象;
      if ((対象 = 敵[敵番号]) && SPD_LIFE (対象) > 0)
	{
	  int 敵座標x = SPD_POS_X (対象);
	  if (絶対値 (座標x, 敵座標x) < 10)
	    {
	      int 敵座標y = SPD_POS_Y (対象);
	      if (絶対値 (座標y, 敵座標y) < 10)
		{
		  int ダメージ = SPD_REGIST (弾);
#ifdef NON_LIKE_R_TYPE
		  SPD_REGIST (弾) -= SPD_REGIST (対象);
#endif
		  /* 敵キャラの処理 */
		  SPD_REGIST (対象)-= ダメージ;
		  if (SPD_REGIST (対象) < 0)
                    {
                      クラッシュ (対象);
                      消去記録 (対象, 敵番号);
                      スコア++;
		    }
		  else
		    {
		      SPD_WORK1 (対象) = 3;
		      select_sprite_color (対象, 2);
#ifndef NON_LIKE_R_TYPE
		      return 1;
#endif
                    }
                }
#ifdef NON_LIKE_R_TYPE
              if (SPD_REGIST (弾) < 0)
                return 1;
              else
                select_sprite_pcg (弾, SPD_REGIST (弾)/10);
#endif
	    }
	}
    }
  return 0;
}

static int
当たり判定サブ1 (void)
{
  int 敵番号;
  int 座標x = SPD_POS_X (自機);
  int 座標y = SPD_POS_Y (自機);
  int 当たり = 0;

  for (敵番号 = 0; 敵番号 < MAX_NUM; 敵番号++)
    {
      Sprite 対象;
      if ((対象 = 敵[敵番号]) && SPD_LIFE (対象) > 0)
	{
	  int 敵座標x = SPD_POS_X (対象);
	  if (絶対値 (座標x, 敵座標x) < 10)
	    {
	      int 敵座標y = SPD_POS_Y (対象);
	      if (絶対値 (座標y, 敵座標y) < 10)
		{
		  SPD_REGIST (対象)--;
		  if (SPD_REGIST (対象) < 0)
                    {
                      クラッシュ (対象);
                      消去記録 (対象, 敵番号);
                      スコア++;
		    }
		  else
		    {
		      SPD_WORK1 (対象) = 3;
		      select_sprite_color (対象, 2);
                    }
		  当たり = 1;
		}
	    }
	}
    }
  return 当たり;
}

/* 当たり判定を行う */
void
当たり判定 (void)
{
  int 弾数local;
  for (弾数local = 0; 弾数local < MAX_BOM; 弾数local++)
    if (弾[弾数local] && 当たり判定サブ0 (弾[弾数local]))
      消去記録 (弾[弾数local], 弾数local);

  /* 自機に当たり判定を行う */
  if (やられ自機)
    {
      SPD_LIFE (やられ自機)++;
      if (SPD_LIFE (やられ自機) == 30)
	select_sprite_pcg (やられ自機, 1);
      if (SPD_LIFE (やられ自機) == 60)
	select_sprite_pcg (やられ自機, 2);
      if (SPD_LIFE (やられ自機) == 120)
	終 = 1;
    }
  else if (SPD_WORK1 (自機) == 0 && 当たり判定サブ1 ())
    {
      select_sprite_color (自機, 2);
      SPD_WORK1 (自機) = 16;
      if ((--SPD_REGIST (自機)) == 0)
	{
	  やられ自機 = dup_sprite (爆発0ダミー);
	  move_sprite_abs (やられ自機, SPD_POS_X (自機), SPD_POS_Y (自機));
	  select_sprite_pcg (やられ自機, 0);
	  SPD_LIFE (やられ自機) = 0;
	  select_sprite_color (やられ自機, 3);
	  display_sprite (やられ自機, 表示);
	  display_sprite (自機, 非表示);
	}
    }
  爆発処理 ();
}

