/* C Maga X68000 Game ���@���� */

#include "game.h"

/* ���@�̈ړ������ƒe�̔��˂�ǂݎ��B*/
enum �ړ�����
�����ǎ� ()
{
  unsigned char data;
  static short �A�j��;
  {
    /* GCC asm �����g���� trap�𔭍s���� */
    register int d0 asm ("d0");
    register int d1 asm ("d1");
    d1 = 0;
    d0 = 0x3b;
    asm ("trap #15": "=d" (d0):"0" (d0), "d" (d1));
    data = ~d0;
  }
  if (data & 0b01000000)
    �I = 1;

  if (���ꎩ�@)
    {
      display_sprite (�~��sp, ��\��);
      �~�� = 0;
      return �Î~;
    }

  /* ���@�̒e���ˏ��� */
  if (data & 0b00100000)
    {
      if (�e���� == 0)
	�e���� = 2;
      else if (�~�� < 30 * 5)
        {
          �~�� += 4;
        }
      if (�~��)
        {
          short sel = (�A�j�� >> 2) % 5;
          if (sel)
            {
              display_sprite (�~��sp, �\��);
              select_sprite_pcg (�~��sp, sel - 1);
            }
          else
            display_sprite (�~��sp, ��\��);
          �A�j��++;
        }
    }
  else if (�e���� == 2)
    {
      �A�j�� = 0;
      �e���� = 1;
    }

  /* �ړ������̌��� */
  switch (data & 0b00001111)
    {
    case 0b1000:
      return �E;
    case 0b0100:
      return ��;
    case 0b0001:
      return ��;
    case 0b0010:
      return ��;
    case 0b0101:
      return ����;
    case 0b0110:
      return ����;
    case 0b1001:
      return �E��;
    case 0b1010:
      return �E��;
    }
  return �Î~;
}

/* ���@�̈ړ��������s���B
  1�h�b�g�ړ����\�ɂ��邽�ߏ��������������Ă��� */
void
���@�ړ����� (void)
{
  static enum �ړ����� �O��ړ����� = �Î~;
  static int ��������J�E���^;
  static int �X�΃J�E���^;
  enum �ړ����� �ړ����� = �����ǎ� ();

  if (SPD_WORK1 (���@))
    if ((--SPD_WORK1 (���@)) == 0)
      select_sprite_color (���@, 1);

  if (�ړ����� == �Î~)
    {
      ��������J�E���^--;
      if (��������J�E���^ > 2)
	select_sprite_pcg (���@, 1);
      else
	{
	  select_sprite_pcg (���@, 0);
	  select_sprite_h_invert (���@, 0);
	}
      �O��ړ����� = �Î~;
      return;
    }
  else
    {
      int �ړ���;
      /* �O�񓯂������ɓ����Ă���Ή������ē��� */
      if (�ړ����� == �O��ړ�����)
	{
	  if (��������J�E���^ < 4)
	    {
	      �ړ��� = 1;
	      ��������J�E���^++;
	    }
	  else
	    �ړ��� = 2;
	}
      else
	{
	  ��������J�E���^ = 0;
	  �ړ��� = 1;
	}

      switch (�ړ�����)
        {
        case ��:
	  if (SPD_POS_Y (���@) > 32)
	    {
	      move_sprite_diff (���@, 0, -�ړ���);
	      move_sprite_diff (�~��sp, 0, -�ړ���);
	    }
	  select_sprite_pcg (���@, 0);
	  select_sprite_h_invert (���@, 0);
	  break;
        case ��:
	  if (SPD_POS_Y (���@) < 256- 16)
	    {
	      move_sprite_diff (���@, 0, �ړ���);
	      move_sprite_diff (�~��sp, 0, �ړ���);
	    }
	  select_sprite_pcg (���@, 0);
	  select_sprite_h_invert (���@, 0);
	  break;
        case �E:
	  if (SPD_POS_X (���@) < 256 - 16)
	    {
	      move_sprite_diff (���@, �ړ���, 0);
	      move_sprite_diff (�~��sp, �ړ���, 0);
	    }
	  if (�ړ��� == 1)
	    select_sprite_pcg (���@, 1);
	  else
	    select_sprite_pcg (���@, 2);
	  select_sprite_h_invert (���@, 1);
	  break;
        case ��:
	  if (SPD_POS_X (���@) > 32)
	    {
	      move_sprite_diff (���@, -�ړ���, 0);
	      move_sprite_diff (�~��sp, -�ړ���, 0);
	    }
	  if (�ړ��� == 1)
	    select_sprite_pcg (���@, 1);
	  else
	    select_sprite_pcg (���@, 2);
	  select_sprite_h_invert (���@, 0);
          break;
        case ����:
          if (�O��ړ����� == �ړ�����)
            �X�΃J�E���^++;
          else
            �X�΃J�E���^ = 0;
	  if (�ړ��� == 1)
	    select_sprite_pcg (���@, 1);
	  else
	    select_sprite_pcg (���@, 2);
          if (�X�΃J�E���^ % 3 == 2)
            �ړ��� /= 2;
	  if (SPD_POS_X (���@) > 32 && SPD_POS_Y (���@) > 32)
	    {
	      move_sprite_diff (���@, -�ړ���, -�ړ���);
	      move_sprite_diff (�~��sp, -�ړ���, -�ړ���);
	    }
	  select_sprite_h_invert (���@, 0);
	  break;
        case ����:
	  if (�ړ��� == 1)
	    select_sprite_pcg (���@, 1);
	  else
	    select_sprite_pcg (���@, 2);
          if (�O��ړ����� == �ړ�����)
            �X�΃J�E���^++;
          else
            �X�΃J�E���^ = 0;
          if (�X�΃J�E���^ % 3 == 2)
            �ړ��� /= 2;
	  if (SPD_POS_X (���@) > 32 && SPD_POS_Y (���@) < 256- 16)
	    {
	      move_sprite_diff (���@, -�ړ���, �ړ���);
	      move_sprite_diff (�~��sp, -�ړ���, �ړ���);
	    }
	  select_sprite_h_invert (���@, 0);
	  break;
        case �E��:
	  if (�ړ��� == 1)
	    select_sprite_pcg (���@, 1);
	  else
	    select_sprite_pcg (���@, 2);
          if (�O��ړ����� == �ړ�����)
            �X�΃J�E���^++;
          else
            �X�΃J�E���^ = 0;
          if (�X�΃J�E���^ % 3 == 2)
            �ړ��� /= 2;
	  if (SPD_POS_X (���@) < 256 - 16 && SPD_POS_Y (���@) > 32)
	    {
	      move_sprite_diff (���@, �ړ���, -�ړ���);
	      move_sprite_diff (�~��sp, �ړ���, -�ړ���);
	    }
	  select_sprite_h_invert (���@, 1);
	  break;
        case �E��:
	  if (�ړ��� == 1)
	    select_sprite_pcg (���@, 1);
	  else
	    select_sprite_pcg (���@, 2);
          if (�O��ړ����� == �ړ�����)
            �X�΃J�E���^++;
          else
            �X�΃J�E���^ = 0;
          if (�X�΃J�E���^ % 3 == 2)
            �ړ��� /= 2;
	  if (SPD_POS_X (���@) < 256 - 16 && SPD_POS_Y (���@) < 256- 16)
	    {
	      move_sprite_diff (���@, �ړ���, �ړ���);
	      move_sprite_diff (�~��sp, �ړ���, �ړ���);
	    }
	  select_sprite_h_invert (���@, 1);
	  break;
        case �Î~:
          game_abort ("���@�ړ������ُ�");
          break;
        }
      �O��ړ����� = �ړ�����;
    }
}

/* �e�L�����N�^�[�̈ړ��������s���B�����������ꂽ�� 1 ��Ԃ��B */
static int
�e�ړ����� (Sprite �Ώ�)
{
  move_sprite_diff (�Ώ�, 0, -6);
  if (SPD_POS_Y (�Ώ�) < 12)
    return 1;
  else
    return 0;
}

/* �e�̔����ƈړ����s�� */
void
�e���ˈړ� (void)
{
  int �e��local;

  if (�e���� == 1)
    {
      Sprite �����L����;
      /* Debug 05 09 */
      �e���� = 0;
      /* �e�̐���Max�ȉ��Ȃ�L�����𔭐������� */
      if (�e�� < MAX_BOM && !���ꎩ�@)
	{
	  int ��;
	  for (�� = 0; �� < MAX_BOM; ��++)
	    if (!�e[��])
	      break;
	  �e[��] = �����L���� = dup_sprite (�e�_�~�[);
	  move_sprite_abs (�����L����, SPD_POS_X (���@), SPD_POS_Y (���@) - 6);

	  select_sprite_pcg (�����L����, �~��/30);
	  SPD_REGIST (�����L����) = �~��/3 + 1;
	  �e���� = �~�� = 0;
          display_sprite (�~��sp, ��\��);
	  select_sprite_color (�����L����, 3);
	  /* �\�����s�� */
	  display_sprite (�����L����, �\��);
          /* ���������������Ă��� */
          SPD_WORK0 (�����L����) = C_�e;
	  �e��++;
	}
    }
  for (�e��local = 0; �e��local < MAX_BOM; �e��local++)
    if (�e[�e��local] && �e�ړ����� (�e[�e��local]))
      �����L�^ (�e[�e��local], �e��local);
}

