/*
 * PROJECT C Library, X68000 PROGRAMMING INTERFACE DEFINITION
 * --------------------------------------------------------------------
 * This file is written by the Project C Library Group,  and completely
 * in public domain. You can freely use, copy, modify, and redistribute
 * the whole contents, without this notice.
 * --------------------------------------------------------------------
 * $Id: search.h,v 1.1.1.1 1993/04/18 16:13:31 mura Exp $
 */

/*
** PLEASE DO NOT USE THIS HEADER FILE !!!
** ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
** The following features will be supported in future, but not
** supprted now.  If you want to use the features, please make
** the following interfaces, and contribute them to us.
*/

#ifndef __search_h__
#define __search_h__

#ifndef __cdecl_h__
#include <cdecl.h>
#endif

#ifndef __sys_types_h__
#include <sys/types.h>
#endif

typedef enum {
    FIND,
    ENTER,
} ACTION;

typedef enum {
    preorder,
    postorder,
    endorder,
    leaf,
} VISIT;

typedef struct {
    char *key;
    char *data;
} ENTRY;

EXT (ENTRY *hsearch (ENTRY, ACTION));
EXT (int_ hcreate (unsigned int_));
EXT (void *bsearch (const void *, const void *, size_t, size_t, int_ (*) (const void *, const void *)));
EXT (void *lfind (const void *, const void *, size_t *, size_t, int_ (*) (const void *, const void *)));
EXT (void *lsearch (const void *, const void *, size_t *, size_t, int_ (*) (const void *, const void *)));
EXT (void *tdelete (const void *, const void **, int_ (*) (const void *, const void *)));
EXT (void *tfind (const void *, const void **, int_ (*) (const void *, const void *)));
EXT (void *tsearch (const void *, const void **, int_ (*) (const void *, const void *)));
EXT (void hdestroy (void_));
EXT (void twalk (const void **, void (*) (const void *, const VISIT, const int_)));

#endif
