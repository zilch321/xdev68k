#include "game.h"

/* #define MAP_IS_FILE */

#ifndef MAP_IS_FILE
#include "mapdata.h"
#endif

#include "sindata.h"

static int 面初期化 = 1;

/* Vram 書き込みアドレス */
static unsigned char *vram0 = (unsigned char *) (0xc80000 - 0x400 * 272);
static unsigned char *vram1 = (unsigned char *) (0xd00000 - 0x400 * 272);

static int now_counter;
static unsigned char *map_data_ptr0;
static unsigned char *map_data_ptr1;

#define RASTER_MIN 40
#define RASTER_MAX RASTER_MIN + 512
#define RASTER_STEP 32

static int *raster_map;
static int scroll_counter;
static short do_raster;
static short start_raster = RASTER_MIN;
static short end_raster = RASTER_MIN;
static int index_val;
static CRTC_REG raster_val;

/* 16*16 矩形を指定された Vram アドレスに書き込み */

#ifdef SOFT_TRANS
static void
write_vram (unsigned short *vr, unsigned short *dat)
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
#else
#define DMA_SENS                                             \
({ register int d0 asm ("d0");                               \
   d0 = 0x8d;                                                \
   asm volatile ("trap #15":"=d"(d0):"0"(d0));               \
   d0;                                                       \
})

#define DO_DMA(BUF,DAT)                                      \
do {  register int d0 asm ("d0");                            \
      register int d1 asm ("d1");                            \
      register int d2 asm ("d2");                            \
      register void *a1 asm ("a1");                          \
      register void *a2 asm ("a2");                          \
      d0 = 0x8b;                                             \
      d1 = 0b1_000_01_01;                                    \
      d2 = 16;                                               \
      a1 = (BUF); a2 = (DAT);                                \
      asm (                                                  \
      "trap #15"::"d"(d0),"d"(d1),"d"(d2),"a"(a1),"a"(a2)    \
          );                                                 \
} while (0)

typedef struct
{
  unsigned char  *addr;
  unsigned short count;
} array_chain;

static void
write_vram (unsigned char *vr, unsigned char *dat)
{
  int i;
  static array_chain buf[16];
  while (DMA_SENS)
    ;
  for (i = 0; i < 16; i++)
    {
      buf[i].addr =  vr;
      buf[i].count = 32;
      vr += 0x400;
    }
  DO_DMA (buf, dat);
}

#endif

void write_one_block0 ()
{
  static int write_count;
  write_vram (vram0, (unsigned char *)map_data[map_data_ptr0[now_counter]]);
  vram0 += 32;
  write_count ++;
  if (write_count == H_BLOCK_NUM)
    {
      write_count = 0;
      vram0 -= ((H_BLOCK_NUM * 32) + 0x400 * 16);
      if (vram0 < (unsigned char *) 0xc00000)
        vram0 =  (unsigned char *) (0xc80000 - 0x400 * 16);
    }
}

void write_one_block1 ()
{
  static int write_count;
  write_vram (vram1, (unsigned char *) map_data[map_data_ptr1[now_counter]]);
  vram1 += 32;
  write_count ++;
  if (write_count == H_BLOCK_NUM)
    {
      write_count = 0;
      vram1 -= ((H_BLOCK_NUM * 32) + 0x400 * 16);
      if (vram1 < (unsigned char *) 0xc80000)
        vram1 =  (unsigned char *) (0xd00000 - 0x400 * 16);
    }
}

void ロードマップ (int 面)
{
  static char file_name[] = "han0.dat";
  char name[128];
  unsigned char gbuf[256];
  FILE *file;
  file_name[3] += 面;
  strcpy (name, LOAD_DIR);
  strcat (name, file_name);
  file = fopen (name, "rb");
  if (!file)
    game_abort ("マップファイルがありません");
  fread (g_palet, sizeof (g_palet), sizeof (char), file);
  if (!map_data[0])
    {
      int i;
      for (i = 0; i < 256; i++)
        map_data[i] = xmalloc (sizeof (short) * 256);
    }
  {
    int i,j;
    unsigned short *p;
    unsigned char *q;
    for (i = 0; i < 256; i++)
      {
        fread (gbuf, sizeof (gbuf), sizeof (char), file);
        p = map_data[i];
        q = gbuf;
        for (j = 0; j < 256; j++)
          *p ++ = *q ++;
      }
  }
  fclose (file);
#ifdef MAP_IS_FILE
  strcpy (name, LOAD_DIR);
  file_name[5] = 'd';
  strcat (name, file_name);
  file_name[5] = 'p';
  file = fopen (name, "rb");
  if (!file)
    game_abort ("マップデータファイルがありません");
  map_data_ptr0 = xmalloc (now_counter = filelength (fileno (file)));
  fread (map_data_ptr0, now_counter, sizeof (char), file);
  fclose (file);
#else
  map_data_ptr0 = MAP_DATA_PTR0;
  map_data_ptr1 = MAP_DATA_PTR1;
  if (sizeof (MAP_DATA_PTR0) != sizeof (MAP_DATA_PTR1))
    game_abort ("マップデータ異常");
  now_counter = sizeof (MAP_DATA_PTR0);
  {
    int i,j;
    unsigned char buf[H_BLOCK_NUM];
    unsigned char *p;
    p = map_data_ptr0;
    for (j = 0; j < sizeof (MAP_DATA_PTR0)/ H_BLOCK_NUM; j++)
      {
        for (i = 0; i < H_BLOCK_NUM; i++)
          buf[i] = *p++;
        for (i = 0; i < H_BLOCK_NUM; i++)
          *--p = buf[i];
        p += H_BLOCK_NUM;
      }
    p = map_data_ptr1;
    for (j = 0; j < sizeof (MAP_DATA_PTR1)/ H_BLOCK_NUM; j++)
      {
        for (i = 0; i < H_BLOCK_NUM; i++)
          buf[i] = *p++;
        for (i = 0; i < H_BLOCK_NUM; i++)
          *--p = buf[i];
        p += H_BLOCK_NUM;
      }
  }
#endif
  {
    int i;
    int counter;
    raster_map =
      xmalloc (sizeof (int) * (now_counter/ H_BLOCK_NUM + 1));
    counter = 0;
    for (i = 16; i < now_counter / H_BLOCK_NUM; i++)
      {
      	unsigned char dat =
      	   map_data_ptr0[sizeof (MAP_DATA_PTR0) - 1 - i * H_BLOCK_NUM];
      	counter += 32;
    	if (dat == RASTER_DATA)
          raster_map[i - 16] = counter;
        else
          raster_map[i - 16] = 0;
      }
  }
  面初期化 = 1;
}


void
raster_scroll ()
{
  static short count;
  static short last;
  static short next = RASTER_MIN;
  /* ラスター位置指定レジスタアドレス */
  short *next_inter = (short *) 0xe80012;
  /* スクロールレジスタアドレス */
  if (do_raster)
    {
      /* スクロールレジスタアドレス */
      CRTC_REG *crtc = (CRTC_REG *) 0xe80018;
      short difs = sin_tbl[index_val][count];
      next += RASTER_STEP;
      if (!last && end_raster < RASTER_MAX && end_raster < next)
        {
          next = end_raster;
          last = 1;
        }
      else if (next > RASTER_MAX)
        last = 1;
      if (last)
        {
          if (start_raster > RASTER_MIN && start_raster < RASTER_MAX)
            next = start_raster;
          else
            next = RASTER_MIN;
          last = count = difs = 0;
        }
      raster_val.sc2_x_reg = raster_val.sc3_x_reg = scroll_data.sc2_x_reg + difs;
      *crtc = raster_val;
    }
  else
    next = RASTER_MIN;
  /* 次回割り込み位置を指定する */
  *next_inter = next;
  count ++;
  if (count > 32)
    count = 0;
  IRTE ();
}

void
背景移動処理 (void)
{
  static int cont = 0;
  static int cont_block = 0;
  static int pal_count;
  if (!面初期化)
    {
      if (!面クリア)
        {
          int i;
          int j = PAL_C_MIN + (cont >> 2) % (PAL_C_MAX - PAL_C_MIN);
          for (i = 0; i < PAL_C_MAX - PAL_C_MIN; i++)
            {
              c_palet[i] = g_palet[j];
              if (++j > PAL_C_MAX)
                j = PAL_C_MIN;
            }
          if (cont_block < H_BLOCK_NUM)
            {
              now_counter --;
              write_one_block0 ();
              write_one_block1 ();
            }
          if (cont & 1)
            {
              scroll_data.sc0_y_reg --;
              scroll_data.sc1_y_reg --;
              scroll_data.sc2_y_reg --;
              scroll_data.sc3_y_reg --;
              raster_val = scroll_data;
              scroll_counter +=2;
              if (++index_val > 31)
                index_val = 0;
              if (raster_map[scroll_counter/32])
                end_raster += 2;
              if (end_raster > RASTER_MIN + RASTER_STEP)
                do_raster = 1;
              if (end_raster > RASTER_MIN && raster_map[scroll_counter/32] == 0)
                start_raster += 2;
              if (start_raster > RASTER_MAX - RASTER_STEP)
                {
                  do_raster = 0;
                  end_raster = start_raster = RASTER_MIN;
                }
            }
          cont ++;
          if (++cont_block > 31)
            cont_block = 0;
        }
      if (now_counter == 0)
        面クリア = 1;
      return;
    }

  if (面初期化 == 1)
    {
      int i;
      面初期化 =  2;
      for (i = 0; i < 256; i++)
        GPALET (i, 0);
      for (i = 0; i < H_BLOCK_NUM * 16 + H_BLOCK_NUM; i++)
        {
          now_counter --;
          write_one_block0 ();
          write_one_block1 ();
        }
      half_def_data = 0b1_0_0_1_1_1_1_0_010_0_1111;
      use_half_tone = 1;
    }
  else if (面初期化 < (12 * 32 + 2))
    {
      面初期化 ++;
      if (面初期化 % 12 == 2)
        {
          int i,pal;
          pal_count++;
          for (i = 0; i < 256; i++)
            {
              pal = 0;
              if ((g_palet[i] >> 11) > pal_count)
                pal |= pal_count << 11;
              else
                pal |= (g_palet[i] & 0b11111_00000_00000_0);
              if (((g_palet[i] >> 6) & 0b11111) > pal_count)
                pal |= pal_count << 6;
              else
                pal |= (g_palet[i] & 0b00000_11111_00000_0);
              if (((g_palet[i] >> 1) & 0b11111) > pal_count)
                pal |= pal_count << 1;
              else
                pal |= (g_palet[i] & 0b00000_00000_11111_0);
              palet_buf[i] = pal;
            }
          palet_def = 1;
        }
    }
  else
    {
      ゲーム開始 = 1;
      pal_count = 0;
      面初期化 = 0;
    }
}

