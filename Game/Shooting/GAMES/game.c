/* �ȒP�ȃQ�[�� for C Magazine */

#define MAIN
#include "game.h"

/* �Q�[���̃��C�����[�`�� */
static void
�Q�[�����C�� (void)
{
  int sc = 0;
  int lkup = 5;
  int �� = 0;

  while (!�I && �� <= �ŏI��)
    {
      ���[�h�}�b�v (��);
      do {
	  �w�i�ړ����� ();
	  �X�R�A�\�� ();
	  �Q�[�W�\�� ();
	  sp_is_ready = 1;
	  while (sp_is_ready)
	    ;
	  �������s ();
      } while (!�Q�[���J�n);

     ���@�ړ����� ();
     �e���ˈړ� ();
     sp_is_ready = 1;
     while (sp_is_ready)
      ;

      do
	{
	  /* �ꎞ��~���� */
	  if (BITSNS (0) & 2)
	    {
	      while ((BITSNS (0) & 2))
		;
	      while (!(BITSNS (0) & 2))
		;
	      while ((BITSNS (0) & 2))
		;
	    }
	  ���@�ړ����� ();
	  �e���ˈړ� ();
	  �G�L���������ړ� ();
	  �����蔻�� ();
	  �w�i�ړ����� ();
	  �X�R�A�\�� ();
	  �Q�[�W�\�� ();
	  sp_is_ready = 1;
	  while (sp_is_ready)
	    ;
	  �������s ();
  	  if (((�o�ߎ���++) & 7) == 7)
	    �X�R�A += 1;
	  if ((�X�R�A >> 2) - sc > lkup)
	    {
	      sc = (�X�R�A >> 2);
	      �����N += �����N < MAX_NUM ? (�����N > 90 ? lkup += 5, 1 : 5) : 0;
	    }
	}
      while (!�I && !�ʃN���A);
      if (�ʃN���A)
        {
          �ʃN���A = 0;
          ��++;
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

  ��ʏ����� ();
  ���[�h�f�[�^ ();
  BG�f�[�^������ ();
  sp_is_ready = 1;
  while (sp_is_ready)
    ;
  �Q�[�����C�� ();
  ��ʏI������ ();
#ifdef SOFT_TRANS
  B_SUPER (ssp);
#endif
  printf ("�o�ߎ���  %d �X�R�A %d �����N %d\n",
	  �o�ߎ���, �X�R�A, �����N);
  exit (0);
}
