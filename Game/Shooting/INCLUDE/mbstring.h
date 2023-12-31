/*
 * PROJECT C Library, X68000 PROGRAMMING INTERFACE DEFINITION
 * --------------------------------------------------------------------
 * This file is written by the Project C Library Group,  and completely
 * in public domain. You can freely use, copy, modify, and redistribute
 * the whole contents, without this notice.
 * --------------------------------------------------------------------
 * $Id: mbstring.h,v 1.2 1993/04/30 19:09:08 mura Exp $
 */

#ifndef __mbstring_h__
#define __mbstring_h__

#ifndef __cdecl_h__
#include <cdecl.h>
#endif

#ifndef __mbctype_h__
#include <mbctype.h>
#endif

#ifndef __size_t_defined__
#define __size_t_defined__
typedef unsigned int_ size_t;
#endif

#ifndef NULL
#define NULL ((void *) 0)
#endif

#define _MBC_SINGLE   0
#define _MBC_LEAD     1
#define _MBC_TRAIL    2
#define _MBC_ILLEGAL -1

#define _MBIS16(c) ((c) & 0xff00)

EXT (int_ __const mbbtombc (int_));
EXT (int_ __const mbbtype (unsigned char, int_));
EXT (int_ __const mbcjistojms (int_));
EXT (int_ __const mbcjmstojis (int_));
EXT (int_ __const mbctombb (int_));
EXT (int_ mbsbtype (const unsigned char *, size_t));
EXT (int_ mbscmp (const unsigned char *, const unsigned char *));
EXT (int_ mbsicmp (const unsigned char *, const unsigned char *));
EXT (int_ mbsncmp (const unsigned char *, const unsigned char *, size_t));
EXT (int_ mbsnextc (const unsigned char *));
EXT (int_ mbsnicmp (const unsigned char *, const unsigned char *, size_t));
EXT (size_t mbscspn (const unsigned char *, const unsigned char *));
EXT (size_t mbslen (const unsigned char *));
EXT (size_t mbsnbcnt (const unsigned char *, size_t));
EXT (size_t mbsnccnt (const unsigned char *, size_t));
EXT (size_t mbsspn (const unsigned char *, const unsigned char *));
EXT (unsigned char *mbscat (unsigned char *, const unsigned char *));
EXT (unsigned char *mbschr (const unsigned char *, int_));
EXT (unsigned char *mbscpy (unsigned char *, const unsigned char *));
EXT (unsigned char *mbsdec (const unsigned char *, unsigned char *));
EXT (unsigned char *mbsdup (const unsigned char *));
EXT (unsigned char *mbsinc (unsigned char *));
EXT (unsigned char *mbslwr (unsigned char *));
EXT (unsigned char *mbsncat (unsigned char *, const unsigned char *, size_t));
EXT (unsigned char *mbsncpy (unsigned char *, const unsigned char *, size_t));
EXT (unsigned char *mbsninc (const unsigned char *, size_t));
EXT (unsigned char *mbsnset (unsigned char *, int_, size_t));
EXT (unsigned char *mbspbrk (const unsigned char *, const unsigned char *));
EXT (unsigned char *mbsrchr (const unsigned char *, int_));
EXT (unsigned char *mbsrev (unsigned char *));
EXT (unsigned char *mbsset (unsigned char *, int_));
EXT (unsigned char *mbsspnp (const unsigned char *, const unsigned char *));
EXT (unsigned char *mbsstr (const unsigned char *, const unsigned char *));
EXT (unsigned char *mbstok (unsigned char *, const unsigned char *));
EXT (unsigned char *mbsupr (unsigned char *));

#endif
