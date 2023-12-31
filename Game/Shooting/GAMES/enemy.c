
#include "game.h"

/*
  �G�L�����N�^�[�̈ړ��������s���B
  �����������ꂽ�� 1 ��Ԃ��B
*/

static int
�G�ړ����� (Sprite �Ώ�)
{
  switch (SPD_WORK0 (�Ώ�))
    {
    case C_�G0:
      SPD_WORK2 (�Ώ�)++;
      if (SPD_WORK2 (�Ώ�) == 16)
        select_sprite_pcg (�Ώ�, 1);
      else if (SPD_WORK2 (�Ώ�) == 32)
        select_sprite_pcg (�Ώ�, 2);
      else if (SPD_WORK2 (�Ώ�) == 48)
        {
          SPD_WORK2 (�Ώ�) = 0;
          select_sprite_pcg (�Ώ�, 0);
        }
      SPD_WORK3 (�Ώ�)++;
      if (SPD_WORK3 (�Ώ�) == 6)
        {
          SPD_WORK3 (�Ώ�) = 0;
          if (SPD_POS_X (���@) == SPD_POS_X (�Ώ�))
            move_sprite_diff (�Ώ�, 0, 1);
          else if (SPD_POS_X (���@) > SPD_POS_X (�Ώ�))
            move_sprite_diff (�Ώ�, 1, 1);
          else
            move_sprite_diff (�Ώ�, -1, 1);
        }
      else
        move_sprite_diff (�Ώ�, 0, 1);
      if (SPD_POS_Y (�Ώ�) > 273)
        return 1;
      else
        return 0;
      break;

    case C_�G1:
      if (SPD_WORK2 (�Ώ�) == 0)
        if (SPD_POS_X (���@) == SPD_POS_X (�Ώ�))
           move_sprite_diff (�Ώ�, 0, 2);
        else if (SPD_POS_X (���@) > SPD_POS_X (�Ώ�))
          move_sprite_diff (�Ώ�, 1, 2);
        else
          move_sprite_diff (�Ώ�, -1, 2);
      else if (SPD_WORK2 (�Ώ�) > 4 * 8)
         move_sprite_diff (�Ώ�, 0, 6);
      else
        select_sprite_pcg (�Ώ�, (++SPD_WORK2 (�Ώ�)) / 8);

      if (SPD_WORK2 (�Ώ�) == 0
          && ��Βl (SPD_POS_X (�Ώ�), SPD_POS_X (���@)) < 8)
        select_sprite_pcg (�Ώ�, (++SPD_WORK2 (�Ώ�)) / 8);

      if (SPD_POS_Y (�Ώ�) > 273)
        return 1;
      else
        return 0;
      break;
    default:
      game_abort ("�X�v���C�g�^�C�v�ُ�");
      break;
    }
}

/*
  �G�L�����N�^�������_��X�ʒu�ɔ��������ړ����s��
*/
void
�G�L���������ړ� (void)
{
  static int �O�񎞊�;
  Sprite �����L����;
  int �L������;

  /* �G�̔������ԊԊu�������N�ɉ����ĕς��� */
  if (�o�ߎ��� - �O�񎞊� > MAX_NUM + 2 - �����N)
    {
      �O�񎞊� = �o�ߎ���;

      /* �G�̐������݂̃����N�ȉ��Ȃ�L�����𔭐������� */
      if (�G�� < �����N)
	{

	  int ��;
	  Sprite type;
	  for (�� = 0; �� < MAX_NUM; ��++)
	    if (�G[��] == 0)
	      break;
	  if (�� == MAX_NUM)
	    game_abort ("�ُ픭���@�L�����N�^����");

	  �G[��] = �����L���� =
	    dup_sprite (type = (unsigned) rand ()< 0x2000 ? �^�C�vB : �^�C�vA);

	  /* ���������ȃ����_���ʒu�ɏ��������� */
	  move_sprite_abs (�����L����, (rand ()% 200) + 16, 0);

	  /* �G�L�����p�^�[�����Z���N�g */
	  select_sprite_pcg (�����L����, 0);

	  /* �p���b�g��I��  */
	  select_sprite_color (�����L����, 3);

	  /* �\�����s�� */
	  display_sprite (�����L����, �\��);

	  /* �J�^�T��ݒ肷��B�傫������ƃJ�^���Ȃ� */
	  SPD_REGIST (�����L����) = type == �^�C�vA ? 20 : 40;

	  /* ���������������Ă��� */
	  SPD_LIFE (�����L����) = 256;

	  SPD_WORK0 (�����L����) = type == �^�C�vA ? (int) C_�G0 : (int) C_�G1;
	  SPD_WORK1 (�����L����) = 0;
	  SPD_WORK2 (�����L����) = 0;
	  SPD_WORK3 (�����L����) = 0;

	  �G��++;
	}
    }

  /* �e�G�ɂ��Ĉړ��������s�� */
  for (�L������ = 0; �L������ < MAX_NUM; �L������++)
    {
      Sprite �Ώ�;
      if (�Ώ� = �G[�L������])
	{
	  if (SPD_WORK1 (�Ώ�))
	    if (--SPD_WORK1 (�Ώ�) == 0)
	      select_sprite_color (�Ώ�, 3);
	  if (�G�ړ����� (�Ώ�))
	    �����L�^ (�Ώ�, �L������);
	}
    }
}

