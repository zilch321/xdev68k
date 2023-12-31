/*
 * PROJECT C Library, X68000 PROGRAMMING INTERFACE DEFINITION
 * --------------------------------------------------------------------
 * This file is written by the Project C Library Group,  and completely
 * in public domain. You can freely use, copy, modify, and redistribute
 * the whole contents, without this notice.
 * --------------------------------------------------------------------
 * $Id: utime.h,v 1.1.1.1 1993/04/18 16:13:49 mura Exp $
 */

#ifndef __utime_h__
#define __utime_h__

#ifndef __cdecl_h__
#include <cdecl.h>
#endif

#ifndef __sys_types_h__
#include <sys/types.h>
#endif

struct utimbuf {
    time_t actime;
    time_t modtime;
};

EXT (int_ utime (const char *, struct utimbuf *));

#endif
