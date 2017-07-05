/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#ifndef _CHAOSDEF_H_
# define _CHAOSDEF_H_

/*
** Define a usefull set of macros that acts like keywords that are not
** available in c89.
*/
# define restrict		__restrict__
# define asm			__asm__
# define inline			__inline__
# define __pure			__attribute__((pure))
# define __const		__attribute__((const))
# define __cold			__attribute__((cold))
# define __hot			__attribute__((hot))
# define __used			__attribute__((used))
# define __unused		__attribute__((unused))
# define __packed		__attribute__((packed))

/* Determine the wordsize from the preprocessor defines.  */
# if defined __x86_64__ && !defined __ILP32__
#  define __WORDSIZE		64
# else
#  define __WORDSIZE		32
# endif /* defined __x86_64__ && !defined __ILP32__ */

/* Defines some shortcuts types. */
typedef unsigned int		uint;
typedef unsigned short		ushort;
typedef unsigned char		uchar;
typedef unsigned long		ulong;
typedef unsigned long long	ulonglong;

/* Defines some size-dependant types. */
typedef signed char		int8;
typedef signed short		int16;
typedef signed int		int32;
# if __WORDSIZE == 64
typedef signed long		int64;
typedef signed long		intptr;
# else
typedef signed long long	int64;
typedef signed int		intptr;
# endif /* __WORDSIZE == 64 */

typedef unsigned char		uint8;
typedef unsigned short		uint16;
typedef unsigned int		uint32;
# if __WORDSIZE == 64
typedef unsigned long		uint64;
typedef unsigned long		uintptr;
# else
typedef unsigned long long	uint64;
typedef unsigned int		uintptr;
# endif /* __WORDSIZE == 64 */

typedef enum
{
  false				= 0,
  true				= 1
}				bool;

#endif // !_CHAOSDEF_H_
