#include "game.h"

static BG_REG 数字フォント[10];
static BG_REG ゲージfont[13];


void
BGデータ初期化 (void)
{
  {
    int pcg_no;
    int i;

    pcg_no = SP_PCG_NO (SPD_BODY (数字, 0, 0), 0);
    for (i = 0; i < 4; i++)
      {
        数字フォント[i + 1].sp_code = pcg_no * 4 + i;
        数字フォント[i + 1].color = 3;
      }

    pcg_no = SP_PCG_NO (SPD_BODY (数字, 0, 0), 1);
    for (i = 4; i < 8; i++)
      {
        数字フォント[i + 1].sp_code = pcg_no * 4 + (i - 4);
        数字フォント[i + 1].color = 3;
      }

    pcg_no = SP_PCG_NO (SPD_BODY (数字, 0, 0), 2);
    数字フォント[9].sp_code = pcg_no * 4;
    数字フォント[9].color = 3;
    数字フォント[0].sp_code = pcg_no * 4 + 1;
    数字フォント[0].color = 3;
  }
  {
    int pcg_no;
    int i;
    pcg_no = SP_PCG_NO (SPD_BODY (ゲージ, 0, 0), 0);
    for (i = 0; i < 4; i++)
      {
        ゲージfont[i].sp_code = pcg_no * 4 + i;
        ゲージfont[i].color = 1;
      }
    pcg_no = SP_PCG_NO (SPD_BODY (ゲージ, 0, 0), 1);
    for (i = 4; i < 8; i++)
      {
        ゲージfont[i].sp_code = pcg_no * 4 + (i - 4);
        ゲージfont[i].color = 1;
      }
    pcg_no = SP_PCG_NO (SPD_BODY (ゲージ, 0, 0), 2);
    for (i = 8; i < 12; i++)
      {
        ゲージfont[i].sp_code = pcg_no * 4 + (i - 8);
        ゲージfont[i].color = 1;
      }
   ゲージfont[12].sp_code = ゲージfont[0].sp_code;
   ゲージfont[12].color = ゲージfont[0].color;
   ゲージfont[12].h_invert= 1;
  }
}

void
スコア表示 (void)
{
   BG_REG *dest = &bg_array[4];
   int sc = スコア * 10;
   int i,val;
   for (i = 10000000; i > 0; i/=10)
     {
       val = sc / i;
       *dest++ = 数字フォント[val];
       sc -= (val * i);
     }
}

static char gaji_val[][6] =
{
  { 0, 4, 4, 4, 4, 12 },
  { 1, 4, 4, 4, 4, 12 },
  { 2, 4, 4, 4, 4, 12 },
  { 3, 4, 4, 4, 4, 12 },
  { 3, 5, 4, 4, 4, 12 },
  { 3, 6, 4, 4, 4, 12 },
  { 3, 7, 4, 4, 4, 12 },
  { 3, 8, 4, 4, 4, 12 },
  { 3, 8, 5, 4, 4, 12 },
  { 3, 8, 6, 4, 4, 12 },
  { 3, 8, 7, 4, 4, 12 },
  { 3, 8, 8, 4, 4, 12 },
  { 3, 8, 8, 5, 4, 12 },
  { 3, 8, 8, 6, 4, 12 },
  { 3, 8, 8, 7, 4, 12 },
  { 3, 8, 8, 8, 4, 12 },
  { 3, 8, 8, 8, 5, 12 },
  { 3, 8, 8, 8, 6, 12 },
  { 3, 8, 8, 8, 7, 12 },
  { 3, 8, 8, 8, 8, 12 },
  { 3, 8, 8, 8, 8, 9 },
  { 3, 8, 8, 8, 8, 10 },
  { 3, 8, 8, 8, 8, 11 },
};


void
ゲージ表示 (void)
{
   BG_REG *dest = &bg_array[20];
   int val = 蓄積/(150/(sizeof (gaji_val) / 6));
   int i;
   if (蓄積 && val == 0)
     val = 1;
   else if (val > sizeof (gaji_val) / 6 -1)
     val = sizeof (gaji_val) / 6 -1;
   for (i = 0; i < 6; i++)
     *dest++ = ゲージfont[gaji_val[val][i]];
}

