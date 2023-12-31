#include <stdio.h>
#include <stdlib.h>

typedef struct friend_loop {
  char *name;                /* ���O */
  char *address;             /* �Z�� */
  char *tel_no;              /* �d�b�ԍ� */
  int  sex;                  /* ���� */
  struct friend_loop *next;  /* �F�B�ւ̃|�C���^ */
} FRIEND;

FRIEND *root;

void
make_root ()
{
  /* �܂����������m�ۂ��܂��B */
  root = malloc (sizeof (FRIEND));

  /* ���O��o�^ */
  root -> name = "�悵����";
  /* �Z����o�^ */
  root -> address = "���̉�";
  /* �d�b��o�^ */
  root -> tel_no  = "0123-45-6789";

  /* �F�B�͌��݂��Ȃ� */
  root -> next = 0;
}


void
add_friend(char *name, char *address, char *tel_no)
{
  FRIEND *new_p;
  FRIEND *p;
  /* �F�B�����Ȃ��l�܂ł��ǂ� */
  for (p = root; p -> next; p = p -> next)
    ;
  
  /* ���������m�ۂ��� */
  new_p = malloc (sizeof (FRIEND));
  /* �F�B�̗ւɂ���Ă����� */
  p -> next = new_p;

  new_p -> name = name;
  new_p -> address = address;
  new_p -> tel_no = tel_no;

  /* ���͂��Ȃ� */
  new_p -> next = 0;
}

void
main()
{
  FRIEND *x;
  make_root ();
  add_friend ("���񂿂��", "�_�̏�", "123-4565");
  add_friend ("��������", "�C�̒�", "456-4579");
  add_friend ("�܂������", "�R�̒�", "456-4579");
  for (x = root; x -> next; x = x -> next)
    printf ("%s�̗F�B��%s�ł�\n",x -> name, x -> next -> name);
}
