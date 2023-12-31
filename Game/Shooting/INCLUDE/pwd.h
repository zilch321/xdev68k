/*
 * PROJECT C Library, X68000 PROGRAMMING INTERFACE DEFINITION
 * --------------------------------------------------------------------
 * This file is written by the Project C Library Group,  and completely
 * in public domain. You can freely use, copy, modify, and redistribute
 * the whole contents, without this notice.
 * --------------------------------------------------------------------
 * $Id: pwd.h,v 1.1.1.1 1993/04/18 16:13:29 mura Exp $
 */

#ifndef __pwd_h__
#define __pwd_h__

#ifndef __cdecl_h__
#include <cdecl.h>
#endif

#ifndef __sys_types_h__
#include <sys/types.h>
#endif

#define _PATH_PASSWD "/etc/passwd"

struct passwd {
    char *pw_name;
    char *pw_passwd;
    uid_t pw_uid;
    gid_t pw_gid;
    char *pw_gecos;
    char *pw_dir;
    char *pw_shell;
};

EXT (struct passwd *getpwent (void_));
EXT (struct passwd *getpwnam (const char *));
EXT (struct passwd *getpwuid (uid_t));
EXT (void endpwent (void_));
EXT (void setpwent (void_));

#endif
