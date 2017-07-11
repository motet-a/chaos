/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#ifndef _CHAOS_DEF_H_
# define _CHAOS_DEF_H_

# include <stddef.h>
# include <stdint.h>
# include <stdbool.h>
# include <stdarg.h>

/*
** Define a useful set of macros that act like keywords that are not
** available in c11.
*/
# define inline			__inline
# define asm			__asm__
# define restrict		__restrict
# define __pure			__attribute__((pure))
# define __const		__attribute__((const))
# define __cold			__attribute__((cold))
# define __hot			__attribute__((hot))
# define __used			__attribute__((used))
# define __unused		__attribute__((unused))
# define __packed		__attribute__((packed))
# define __weak			__attribute__((weak))
# define __aligned(x)		__attribute__((aligned (x)))
# define __section(s)		__attribute__((section (s)))
# define __noreturn		__attribute__((noreturn))

# include <debug.h>

/* Defines some shortcuts types. */
typedef unsigned char		uchar;
typedef unsigned short		ushort;
typedef unsigned int		uint;
typedef unsigned long		ulong;
typedef intmax_t		intmax;
typedef uintmax_t		uintmax;

/* Defines some shortcuts for size-dependant types. */
typedef int8_t			int8;
typedef int16_t			int16;
typedef int32_t			int32;
typedef int64_t			int64;
typedef intptr_t		intptr;

typedef uint8_t			uint8;
typedef uint16_t		uint16;
typedef uint32_t		uint32;
typedef uint64_t		uint64;
typedef uintptr_t		uintptr;

#endif /* !_CHAOS_DEF_H_ */
