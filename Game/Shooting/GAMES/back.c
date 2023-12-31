#include "game.h"

static BG_REG �����t�H���g[10];
static BG_REG �Q�[�Wfont[13];


void
BG�f�[�^������ (void)
{
  {
    int pcg_no;
    int i;

    pcg_no = SP_PCG_NO (SPD_BODY (����, 0, 0), 0);
    for (i = 0; i < 4; i++)
      {
        �����t�H���g[i + 1].sp_code = pcg_no * 4 + i;
        �����t�H���g[i + 1].color = 3;
      }

    pcg_no = SP_PCG_NO (SPD_BODY (����, 0, 0), 1);
    for (i = 4; i < 8; i++)
      {
        �����t�H���g[i + 1].sp_code = pcg_no * 4 + (i - 4);
        �����t�H���g[i + 1].color = 3;
      }

    pcg_no = SP_PCG_NO (SPD_BODY (����, 0, 0), 2);
    �����t�H���g[9].sp_code = pcg_no * 4;
    �����t�H���g[9].color = 3;
    �����t�H���g[0].sp_code = pcg_no * 4 + 1;
    �����t�H���g[0].color = 3;
  }
  {
    int pcg_no;
    int i;
    pcg_no = SP_PCG_NO (SPD_BODY (�Q�[�W, 0, 0), 0);
    for (i = 0; i < 4; i++)
      {
        �Q�[�Wfont[i].sp_code = pcg_no * 4 + i;
        �Q�[�Wfont[i].color = 1;
      }
    pcg_no = SP_PCG_NO (SPD_BODY (�Q�[�W, 0, 0), 1);
    for (i = 4; i < 8; i++)
      {
        �Q�[�Wfont[i].sp_code = pcg_no * 4 + (i - 4);
        �Q�[�Wfont[i].color = 1;
      }
    pcg_no = SP_PCG_NO (SPD_BODY (�Q�[�W, 0, 0), 2);
    for (i = 8; i < 12; i++)
      {
        �Q�[�Wfont[i].sp_code = pcg_no * 4 + (i - 8);
        �Q�[�Wfont[i].color = 1;
      }
   �Q�[�Wfont[12].sp_code = �Q�[�Wfont[0].sp_code;
   �Q�[�Wfont[12].color = �Q�[�Wfont[0].color;
   �Q�[�Wfont[12].h_invert= 1;
  }
}

void
�X�R�A�\�� (void)
{
   BG_REG *dest = &bg_array[4];
   int sc = �X�R�A * 10;
   int i,val;
   for (i = 10000000; i > 0; i/=10)
     {
       val = sc / i;
       *dest++ = �����t�H���g[val];
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
�Q�[�W�\�� (void)
{
   BG_REG *dest = &bg_array[20];
   int val = �~��/(150/(sizeof (gaji_val) / 6));
   int i;
   if (�~�� && val == 0)
     val = 1;
   else if (val > sizeof (gaji_val) / 6 -1)
     val = sizeof (gaji_val) / 6 -1;
   for (i = 0; i < 6; i++)
     *dest++ = �Q�[�Wfont[gaji_val[val][i]];
}

