/*
 * PROJECT C Library, X68000 PROGRAMMING INTERFACE DEFINITION
 * --------------------------------------------------------------------
 * This file is written by the Project C Library Group,  and completely
 * in public domain. You can freely use, copy, modify, and redistribute
 * the whole contents, without this notice.
 * --------------------------------------------------------------------
 * $Id: grp.h,v 1.1.1.1 1993/04/18 16:13:06 mura Exp $
 */

#ifndef __grp_h__
#define __grp_h__

#ifndef __cdecl_h__
#include <cdecl.h>
#endif

#ifndef __sys_types_h__
#include <sys/types.h>
#endif

#define _PATH_GROUP "/etc/group"

struct group {
    char *gr_name;
    char *gr_passwd;
    gid_t gr_gid;
    char **gr_mem;
};

EXT (struct group *getgrent (void_));
EXT (struct group *getgrgid (gid_t));
EXT (struct group *getgrnam (const char *));
EXT (void endgrent (void_));
EXT (void setgrent (void_));

#endif
