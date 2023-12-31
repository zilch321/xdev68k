/*
 * PROJECT C Library, X68000 PROGRAMMING INTERFACE DEFINITION
 * --------------------------------------------------------------------
 * This file is written by the Project C Library Group,  and completely
 * in public domain. You can freely use, copy, modify, and redistribute
 * the whole contents, without this notice.
 * --------------------------------------------------------------------
 * $Id: widec.h,v 1.2 1993/04/30 19:11:07 mura Exp $
 */

#ifndef __widec_h__
#define __widec_h__

#ifndef __cdecl_h__
#include <cdecl.h>
#endif

#ifndef __stdio_h__
#include <stdio.h>
#endif

#ifndef NULL
#define NULL ((void *) 0)
#endif

#ifndef WNULL
#define WNULL ((void *) 0)
#endif

#ifndef WEOF
#define WEOF (-1)
#endif

#ifndef __wchar_t_defined__
#define __wchar_t_defined__
typedef int_ wchar_t;
#endif

#ifndef __wint_t_defined__
#define __wint_t_defined__
typedef int_ wint_t;
#endif

#ifndef __size_t_defined__
#define __size_t_defined__
typedef unsigned int_ size_t;
#endif

#define getwc(p)    fgetwc (p)
#define getwchar()  fgetwc (stdin)
#define putwc(x,p)  fputwc ((x), (p))
#define putwchar(x) fputwc ((x), stdout)

EXT (int_ fputws (const wchar_t *, FILE *));
EXT (int_ fwprintf (FILE *, const wchar_t * dotdot_));
EXT (int_ fwscanf (FILE *, const wchar_t * dotdot_));
EXT (int_ putws (const wchar_t *));
EXT (int_ swprintf (wchar_t *, size_t, const wchar_t * dotdot_));
EXT (int_ swscanf (const wchar_t *, const wchar_t * dotdot_));
EXT (int_ vfwprintf (FILE *, const wchar_t *, va_list));
EXT (int_ vswprintf (wchar_t *, const wchar_t *, va_list));
EXT (int_ vwprintf (const wchar_t *, va_list));
EXT (int_ wprintf (const wchar_t * dotdot_));
EXT (int_ wscanf (const wchar_t * dotdot_));
EXT (wchar_t *fgetws (wchar_t *, int_, FILE *));
EXT (wchar_t *getws (wchar_t *));
EXT (wint_t fgetwc (FILE *));
EXT (wint_t fputwc (wint_t, FILE *));
EXT (wint_t ungetwc (wint_t, FILE *));

#endif
