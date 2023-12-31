/*
 * PROJECT C Library, X68000 PROGRAMMING INTERFACE DEFINITION
 * --------------------------------------------------------------------
 * This file is written by the Project C Library Group,  and completely
 * in public domain. You can freely use, copy, modify, and redistribute
 * the whole contents, without this notice.
 * --------------------------------------------------------------------
 * $Id: errno.h,v 1.1.1.1 1993/04/18 16:13:01 mura Exp $
 */

#ifndef __errno_h__
#define __errno_h__

#ifndef __cdecl_h__
#include <cdecl.h>
#endif

#define EDOM         1
#define ERANGE       2
#define E2BIG        3
#define EACCES       4
#define EAGAIN       5
#define EBADF        6
#define EBUSY        7
#define ECHILD       8
#define EDEADLK      9
#define EEXIST       10
#define EFAULT       11
#define EFBIG        12
#define EINTR        13
#define EINVAL       14
#define EIO          15
#define EISDIR       16
#define ELOOP        17
#define EMFILE       18
#define EMLINK       19
#define ENAMETOOLONG 20
#define ENFILE       21
#define ENODEV       22
#define ENOENT       23
#define ENOEXEC      24
#define ENOLCK       25
#define ENOMEM       26
#define ENOSPC       27
#define ENOTBLK      28
#define ENOSYS       29
#define ENOTDIR      30
#define ENOTEMPTY    31
#define ENOTTY       32
#define ENXIO        33
#define EPERM        34
#define EPIPE        35
#define EROFS        36
#define ESPIPE       37
#define ETXTBSY      38
#define ESRCH        39
#define EXDEV        40
#define EDEVFS       41
#define EWOULDBLOCK  EDEADLK

extern char *sys_errlist[];
extern int_ sys_nerr;
extern volatile int_ errno;

#endif
