/*
 * PROJECT C Library, X68000 PROGRAMMING INTERFACE DEFINITION
 * --------------------------------------------------------------------
 * This file is written by the Project C Library Group,  and completely
 * in public domain. You can freely use, copy, modify, and redistribute
 * the whole contents, without this notice.
 * --------------------------------------------------------------------
 * $Id: regexp.h,v 1.1.1.1 1993/04/18 16:13:30 mura Exp $
 */

/*
** PLEASE DO NOT USE THIS HEADER FILE !!!
** ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
** The following features will be supported in future, but not
** supprted now.  If you want to use the features, please make
** the following interfaces, and contribute them to us.
*/

#ifndef __regexp_h__
#define __regexp_h__

#ifndef __cdecl_h__
#include <cdecl.h>
#endif

extern char *loc1;
extern char *loc2;
extern char *locs;

EXT (char *compile (char *, char *, char *, int_));
EXT (int_ advance (char *, char *));
EXT (int_ step (char *, char *));

#endif
