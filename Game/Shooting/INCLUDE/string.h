/*
 * PROJECT C Library, X68000 PROGRAMMING INTERFACE DEFINITION
 * --------------------------------------------------------------------
 * This file is written by the Project C Library Group,  and completely
 * in public domain. You can freely use, copy, modify, and redistribute
 * the whole contents, without this notice.
 * --------------------------------------------------------------------
 * $Id: string.h,v 1.4 1993/08/16 13:31:52 mura Exp $
 */

#ifndef __string_h__
#define __string_h__

#ifndef __cdecl_h__
#include <cdecl.h>
#endif

#ifndef __size_t_defined__
#define __size_t_defined__
typedef unsigned int_ size_t;
#endif

#ifndef NULL
#define NULL ((void *) 0)
#endif

#define memcmpi memicmp
#define strcmpi stricmp
#define strcasecmp stricmp
#define strncasecmp strnicmp

#define movmem memmove ((b), (a), (c))
#define movedata(a,b,c) memmove ((b), (a), (c))
#define setmem(a,b,c) memset ((a), (c), (b))

EXT (char *index (const char *, int_));
EXT (char *rindex (const char *, int_));
EXT (char *strcat (char *, const char *));
EXT (char *strchr (const char *, int_));
EXT (char *strcpy (char *, const char *));
EXT (char *strdup (const char *));
EXT (char *strerror (int_));
EXT (char *strlwr (char *));
EXT (char *strncat (char *, const char *, size_t));
EXT (char *strncpy (char *, const char *, size_t));
EXT (char *strnset (char *, int_, size_t));
EXT (char *strpbrk (const char *, const char *));
EXT (char *strrchr (const char *, int_));
EXT (char *strrev (char *));
EXT (char *strset (char *, int_));
EXT (char *strstr (const char *, const char *));
EXT (char *strtok (char *, const char *));
EXT (char *strtok2 (char *, const char *));
EXT (char *strupr (char *));
EXT (int_ __const ffs (int_));
EXT (int_ bcmp (const void *, const void *, size_t));
EXT (int_ bcopy (const void *, void *, size_t));
EXT (int_ bzero (void *, size_t));
EXT (int_ memcmp (const void *, const void *, size_t));
EXT (int_ memicmp (const void *, const void *, size_t));
EXT (int_ stcgfe (char *, const char *));
EXT (int_ stcgfn (char *, const char *));
EXT (int_ strbpl (char **, int_, const char *));
EXT (int_ strcmp (const char *, const char *));
EXT (int_ strcoll (const char *, const char *));
EXT (int_ stricmp (const char *, const char *));
EXT (int_ strncmp (const char *, const char *, size_t));
EXT (int_ strnicmp (const char *, const char *, size_t));
EXT (size_t strcspn (const char *, const char *));
EXT (size_t strlen (const char *));
EXT (size_t strspn (const char *, const char *));
EXT (size_t strxfrm (char *, const char *, size_t));
EXT (void *memccpy (void *, const void *, int_, size_t));
EXT (void *memchr (const void *, int_, size_t));
EXT (void *memcpy (void *, const void *, size_t));
EXT (void *memmove (void *, const void *, size_t));
EXT (void *memset (void *, int_, size_t));
EXT (void repmem (void *, const void *, size_t, size_t));
EXT (void strins (const char *, char *));
EXT (void strmfe (char *, const char *, const char *));
EXT (void strmfn (char *, const char *, const char *, const char *, const char *));
EXT (void strmfp (char *, const char *, const char *));
EXT (void strsfn (const char *, char *, char *, char *, char *));
EXT (void strsrt (char **, int_));
EXT (void swab (const char *, char *, size_t));
EXT (void swmem (void *, void *, size_t));

#endif
