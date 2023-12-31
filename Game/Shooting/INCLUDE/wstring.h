/*
 * PROJECT C Library, X68000 PROGRAMMING INTERFACE DEFINITION
 * --------------------------------------------------------------------
 * This file is written by the Project C Library Group,  and completely
 * in public domain. You can freely use, copy, modify, and redistribute
 * the whole contents, without this notice.
 * --------------------------------------------------------------------
 * $Id: wstring.h,v 1.2 1993/04/30 19:11:20 mura Exp $
 */

#ifndef __wsing_h__
#define __wsing_h__

#ifndef __cdecl_h__
#include <cdecl.h>
#endif

#ifndef __time_h__
#include <time.h>
#endif

#ifndef NULL
#define NULL ((void *) 0)
#endif

#ifndef WNULL
#define WNULL ((void *) 0)
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

/* for compatibility with OSF/1, and SIGMA */
#define wstrcat   wcscat
#define wstrchr   wcschr
#define wstrcmp   wcscmp
#define wstrcpy   wcscpy
#define wstrcspn  wcscspn
#define wstrdup   wcsdup
#define wstrlen   wcslen
#define wstrncat  wcsncat
#define wstrncmp  wcsncmp
#define wstrncpy  wcsncpy
#define wstrpbrk  wcspbrk
#define wstrrchr  wcsrchr
#define wstrspn   wcsspn
#define wstrtok   wcstok

/* for compatibility with SVR4 */
#define windex    wcschr
#define wrindex   wcsrchr
#define wscat     wcscat
#define wsdup     wcsdup
#define wschr     wcschr
#define wscmp     wcscmp
#define wscmpi    wcsicmp
#define wscpy     wcscpy
#define wscspn    wcscspn
#define wslen     wcslen
#define wsncat    wcsncat
#define wsncmp    wcsncmp
#define wsncpy    wcsncpy
#define wspbrk    wcspbrk
#define wsrchr    wcsrchr
#define wsspn     wcsspn
#define wstok     wcstok

EXT (double wcstod (const wchar_t *, wchar_t **));
EXT (int_ wcscmp (const wchar_t *, const wchar_t *));
EXT (int_ wcscoll (const wchar_t *, const wchar_t *));
EXT (int_ wcsncmp (const wchar_t *, const wchar_t *, size_t));
EXT (int_ wcswidth (const wchar_t *, size_t));
EXT (int_ wcwidth (wint_t));
EXT (long wcstol (const wchar_t *, wchar_t **, int_));
EXT (size_t wcscspn (const wchar_t *, const wchar_t *));
EXT (size_t wcsftime (wchar_t *, size_t, const wchar_t *, const struct tm *));
EXT (size_t wcslen (const wchar_t *));
EXT (size_t wcsspn (const wchar_t *, const wchar_t *));
EXT (size_t wcsxfrm (wchar_t *, const wchar_t *, size_t));
EXT (unsigned long wcstoul (const wchar_t *, wchar_t **, int_));
EXT (wchar_t *wcscat (wchar_t *, const wchar_t *));
EXT (wchar_t *wcschr (const wchar_t *, wint_t));
EXT (wchar_t *wcscpy (wchar_t *, const wchar_t *));
EXT (wchar_t *wsdup (const wchar_t *));
EXT (wchar_t *wcsncat (wchar_t *, const wchar_t *, size_t));
EXT (wchar_t *wcsncpy (wchar_t *, const wchar_t *, size_t));
EXT (wchar_t *wcspbrk (const wchar_t *, const wchar_t *));
EXT (wchar_t *wcsrchr (const wchar_t *, wint_t));
EXT (wchar_t *wcstok (wchar_t *, const wchar_t *));
EXT (wchar_t *wcswcs (const wchar_t *, const wchar_t *));

#endif
