/*
 * PROJECT C Library, X68000 PROGRAMMING INTERFACE DEFINITION
 * --------------------------------------------------------------------
 * This file is written by the Project C Library Group,  and completely
 * in public domain. You can freely use, copy, modify, and redistribute
 * the whole contents, without this notice.
 * --------------------------------------------------------------------
 * $Id: dirent.h,v 1.3 1993/06/22 15:07:41 mura Exp $
 */

#ifndef __dirent_h__
#define __dirent_h__

#ifndef __cdecl_h__
#include <cdecl.h>
#endif

#ifndef __limits_h__
#include <limits.h>
#endif

#ifndef __sys_types_h__
#include <sys/types.h>
#endif

#ifndef __sys_dos_h__
#include <sys/dos.h>
#endif

#define MAXNAMLEN PATH_MAX

struct dirent {
    ino_t d_ino;
    int d_reclen;
    int d_namlen;
    char d_name[NAME_MAX + 1];
};

struct _dirdesc {
    struct _filbuf filesbuf;
    long loc;
    long filemax;
    struct dirent *dp;
};

typedef struct _dirdesc DIR;

EXT (DIR *opendir (const char *));
EXT (int_ rewinddir (DIR *));
EXT (int_ seekdir (DIR *, long));
EXT (long telldir (DIR *));
EXT (struct dirent *readdir (DIR *));
EXT (void closedir (DIR *));

#endif
