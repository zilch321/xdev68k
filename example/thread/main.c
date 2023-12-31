/*
	�}���`�X���b�h�������s���܂��B

	[���]
		Human68k �́u�o�b�N�O���E���h�����v�𗘗p���A�����̃X���b�h�������s
		���܂��B

		X68K �� CPU �̓V���O���R�A�Ȃ̂ŁA�����̃X���b�h�𓯎��Ɏ��s���邱�Ƃ�
		�ł��܂��񂪁ACPU �̎��s�ʒu���������Ŋe�X���b�h�ɐ؂�ւ��邱�Ƃɂ��A
		�^���I�ȕ�����s���\�ł��B

	[!!!!! ���� !!!!!]
		Human68k �̃o�b�N�O���E���h�����𗘗p����ɂ́ACONFIG.SYS �Ɉȉ��̋L�q
		���K�v�ł��B

			PROCESS = <�v���O������> <���x��> <�^�C���X���C�X�l>

			�E<�v���O������>
				����Ɏ��s����v���O�������B
				2�`32�͈̔͂Ŏw��B

			�E<���x��>
				�v���O�����̎��s�Ԋu�����߂�l�B
				2�`255�͈̔͂Ŏw��B

			�E<�^�C���X���C�X�l>
				�e�v���O�����̎��s���ԁB
				1�`100ms�͈̔͂Ŏw��B

			[��] PROCESS = 10 2 10

		XC �� printf() �֐��͍ē��u���b�N�̎d�g�݂������Ȃ��̂ŁA�����X���b�h
		���烍�O�o�͂���ƁA�\��������܂��B���̖��̑Ώ����@�͂���܂���B
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <doslib.h>


/* �X���b�h�̃X�^�b�N */
static uint8_t s_usp[1024*16] = {0};
static uint8_t s_ssp[1024*16] = {0};

/* �X���b�h�̏I���t���O */
static volatile int s_has_finished = 0;

/* �o�b�N�O���E���h�X���b�h�֐� */
static void thread() {
	/* �X���b�h���� printf */
	int loop_count_max = 200;
	for (int loop_count = 0; loop_count < loop_count_max; loop_count++) {
		printf("thread: loop_count %d/%d\n", loop_count+1, loop_count_max);
	}

	/* �X���b�h�̏I�� */
	printf("thread: KILL_PR()\n");
	s_has_finished = 1;
	KILL_PR();

	/* �����ɂ͓��B���Ȃ� */
	printf("thread: unreachable.\n");
}


int main(int argc, char *argv[]){
	/* �o�b�N�O���E���h�X���b�h�̍쐬 */
	int thread_id = OPEN_PR(
		/* const char *name */		"my_thread",						/* �X���b�h�̖��O�i15 �����ȓ��j*/
		/* int counter */			2,									/* �^�X�N�̎��s�Ԋu�̐���p�����[�^�i2�`255�j*/
		/* int usp */				(uint32_t)&s_usp[sizeof(s_usp)],	/* �^�X�N�N������ usp �̏����l */
		/* int ssp */				(uint32_t)&s_ssp[sizeof(s_ssp)],	/* �^�X�N�N������ ssp �̏����l */
		/* int sr */				(uint32_t)0,						/* �^�X�N�N������ sr �̏����l */
		/* int pc */				(uint32_t)thread,					/* �^�X�N�N������ pc �̏����l */
		/* struct PRCCTRL *buff */	NULL,								/* �^�X�N�ԒʐM�̂��߂̗̈���i�ȗ��j*/
		/* long sleep_time */		1									/* �N�����҂����ԁi1 ���ŒZ�j*/
	);

	/* �o�b�N�O���E���h�X���b�h�̍쐬�Ɏ��s������I�� */
	if (thread_id < 0) {
		printf("ERROR : thread_id = %d\n", thread_id);
		return EXIT_FAILURE;
	}

	/* ���C���X���b�h���� printf */
	int loop_count_max = 200;
	for (int loop_count = 0; loop_count < loop_count_max; loop_count++) {
		printf("main: loop_count %d/%d\n", loop_count+1, loop_count_max);
	}

	/* �o�b�N�O���E���h�X���b�h�̏I���҂� */
	/*
		�����ɂ͂��̕��@�Ō��o�ł���̂� KILL_PR() ���s���O�̃^�C�~���O�ł���A
		KILL_PR() ���s�����͌��o�ł��Ȃ��B
	*/
	while (s_has_finished == 0) {
		/* CPU �����ߖ�̂��ߏ�������������� */
		CHANGE_PR();
	}

	printf("main: exit.\n");
	return EXIT_SUCCESS;
}


