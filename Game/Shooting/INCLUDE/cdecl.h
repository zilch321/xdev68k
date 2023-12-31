/*
 * PROJECT C Library, X68000 PROGRAMMING INTERFACE DEFINITION
 * --------------------------------------------------------------------
 * This file is written by the Project C Library Group,  and completely
 * in public domain. You can freely use, copy, modify, and redistribute
 * the whole contents, without this notice.
 * --------------------------------------------------------------------
 * $Id: cdecl.h,v 1.3 1993/06/09 06:23:09 mura Exp $
 */

#ifndef __cdecl_h__
#define __cdecl_h__

/*
** LibC Identifier
*/
#ifndef __LIBC__
# define __LIBC__ 1
#endif

/*
** GNU C, GNU C++ Compilers can treat function attributes (const
** function, and volatile function).
*/

#if !defined (__GNUC__) && !defined (__GNUG__)
# ifndef __const
#  define __const
#  define __volatile
# endif
#endif

/*
** All of XC, GNU C, and GNU C++ Compilers can treat zero size array.
** But their implementations differ with each other.
*/

#if defined (__GNUC__) || defined (__GNUG__)
# ifndef _ZEROARRAY
#  define _ZEROARRAY 0
# endif
#else
# ifndef _ZEROARRAY
#  define _ZEROARRAY
# endif
#endif

/*
** GNU C, GNU-C++ Compiler can treat 16bit integer as the default
** size of int. But the interfaces with libc must be 32bit always.
*/

#ifdef __MSHORT__
# ifndef int_
#  define int_ long
# endif
#else
# ifndef int_
#  define int_ int
# endif
#endif

/*
** In ANSI C, (void) means no argument, but in C++, () should be
** used instead. And in ANSI C, ", ..." means variable argument,
** but in C++, leading comma should be omitted.
*/

#ifdef __cplusplus
# ifndef void_
#  define void_
#  define dotdot_ ...
# endif
#else
# ifndef void_
#  define void_ void
#  define dotdot_ , ...
# endif
#endif

/*
** In C++, function name will be mangled in the compiler dependent
** way. To link normal C functions, 'extern "C" {}' will be needed
** with the function prototypes.
**
** many spaces are inserted between *extern* and *ptype* to avoid
** a XC v2.0 preprocessor bug.
*/

#ifdef __cplusplus
# define EXT(ptype) extern "C" ptype;
#else
# define EXT(ptype) extern     ptype
#endif

#endif
