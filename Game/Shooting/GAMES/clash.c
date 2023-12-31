
#include "game.h"

static Sprite �����o�b�t�@[128];
static int �����J�E���^;

void �����L�^ (Sprite �Ώ�, int �ԍ�)
{
  display_sprite (�Ώ�, ��\��);
  switch (SPD_WORK0 (�Ώ�))
    {
    case C_���@:
      game_abort ("���@���������Ă��܂�");
      break;
    case C_�e:
      if (�Ώ� == �e[�ԍ�])
        {
          �e[�ԍ�] = 0;
          �e��--;
        }
      else
        game_abort ("�����L�����N�^�ُ� �e");
      break;
    case C_�G0:
    case C_�G1:
      if (�Ώ� == �G[�ԍ�])
        {
          �G[�ԍ�] = 0;
          �G��--;
        }
      else
        game_abort ("�����L�����N�^�ُ� �G");
      break;
    case C_����0:
      if (�Ώ� == ����[�ԍ�])
        {
          ����[�ԍ�] = 0;
          ������--;
        }
      else
        game_abort ("�����L�����N�^�ُ� ����");
      break;
    }
  �����o�b�t�@[�����J�E���^++] = �Ώ�;
}

void �������s (void)
{
  int i;
  for (i = 0; i < �����J�E���^; i++)
    delete_sprite (�����o�b�t�@[i]);
  �����J�E���^ = 0;
}

/* �����p�^�[���𐶐����� */
static void
�N���b�V�� (Sprite �Ώ�)
{
  int ��;
  Sprite �����L����;
  for (�� = 0; �� < MAX_NUM; ��++)
    if (����[��] == 0)
      break;
  if (�� == MAX_NUM)
    game_abort ("�ُ� �����L�����N�^����");
  ����[��] = �����L���� = dup_sprite (����0�_�~�[);
  move_sprite_abs (�����L����, SPD_POS_X (�Ώ�), SPD_POS_Y (�Ώ�));
  select_sprite_pcg (�����L����, 0);
  select_sprite_color (�����L����, 3);
  display_sprite (�����L����, �\��);
  SPD_WORK0 (�����L����) = C_����0;
  SPD_LIFE (�����L����) = 0;
  ������++;
}

static void
�������� (void)
{
  int i;
  for (i = 0; i < MAX_NUM; i++)
    if (����[i])
      {
      	if (++SPD_LIFE (����[i]) > 23)
      	  �����L�^ (����[i], i);
      	else
      	  {
            select_sprite_pcg (����[i], SPD_LIFE (����[i]) / 8);
            select_sprite_h_invert (����[i], 1 & SPD_LIFE (����[i]));
            select_sprite_v_invert (����[i], 2 & SPD_LIFE (����[i]));
	  }
      }
}

/* �e�ƓG�Ƃ̓����蔻����s�� ���Ȃ�蔲�������m��Ȃ�
   �e���������ׂ����ɂ�1��Ԃ� */

static int
�����蔻��T�u0 (Sprite �e)
{
  int �G�ԍ�;
  int ���Wx = SPD_POS_X (�e);
  int ���Wy = SPD_POS_Y (�e);

  for (�G�ԍ� = 0; �G�ԍ� < MAX_NUM; �G�ԍ�++)
    {
      Sprite �Ώ�;
      if ((�Ώ� = �G[�G�ԍ�]) && SPD_LIFE (�Ώ�) > 0)
	{
	  int �G���Wx = SPD_POS_X (�Ώ�);
	  if (��Βl (���Wx, �G���Wx) < 10)
	    {
	      int �G���Wy = SPD_POS_Y (�Ώ�);
	      if (��Βl (���Wy, �G���Wy) < 10)
		{
		  int �_���[�W = SPD_REGIST (�e);
#ifdef NON_LIKE_R_TYPE
		  SPD_REGIST (�e) -= SPD_REGIST (�Ώ�);
#endif
		  /* �G�L�����̏��� */
		  SPD_REGIST (�Ώ�)-= �_���[�W;
		  if (SPD_REGIST (�Ώ�) < 0)
                    {
                      �N���b�V�� (�Ώ�);
                      �����L�^ (�Ώ�, �G�ԍ�);
                      �X�R�A++;
		    }
		  else
		    {
		      SPD_WORK1 (�Ώ�) = 3;
		      select_sprite_color (�Ώ�, 2);
#ifndef NON_LIKE_R_TYPE
		      return 1;
#endif
                    }
                }
#ifdef NON_LIKE_R_TYPE
              if (SPD_REGIST (�e) < 0)
                return 1;
              else
                select_sprite_pcg (�e, SPD_REGIST (�e)/10);
#endif
	    }
	}
    }
  return 0;
}

static int
�����蔻��T�u1 (void)
{
  int �G�ԍ�;
  int ���Wx = SPD_POS_X (���@);
  int ���Wy = SPD_POS_Y (���@);
  int ������ = 0;

  for (�G�ԍ� = 0; �G�ԍ� < MAX_NUM; �G�ԍ�++)
    {
      Sprite �Ώ�;
      if ((�Ώ� = �G[�G�ԍ�]) && SPD_LIFE (�Ώ�) > 0)
	{
	  int �G���Wx = SPD_POS_X (�Ώ�);
	  if (��Βl (���Wx, �G���Wx) < 10)
	    {
	      int �G���Wy = SPD_POS_Y (�Ώ�);
	      if (��Βl (���Wy, �G���Wy) < 10)
		{
		  SPD_REGIST (�Ώ�)--;
		  if (SPD_REGIST (�Ώ�) < 0)
                    {
                      �N���b�V�� (�Ώ�);
                      �����L�^ (�Ώ�, �G�ԍ�);
                      �X�R�A++;
		    }
		  else
		    {
		      SPD_WORK1 (�Ώ�) = 3;
		      select_sprite_color (�Ώ�, 2);
                    }
		  ������ = 1;
		}
	    }
	}
    }
  return ������;
}

/* �����蔻����s�� */
void
�����蔻�� (void)
{
  int �e��local;
  for (�e��local = 0; �e��local < MAX_BOM; �e��local++)
    if (�e[�e��local] && �����蔻��T�u0 (�e[�e��local]))
      �����L�^ (�e[�e��local], �e��local);

  /* ���@�ɓ����蔻����s�� */
  if (���ꎩ�@)
    {
      SPD_LIFE (���ꎩ�@)++;
      if (SPD_LIFE (���ꎩ�@) == 30)
	select_sprite_pcg (���ꎩ�@, 1);
      if (SPD_LIFE (���ꎩ�@) == 60)
	select_sprite_pcg (���ꎩ�@, 2);
      if (SPD_LIFE (���ꎩ�@) == 120)
	�I = 1;
    }
  else if (SPD_WORK1 (���@) == 0 && �����蔻��T�u1 ())
    {
      select_sprite_color (���@, 2);
      SPD_WORK1 (���@) = 16;
      if ((--SPD_REGIST (���@)) == 0)
	{
	  ���ꎩ�@ = dup_sprite (����0�_�~�[);
	  move_sprite_abs (���ꎩ�@, SPD_POS_X (���@), SPD_POS_Y (���@));
	  select_sprite_pcg (���ꎩ�@, 0);
	  SPD_LIFE (���ꎩ�@) = 0;
	  select_sprite_color (���ꎩ�@, 3);
	  display_sprite (���ꎩ�@, �\��);
	  display_sprite (���@, ��\��);
	}
    }
  �������� ();
}

