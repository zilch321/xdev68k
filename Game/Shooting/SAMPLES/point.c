#include <stdio.h>
#include <stdlib.h>

typedef struct friend_loop {
  char *name;                /* 名前 */
  char *address;             /* 住所 */
  char *tel_no;              /* 電話番号 */
  int  sex;                  /* 性別 */
  struct friend_loop *next;  /* 友達へのポインタ */
} FRIEND;

FRIEND *root;

void
make_root ()
{
  /* まずメモリを確保します。 */
  root = malloc (sizeof (FRIEND));

  /* 名前を登録 */
  root -> name = "よしくん";
  /* 住所を登録 */
  root -> address = "橋の下";
  /* 電話を登録 */
  root -> tel_no  = "0123-45-6789";

  /* 友達は現在いない */
  root -> next = 0;
}


void
add_friend(char *name, char *address, char *tel_no)
{
  FRIEND *new_p;
  FRIEND *p;
  /* 友達がいない人までたどる */
  for (p = root; p -> next; p = p -> next)
    ;
  
  /* メモリを確保して */
  new_p = malloc (sizeof (FRIEND));
  /* 友達の輪にいれてあげる */
  p -> next = new_p;

  new_p -> name = name;
  new_p -> address = address;
  new_p -> tel_no = tel_no;

  /* 次はいない */
  new_p -> next = 0;
}

void
main()
{
  FRIEND *x;
  make_root ();
  add_friend ("くんちゃん", "雲の上", "123-4565");
  add_friend ("おっきん", "海の中", "456-4579");
  add_friend ("まこちゃん", "山の頂", "456-4579");
  for (x = root; x -> next; x = x -> next)
    printf ("%sの友達は%sです\n",x -> name, x -> next -> name);
}
