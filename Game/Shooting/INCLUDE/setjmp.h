/*
 * PROJECT C Library, X68000 PROGRAMMING INTERFACE DEFINITION
 * --------------------------------------------------------------------
 * This file is written by the Project C Library Group,  and completely
 * in public domain. You can freely use, copy, modify, and redistribute
 * the whole contents, without this notice.
 * --------------------------------------------------------------------
 * $Id: setjmp.h,v 1.1.1.1 1993/04/18 16:13:32 mura Exp $
 */

#ifndef __setjmp_h__
#define __setjmp_h__

#ifndef __cdecl_h__
#include <cdecl.h>
#endif

/*
** setjmp saves data registers (d3-d7), address registers (a3-a7),
** and program counter (pc).  sigsetjmp saves signal mask in addition
** to the registers.
*/

#define _JBLEN 11

typedef int_ jmp_buf[_JBLEN];
typedef int_ sigjmp_buf[_JBLEN + 1];

EXT (int_ setjmp (jmp_buf));
EXT (int_ sigsetjmp (sigjmp_buf, int_));
EXT (void __volatile longjmp (jmp_buf, int_));
EXT (void __volatile siglongjmp (sigjmp_buf, int_));

#endif
