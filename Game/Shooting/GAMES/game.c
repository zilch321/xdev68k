/* 簡単なゲーム for C Magazine */

#define MAIN
#include "game.h"

/* ゲームのメインルーチン */
static void
ゲームメイン (void)
{
  int sc = 0;
  int lkup = 5;
  int 面 = 0;

  while (!終 && 面 <= 最終面)
    {
      ロードマップ (面);
      do {
	  背景移動処理 ();
	  スコア表示 ();
	  ゲージ表示 ();
	  sp_is_ready = 1;
	  while (sp_is_ready)
	    ;
	  消去実行 ();
      } while (!ゲーム開始);

     自機移動処理 ();
     弾発射移動 ();
     sp_is_ready = 1;
     while (sp_is_ready)
      ;

      do
	{
	  /* 一時停止処理 */
	  if (BITSNS (0) & 2)
	    {
	      while ((BITSNS (0) & 2))
		;
	      while (!(BITSNS (0) & 2))
		;
	      while ((BITSNS (0) & 2))
		;
	    }
	  自機移動処理 ();
	  弾発射移動 ();
	  敵キャラ発生移動 ();
	  当たり判定 ();
	  背景移動処理 ();
	  スコア表示 ();
	  ゲージ表示 ();
	  sp_is_ready = 1;
	  while (sp_is_ready)
	    ;
	  消去実行 ();
  	  if (((経過時間++) & 7) == 7)
	    スコア += 1;
	  if ((スコア >> 2) - sc > lkup)
	    {
	      sc = (スコア >> 2);
	      ランク += ランク < MAX_NUM ? (ランク > 90 ? lkup += 5, 1 : 5) : 0;
	    }
	}
      while (!終 && !面クリア);
      if (面クリア)
        {
          面クリア = 0;
          面++;
        }
    }
}

void
main ()
{
#ifdef SOFT_TRANS
  volatile int ssp = 0;
#endif
  init_trap14 ();

#ifdef SOFT_TRANS
  ssp = B_SUPER (0);
#endif
  if (setjmp (err_buf))
    {
#ifdef SOFT_TRANS
      if (ssp)
        B_SUPER (ssp);
#endif
      exit (1);
    }

  画面初期化 ();
  ロードデータ ();
  BGデータ初期化 ();
  sp_is_ready = 1;
  while (sp_is_ready)
    ;
  ゲームメイン ();
  画面終了処理 ();
#ifdef SOFT_TRANS
  B_SUPER (ssp);
#endif
  printf ("経過時間  %d スコア %d ランク %d\n",
	  経過時間, スコア, ランク);
  exit (0);
}
