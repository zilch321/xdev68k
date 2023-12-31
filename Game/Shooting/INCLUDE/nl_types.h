/*
 * PROJECT C Library, X68000 PROGRAMMING INTERFACE DEFINITION
 * --------------------------------------------------------------------
 * This file is written by the Project C Library Group,  and completely
 * in public domain. You can freely use, copy, modify, and redistribute
 * the whole contents, without this notice.
 * --------------------------------------------------------------------
 * $Id: nl_types.h,v 1.1.1.1 1993/04/18 16:13:25 mura Exp $
 */

/*
** PLEASE DO NOT USE THIS HEADER FILE !!!
** ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
** The following features will be supported in future, but not
** supprted now.  If you want to use the features, please make
** the following interfaces, and contribute them to us.
*/

#ifndef __nl_types_h__
#define __nl_types_h__

#ifndef __cdecl_h__
#include <cdecl.h>
#endif

#define NL_SETD 0

struct _nl_message {
    int_ nl_msgid;
    struct _nl_message *nl_next;
    unsigned char nl_text[_ZEROARRAY];
};

struct _nl_set {
    int_ nl_setid;
    struct _nl_set *nl_nexts;
    struct _nl_message *nl_top;
};

typedef struct _nl_set *nl_catd;
typedef int_ nl_item;

EXT (char *catgets (nl_catd, int_, int_, char *));
EXT (int_ catclose (nl_catd));
EXT (nl_catd catopen (const char *, int_));

#endif
