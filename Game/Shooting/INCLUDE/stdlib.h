/*
 * PROJECT C Library, X68000 PROGRAMMING INTERFACE DEFINITION
 * --------------------------------------------------------------------
 * This file is written by the Project C Library Group,  and completely
 * in public domain. You can freely use, copy, modify, and redistribute
 * the whole contents, without this notice.
 * --------------------------------------------------------------------
 * $Id: stdlib.h,v 1.6 1993/08/16 13:31:48 mura Exp $
 */

#ifndef __stdlib_h__
#define __stdlib_h__

#ifndef __cdecl_h__
#include <cdecl.h>
#endif

#ifndef __size_t_defined__
#define __size_t_defined__
typedef unsigned int_ size_t;
#endif

#ifndef __wchar_t_defined__
#define __wchar_t_defined__
typedef int_ wchar_t;
#endif

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define RAND_MAX     32767
#define MB_CUR_MAX   2

#define _MAX_DRVNO   26
#define _MAX_DRIVE   3
#define _MAX_PATH    64
#define _MAX_FNAME   19
#define _MAX_EXT     19

#define max(a, b) (((a) >= (b)) ? (a) : (b))
#define min(a, b) (((a) <= (b)) ? (a) : (b))

typedef struct {
    int_ quot;
    int_ rem;
} div_t;

typedef struct {
    long quot;
    long rem;
} ldiv_t;

typedef void (*onexit_t) (void_);

extern char *optarg;
extern int_ _getopt_no_ordering;
extern int_ optind;
extern int_ opterr;

#define uitoa ultoa

EXT (char *_fullentry (char *, const char *, size_t));
EXT (char *_fullpath (char *, const char *, size_t));
EXT (char *ecvt (double, int_, int_ *, int_ *));
EXT (char *fcvt (double, int_, int_ *, int_ *));
EXT (char *gcvt (double, int_, char *));
EXT (char *getenv (const char *));
EXT (char *getpass (const char *));
EXT (char *itoa (int_, char *, int_));
EXT (char *ltoa (long, char *, int_));
EXT (char *mktemp (char *));
EXT (char *ultoa (unsigned long, char *, int_));
EXT (div_t __const div (int_, int_));
EXT (double atof (const char *));
EXT (double drand (void_));
EXT (double drand48 (void_));
EXT (double erand48 (unsigned short[3]));
EXT (double strtod (const char *, char **));
EXT (int_ abs (int_));
EXT (int_ atexit (void (*) (void_)));
EXT (int_ atoi (const char *));
EXT (int_ brk (void *));
EXT (int_ clearenv (void_));
EXT (int_ getopt (int_, char *[], const char *));
EXT (int_ mblen (const char *, size_t));
EXT (int_ mbtowc (wchar_t *, const char *, size_t));
EXT (int_ mkstemp (char *));
EXT (int_ putenv (const char *));
EXT (int_ rand (void_));
EXT (int_ setenv (const char *, const char *, int_));
EXT (int_ system (const char *));
EXT (int_ wctomb (char *, wchar_t));
EXT (ldiv_t __const ldiv (long, long));
EXT (long atol (const char *));
EXT (long jrand48 (unsigned short[3]));
EXT (long labs (long));
EXT (long lrand48 (void_));
EXT (long mrand48 (void_));
EXT (long nrand48 (unsigned short[3]));
EXT (long strtol (const char *, char **, int_));
EXT (onexit_t onexit (onexit_t));
EXT (short atow (const char *));
EXT (short wabs (short));
EXT (size_t chkml (void_));
EXT (size_t sizmem (void_));
EXT (size_t mbstowcs (wchar_t *, const char *, size_t));
EXT (size_t wcstombs (char *, const wchar_t *, size_t));
EXT (unsigned int_ random (void_));
EXT (unsigned int_ srandom (unsigned int_));
EXT (unsigned long strtoul (const char *, char **, int_));
EXT (unsigned short *seed48 (unsigned short[3]));
EXT (void *bsearch (const void *, const void *, size_t, size_t, int_ (*) (const void *, const void *)));
EXT (void *calloc (size_t, size_t));
EXT (void *malloc (size_t));
EXT (void *memalign (size_t, size_t));
EXT (void *realloc (void *, size_t));
EXT (void *sbrk (int));
EXT (void *valloc (size_t));
EXT (void __volatile abort (void_));
EXT (void __volatile exit (int_));
EXT (void _makepath (char *, const char *, const char *, const char *, const char *));
EXT (void _splitpath (const char *, char *, char *, char *, char *));
EXT (void free (void *));
EXT (void qsort (void *, size_t, size_t, int_ (*) (const void *, const void *)));
EXT (void rbrk (void_));
EXT (void srand (unsigned int_));
EXT (void srand48 (long));
EXT (void unsetenv (const char *));

#ifndef __NO_STDLIB_INLINE__

#define abs(x)  ((x) >= 0 ? (int_) (x) : (int_) -(x))
#define labs(x) ((x) >= 0 ? (long) (x) : (long) -(x))
#define wabs(x) ((x) >= 0 ? (short) (x) : (short) -(x))

#endif

#endif
