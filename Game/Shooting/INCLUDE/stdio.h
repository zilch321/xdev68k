/*
 * PROJECT C Library, X68000 PROGRAMMING INTERFACE DEFINITION
 * --------------------------------------------------------------------
 * This file is written by the Project C Library Group,  and completely
 * in public domain. You can freely use, copy, modify, and redistribute
 * the whole contents, without this notice.
 * --------------------------------------------------------------------
 * $Id: stdio.h,v 1.6 1993/08/16 13:31:43 mura Exp $
 */

#ifndef __stdio_h__
#define __stdio_h__

#ifndef __cdecl_h__
#include <cdecl.h>
#endif

#ifndef __limits_h__
#include <limits.h>
#endif

#ifndef __va_list_defined__
#define __va_list_defined__
typedef char *va_list;
#endif

#ifndef __size_t_defined__
#define __size_t_defined__
typedef unsigned int_ size_t;
#endif

typedef long fpos_t;

typedef struct _stdbuf {	/* exactly 36bytes */
    int_ _cnt;
    int_ _bufsiz;
    int_ _flag;
    int_ _file;
    int_ _nback;
    unsigned char *_ptr;
    unsigned char *_base;
    unsigned char _pback[4];
    unsigned char _nbuff[4];
} FILE;

#ifndef NULL
#define NULL ((void *) 0)
#endif

#define _IOFBF       0x0000
#define _IOLBF       0x0001
#define _IONBF       0x0002

#define _IOREAD      0x0004
#define _IOWRITE     0x0008
#define _IOAPPEND    0x0010
#define _IOTRUNC     0x0020
#define _IOCREAT     0x0040
#define _IOBIN       0x0080
#define _IOFREE      0x0100
#define _IOEOF       0x0200
#define _IOERR       0x0400
#define _IOR         0x0800
#define _IOW         0x1000
#define _IOAPPLS     0x2000
#define _IOEMU       0x4000

#define _IOUPD       (_IOREAD | _IOWRITE)
#define _IOBINARY    (_IOBIN)   /* for compatibility */
#define _IOTEXT      (0)        /* for compatibility */
#define _IOWRT       (_IOWRITE) /* for compatibility */
#define _IOMYBUF     (_IOFREE)  /* for compatibility */

#define SEEK_SET     0
#define SEEK_CUR     1
#define SEEK_END     2

#define BUFSIZ       4096
#define EOF          (-1)
#define FOPEN_MAX    OPEN_MAX
#define FILENAME_MAX PATH_MAX
#define L_tmpnam     PATH_MAX
#define L_ctermid    64
#define L_cuserid    64
#define P_tmpdir     "./"
#define TMP_MAX      456976

#define stdin       (&_iob[0])
#define stdout      (&_iob[1])
#define stderr      (&_iob[2])
#define stdaux      (&_iob[3])
#define stdprn      (&_iob[4])

extern struct _stdbuf _iob[];

EXT (FILE *fdopen (int_, const char *));
EXT (FILE *fopen (const char *, const char *));
EXT (FILE *freopen (const char *, const char *, FILE *));
EXT (FILE *popen (const char *, const char *));
EXT (FILE *tmpfile (void_));
EXT (char *fgets (char *, int_, FILE *));
EXT (char *gets (char *));
EXT (char *tempnam (const char *, const char *));
EXT (char *tmpnam (char *));
EXT (int_ eprintf (const char * dotdot_));
EXT (int_ fclose (FILE *));
EXT (int_ fcloseall (void_));
EXT (int_ feof (FILE *));
EXT (int_ ferror (FILE *));
EXT (int_ fflush (FILE *));
EXT (int_ fgetc (FILE *));
EXT (int_ fgetpos (FILE *, fpos_t *));
EXT (int_ fileno (FILE *));
EXT (int_ flushall (void_));
EXT (int_ fprintf (FILE *, const char * dotdot_));
EXT (int_ fputc (int_, FILE *));
EXT (int_ fputs (const char *, FILE *));
EXT (int_ fscanf (FILE *, const char * dotdot_));
EXT (int_ fseek (FILE *, long, int_));
EXT (int_ fsetpos (FILE *, const fpos_t *));
EXT (int_ getchar (void_));
EXT (int_ getw (FILE *));
EXT (int_ pclose (FILE *));
EXT (int_ printf (const char * dotdot_));
EXT (int_ putchar (int_));
EXT (int_ puts (const char *));
EXT (int_ putw (int_, FILE *));
EXT (int_ remove (const char *));
EXT (int_ rename (const char *, const char *));
EXT (int_ scanf (const char * dotdot_));
EXT (int_ setvbuf (FILE *, char *, int_, size_t));
EXT (int_ sprintf (char *, const char * dotdot_));
EXT (int_ sscanf (const char *, const char * dotdot_));
EXT (int_ ungetc (int_, FILE *));
EXT (int_ vfprintf (FILE *, const char *, va_list));
EXT (int_ vfscanf (FILE *, const char *, va_list));
EXT (int_ vprintf (const char *, va_list));
EXT (int_ vscanf (const char *, va_list));
EXT (int_ vsprintf (char *, const char *, va_list));
EXT (int_ vsscanf (const char *, const char *, va_list));
EXT (long ftell (FILE *));
EXT (size_t fread (void *, size_t, size_t, FILE *));
EXT (size_t fwrite (const void *, size_t, size_t, FILE *));
EXT (void clearerr (FILE *));
EXT (void fmode (FILE *, int_));
EXT (void perror (const char *));
EXT (void rewind (FILE *));
EXT (void setbuf (FILE *, char *));

#ifdef __NO_STDIO_INLINE__

#define getc fgetc
#define putc fputc

#else

#define getc(fp) \
    (--(fp)->_cnt >= 0 ? ((int_) *(fp)->_ptr++) : (fgetc (fp)))
#define putc(c, fp) \
    (--(fp)->_cnt >= 0 ? ((int_) *(fp)->_ptr++ = (c)) : (fputc ((c), (fp))))

#define feof(fp)     ((fp)->_flag & _IOEOF)
#define ferror(fp)   ((fp)->_flag & _IOERR)
#define fileno(fp)   ((fp)->_file)
#define getchar()    (fgetc (stdin))
#define putchar(c)   (fputc ((c), stdout))

#endif

#endif
