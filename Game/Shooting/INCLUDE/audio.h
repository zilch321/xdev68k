/*
 * PROJECT C Library, X68000 PROGRAMMING INTERFACE DEFINITION
 * --------------------------------------------------------------------
 * This file is written by the Project C Library Group,  and completely
 * in public domain. You can freely use, copy, modify, and redistribute
 * the whole contents, without this notice.
 * --------------------------------------------------------------------
 * based on the contribution from AOI (MAKI aoi).
 * --------------------------------------------------------------------
 * $Id: audio.h,v 1.1.1.1 1993/05/24 15:00:00 
 */

#ifndef __audio_h__
#define __audio_h__

#ifndef __cdecl_h__
#include <cdecl.h>
#endif

EXT (int a_stat (void));
EXT (void a_cont (void));
EXT (void a_end (void));
EXT (void a_play (const void *, int, int, int, int));
EXT (void a_rec (void *, int, int, int));
EXT (void a_stop (void));

#endif
