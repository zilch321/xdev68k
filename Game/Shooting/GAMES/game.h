/* Cmagazine Sample ゲームヘッダ */

/* コンフィグマクロ */
/* XC (Ver 1 or Ver 2)のライブラリを使用する
   場合はコメントを外してください。 */
/* #define USE_XC_LIB */

/* SP_REGST で引き数の数がエラーになったら
   コメントを外してください。 */
/* #define HAVE_SPREGST_BUGS */

/* 溜め打ちで自分の弾の威力が当たった数だけ減らしたい
   場合はコメントを外してください。 */
/* #define NON_LIKE_R_TYPE */

/* 背景データをファイルで読む場合はコメントを外して
   ください。 */
/* #define MAP_IS_FILE */

/* 背景描画を DMA で行わない場合にコメントを外してく
   ださい  */
/* #define SOFT_TRANS */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>

#ifdef HAVE_SPREGIST_BUGS
#define SP_REGIST  XC2_BUG_PROTOS
#include <iocslib.h>
#undef SP_REGIST
int SP_REGST(int, int, int, int, int, int);
#else
#include <iocslib.h>
#endif

#include <interrupt.h>
#include <setjmp.h>
#ifndef USE_XC_LIB
#include <signal.h>
#else
#include <doslib.h>
#endif

#ifndef MAIN
#define EXTERN extern
#else
#define EXTERN
#endif

#define DEBUG

#ifndef NULL
#define NULL 0
#endif

#define LOAD_DIR ".\\DATA\\"

#define SP_CHAR_NO(SP)                ((SP) -> char_no)
#define SP_SP_PTR(SP)                 ((SP) -> spr)
#define SP_POS_X(SP)                  ((SP) -> spr -> sp_x)
#define SP_POS_Y(SP)                  ((SP) -> spr -> sp_y)
#define SP_CODE(SP)                   (((SP) -> spr -> sp_ctrl).sp.sp_code)
#define SP_PALET(SP)                  (((SP) -> spr -> sp_ctrl).sp.color)
#define SP_PRIORITY(SP)               (((SP) -> spr -> sp_pwr).sp.pwr)
#define SP_DEFINED(SP)                ((SP) -> pcg_defined)
#define SP_PCG_DATA_PTR(SP)           (&((SP) -> pcg_data[0]))
#define SP_ANIME(SP)                  ((SP) -> anime)
#define SP_PCG_NO(SP,POS)             ((SP) -> pcg_no[POS])
#define SP_PCG_DATA(SP,POS)           ((SP) -> pcg_data[POS])
#define SP_H_INV(SP)                  (((SP) -> spr -> sp_ctrl).sp.h_invert)
#define SP_V_INV(SP)                  (((SP) -> spr -> sp_ctrl).sp.v_invert)

#define SPD_BODY(SP,PART_X,PART_Y)    ((SP) -> body[(PART_X)][(PART_Y)])
#define SPD_TYPE(SP)                  ((SP) -> type)
#define SPD_MOVE(SP)                  (((SP) -> def_move).move_array)
#define SPD_MOVE_FUNC(SP)             (((SP) -> def_move).move_func)
#define SPD_LIFE(SP)                  ((SP) -> life)
#define SPD_REGIST(SP)                ((SP) -> registance)
#define SPD_ANIME_PTR(SP)             ((SP) -> anime_def)
#define SPD_WORK0(SP)                 ((SP) -> work0)
#define SPD_WORK1(SP)                 ((SP) -> work1)
#define SPD_WORK2(SP)                 ((SP) -> work2)
#define SPD_WORK3(SP)                 ((SP) -> work3)
#define SPD_POS_X(SP)                 SP_POS_X(SPD_BODY((SP), 0, 0))
#define SPD_POS_Y(SP)                 SP_POS_Y(SPD_BODY((SP), 0, 0))

#define MOVE_X(MOV,CL)                ((MOV[CL]).dif_x)
#define MOVE_Y(MOV,CL)                ((MOV[CL]).dif_y)

#define  NO_USE 0
#define  DISP   1
#define  USE    2

#define 絶対値(X,Y) ((X) - (Y) >= 0 ? (X) - (Y) : -((X) - (Y)))
#define 表示   1
#define 非表示 0
#define MAX_NUM 118
#define 最終面  0

#define PAL_C_MIN 160
#define PAL_C_MAX 175

#define H_BLOCK_NUM 18

/* 機種、コンパイラに完全に依存する記述 */
/* PCG レジスタの構造体 */
typedef  union  {
    unsigned short dummy;
    struct {
      unsigned pos0: 4;
      unsigned pos1: 4;
      unsigned pos2: 4;
      unsigned pos3: 4;
    } sp;
} SP_REG_U;

typedef SP_REG_U  PCG[64];

typedef struct {
    unsigned v_invert : 1;
    unsigned h_invert : 1;
    unsigned dummy    : 2;
    unsigned color    : 4;
    unsigned sp_code  : 8;
} BG_REG;

/* スプライトスクロールレジスタ構造体 */
typedef struct {
  short int sp_x;
  short int sp_y;
  union {
    short int dummy;
    BG_REG sp;
  } sp_ctrl;
  union {
    short int dummy;
    struct {
      unsigned dummy   : 13;
      unsigned ext     :  1;
      unsigned pwr     :  2;
    } sp;
  } sp_pwr;
} SP_CTRL;

/* スプライトデータ構造体 */


typedef struct {
  SP_CTRL *spr;                 /* スプライトスクロールレジスタ  */
  short   char_no;              /* キャラクタナンバ */
  short   pcg_defined;          /* pcgが既に定義されている場合は1 */
  short   anime;                /* アニメーションすれば anime > 0 */
  short   pcg_no[8];            /* アニメ用pcg定義番号 */
  PCG     *pcg_data[8];         /* アニメ4パターン,pcg dataへのポインタ */
} SPRITE;

typedef SPRITE *sprite;

enum sp_type {
  DOT16,
  DOT32_1_2,
  DOT32_2_1,
  DOT32_2_2,
  DOT48_1_3,
  DOT48_2_3,
  DOT48_3_3,
  DOT48_3_1,
  DOT48_3_2,
};

typedef struct {
  short dif_x;
  short dif_y;
} move;

typedef union {
  move *move_array;
  int (*move_func)();
} move_def;

typedef struct SP_DATA {
  enum sp_type type;
  short life;
  short registance;
  short work0;
  short work1;
  short work2;
  short work3;
  sprite body[3][3];
  move_def   def_move;
  short  *anime_def;
} *Sprite;

/* スクロールレジスタと同等の構造体 */
typedef struct {
  short sc0_x_reg;
  short sc0_y_reg;
  short sc1_x_reg;
  short sc1_y_reg;
  short sc2_x_reg;
  short sc2_y_reg;
  short sc3_x_reg;
  short sc3_y_reg;
} CRTC_REG;

EXTERN CRTC_REG scroll_data
#ifdef MAIN
 =
{
    ((H_BLOCK_NUM * 16) % 256) / 2,
    0,
    ((H_BLOCK_NUM * 16) % 256) / 2,
    0,
    ((H_BLOCK_NUM * 16) % 256) / 2,
    0,
    ((H_BLOCK_NUM * 16) % 256) / 2,
    0
};
#else
;
#endif

EXTERN volatile int vsync_counter;
EXTERN volatile int sp_is_ready;
EXTERN volatile sprite request_def;
EXTERN volatile int palet_def;
EXTERN unsigned short palet_buf[256];
EXTERN BG_REG   bg_array[32];

EXTERN int use_half_tone;
EXTERN unsigned short half_def_data;

EXTERN jmp_buf err_buf;

typedef struct
{
  short num_p;
  PCG **pcg_ptr_ptr;
} GAME_PCG;

EXTERN struct load_file
{
  GAME_PCG *pcg;
  char     *file_name;
  char     *move_file_name;
  short    *moves;
} load_files[]
#ifdef MAIN
 =
{
  { NULL, "自機.PCG", NULL, NULL},
  { NULL, "蓄積.PCG", NULL, NULL},
  { NULL, "弾.PCG", NULL, NULL},
  { NULL, "風船.PCG", NULL, NULL},
  { NULL, "変形ミサイル.PCG", NULL, NULL},
  { NULL, "爆発0.PCG", NULL, NULL},
  { NULL, "ゲージ.PCG",NULL,NULL},
  { NULL, "数字.PCG", NULL, NULL},
};
#else
;
#endif

enum キャラタイプ
{
  C_自機,
  C_蓄積,
  C_弾,
  C_敵0,
  C_敵1,
  C_爆発0,
  C_ゲージ,
  C_数字,
};

enum 移動方向
{
  静止,
  右,
  左,
  上,
  下,
  左上,
  左下,
  右上,
  右下
};


/* BG 画面用ダミー */
EXTERN Sprite ゲージ;
EXTERN Sprite 数字;

/* ユーザー操作の自機 */
EXTERN Sprite 自機;
EXTERN Sprite 蓄積sp;
EXTERN Sprite やられ自機;

/* 敵キャラクター */
EXTERN Sprite 敵[MAX_NUM];
EXTERN Sprite タイプA;
EXTERN Sprite タイプB;

/* 画面に存在する弾 */
#define MAX_BOM 12
EXTERN Sprite 弾[MAX_BOM];
EXTERN Sprite 弾ダミー;

/* 爆発パターン */
EXTERN Sprite 爆発0ダミー;
EXTERN Sprite 爆発[MAX_NUM];

/* 現在の敵キャラ数 */
EXTERN int 敵数;

/* 現在の弾キャラ数 */
EXTERN int 弾数;

/* 現在の爆発数 */
EXTERN int 爆発数;

/* 経過時間カウンタ */
EXTERN int 経過時間;
EXTERN int ランク
#ifdef MAIN
 = 30;
#else
;
#endif

/* 自機が弾を発射する為のフラグ */
EXTERN int 弾発射;

/* スコアカウンタ */
EXTERN int スコア;
EXTERN int 蓄積;
EXTERN int 終;
EXTERN int ゲーム開始;
EXTERN int 面クリア;

EXTERN int 自機スピード
#ifdef MAIN
= 2;
#else
;
#endif

/* グラフィックパレット */
unsigned int g_palet[256];
unsigned short c_palet[PAL_C_MAX - PAL_C_MIN];


/* マップグラフィックへのポインタ */
unsigned short *map_data[256];


/* sprite.c */
void display_sprite (Sprite,int);
void delete_sprite (Sprite);
Sprite dup_sprite (Sprite);
Sprite def_sprite (enum sp_type, PCG ***, int);
Sprite def_sprite_dummy (enum sp_type, PCG ***, int);
void move_sprite_diff (Sprite, int, int);
void move_sprite_abs (Sprite, int, int);
void select_sprite_pcg (Sprite, int);
void select_sprite_color (Sprite, int);
void select_sprite_h_invert (Sprite, int);
void select_sprite_v_invert (Sprite, int);
/*割り込み処理関数 */
void vsync_disp (void);

/* utiles.c */
volatile void game_abort (char *);
void *xmalloc (int);
void ロードデータ (void);
void 画面初期化 (void);
void 画面終了処理 (void);
void init_trap14 (void);
void 消去記録 (Sprite, int);
void 消去実行 (void);

/* clash.c */
void 当たり判定 (void);

/* enemy.c */
void 敵キャラ発生移動 (void);

/* mychr.c */
void 自機移動処理 (void);
void 弾発射移動 (void);

/* map.c */
void ロードマップ (int);
void 背景移動処理 (void);
void raster_scroll (void);

/* back.c */
void BGデータ初期化 (void);
void スコア表示 (void);
void ゲージ表示 (void);

/* game.c */

