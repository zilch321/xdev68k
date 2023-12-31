/*
 * PROJECT C Library, X68000 PROGRAMMING INTERFACE DEFINITION
 * --------------------------------------------------------------------
 * This file is written by the Project C Library Group,  and completely
 * in public domain. You can freely use, copy, modify, and redistribute
 * the whole contents, without this notice.
 * --------------------------------------------------------------------
 * $Id: conio.h,v 1.1.1.1 1993/04/18 16:12:54 mura Exp $
 */

#ifndef __conio_h__
#define __conio_h__

#ifndef __cdecl_h__
#include <cdecl.h>
#endif

EXT (char *cgets (char *));
EXT (int_ cprintf (const char * dotdot_));
EXT (int_ cputs (const char *));
EXT (int_ cscanf (const char * dotdot_));
EXT (int_ getch (void_));
EXT (int_ getche (void_));
EXT (int_ kbhit (void_));
EXT (int_ putch (int_));
EXT (int_ ungetch (int_));

#endif
