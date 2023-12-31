/* Cmagazine Sample �Q�[���w�b�_ */

/* �R���t�B�O�}�N�� */
/* XC (Ver 1 or Ver 2)�̃��C�u�������g�p����
   �ꍇ�̓R�����g���O���Ă��������B */
/* #define USE_XC_LIB */

/* SP_REGST �ň������̐����G���[�ɂȂ�����
   �R�����g���O���Ă��������B */
/* #define HAVE_SPREGST_BUGS */

/* ���ߑł��Ŏ����̒e�̈З͂������������������炵����
   �ꍇ�̓R�����g���O���Ă��������B */
/* #define NON_LIKE_R_TYPE */

/* �w�i�f�[�^���t�@�C���œǂޏꍇ�̓R�����g���O����
   ���������B */
/* #define MAP_IS_FILE */

/* �w�i�`��� DMA �ōs��Ȃ��ꍇ�ɃR�����g���O���Ă�
   ������  */
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

#define ��Βl(X,Y) ((X) - (Y) >= 0 ? (X) - (Y) : -((X) - (Y)))
#define �\��   1
#define ��\�� 0
#define MAX_NUM 118
#define �ŏI��  0

#define PAL_C_MIN 160
#define PAL_C_MAX 175

#define H_BLOCK_NUM 18

/* �@��A�R���p�C���Ɋ��S�Ɉˑ�����L�q */
/* PCG ���W�X�^�̍\���� */
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

/* �X�v���C�g�X�N���[�����W�X�^�\���� */
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

/* �X�v���C�g�f�[�^�\���� */


typedef struct {
  SP_CTRL *spr;                 /* �X�v���C�g�X�N���[�����W�X�^  */
  short   char_no;              /* �L�����N�^�i���o */
  short   pcg_defined;          /* pcg�����ɒ�`����Ă���ꍇ��1 */
  short   anime;                /* �A�j���[�V��������� anime > 0 */
  short   pcg_no[8];            /* �A�j���ppcg��`�ԍ� */
  PCG     *pcg_data[8];         /* �A�j��4�p�^�[��,pcg data�ւ̃|�C���^ */
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

/* �X�N���[�����W�X�^�Ɠ����̍\���� */
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
  { NULL, "���@.PCG", NULL, NULL},
  { NULL, "�~��.PCG", NULL, NULL},
  { NULL, "�e.PCG", NULL, NULL},
  { NULL, "���D.PCG", NULL, NULL},
  { NULL, "�ό`�~�T�C��.PCG", NULL, NULL},
  { NULL, "����0.PCG", NULL, NULL},
  { NULL, "�Q�[�W.PCG",NULL,NULL},
  { NULL, "����.PCG", NULL, NULL},
};
#else
;
#endif

enum �L�����^�C�v
{
  C_���@,
  C_�~��,
  C_�e,
  C_�G0,
  C_�G1,
  C_����0,
  C_�Q�[�W,
  C_����,
};

enum �ړ�����
{
  �Î~,
  �E,
  ��,
  ��,
  ��,
  ����,
  ����,
  �E��,
  �E��
};


/* BG ��ʗp�_�~�[ */
EXTERN Sprite �Q�[�W;
EXTERN Sprite ����;

/* ���[�U�[����̎��@ */
EXTERN Sprite ���@;
EXTERN Sprite �~��sp;
EXTERN Sprite ���ꎩ�@;

/* �G�L�����N�^�[ */
EXTERN Sprite �G[MAX_NUM];
EXTERN Sprite �^�C�vA;
EXTERN Sprite �^�C�vB;

/* ��ʂɑ��݂���e */
#define MAX_BOM 12
EXTERN Sprite �e[MAX_BOM];
EXTERN Sprite �e�_�~�[;

/* �����p�^�[�� */
EXTERN Sprite ����0�_�~�[;
EXTERN Sprite ����[MAX_NUM];

/* ���݂̓G�L������ */
EXTERN int �G��;

/* ���݂̒e�L������ */
EXTERN int �e��;

/* ���݂̔����� */
EXTERN int ������;

/* �o�ߎ��ԃJ�E���^ */
EXTERN int �o�ߎ���;
EXTERN int �����N
#ifdef MAIN
 = 30;
#else
;
#endif

/* ���@���e�𔭎˂���ׂ̃t���O */
EXTERN int �e����;

/* �X�R�A�J�E���^ */
EXTERN int �X�R�A;
EXTERN int �~��;
EXTERN int �I;
EXTERN int �Q�[���J�n;
EXTERN int �ʃN���A;

EXTERN int ���@�X�s�[�h
#ifdef MAIN
= 2;
#else
;
#endif

/* �O���t�B�b�N�p���b�g */
unsigned int g_palet[256];
unsigned short c_palet[PAL_C_MAX - PAL_C_MIN];


/* �}�b�v�O���t�B�b�N�ւ̃|�C���^ */
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
/*���荞�ݏ����֐� */
void vsync_disp (void);

/* utiles.c */
volatile void game_abort (char *);
void *xmalloc (int);
void ���[�h�f�[�^ (void);
void ��ʏ����� (void);
void ��ʏI������ (void);
void init_trap14 (void);
void �����L�^ (Sprite, int);
void �������s (void);

/* clash.c */
void �����蔻�� (void);

/* enemy.c */
void �G�L���������ړ� (void);

/* mychr.c */
void ���@�ړ����� (void);
void �e���ˈړ� (void);

/* map.c */
void ���[�h�}�b�v (int);
void �w�i�ړ����� (void);
void raster_scroll (void);

/* back.c */
void BG�f�[�^������ (void);
void �X�R�A�\�� (void);
void �Q�[�W�\�� (void);

/* game.c */

