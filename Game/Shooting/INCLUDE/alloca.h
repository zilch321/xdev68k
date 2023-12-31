/*
 * PROJECT C Library, X68000 PROGRAMMING INTERFACE DEFINITION
 * --------------------------------------------------------------------
 * This file is written by the Project C Library Group,  and completely
 * in public domain. You can freely use, copy, modify, and redistribute
 * the whole contents, without this notice.
 * --------------------------------------------------------------------
 * $Id: alloca.h,v 1.1.1.1 1993/04/18 16:12:50 mura Exp $
 */

#ifndef __alloca_h__
#define __alloca_h__

#if !defined (__GNUC__) && !defined (__GNUG__)
#error You lose. This file can be compiled only by GNU-C compiler.
#endif

#ifndef __cdecl_h__
#include <cdecl.h>
#endif

#ifdef alloca
#undef alloca
#endif

#ifdef __ALLOCA_STACK_CHECK__
#ifdef __cplusplus
#define alloca(x)						\
    ({								\
	extern void *_ssta;					\
	extern "C" { __volatile void _stack_over (); };		\
	register void *_sp ("a7");				\
	asm volatile ("" : "=a" (_sp) : );			\
	if (_sp - (x) < _ssta) _stack_over ();			\
	__builtin_alloca (x);					\
    })
#else
#define alloca(x)						\
    ({								\
	extern void *_ssta;					\
	extern __volatile void _stack_over ();			\
	register void *_sp ("a7");				\
	asm volatile ("" : "=a" (_sp) : );			\
	if (_sp - (x) < _ssta) _stack_over ();			\
	__builtin_alloca (x);					\
    })
#endif
#else
#define alloca __builtin_alloca
#endif

#endif
