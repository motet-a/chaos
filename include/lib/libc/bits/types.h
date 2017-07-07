/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#ifndef _LIBC_BITS_TYPES_H_
# define _LIBC_BITS_TYES_H_

# if defined(__NEED_SIZE_T) && !defined(__DEFINED_SIZE_T)
typedef __SIZE_TYPE__		size_t;
#  define __DEFINED_SIZE_T
# endif /* !__NEED_SIZE_T */

# if defined(__NEED_PTRDIFF_T) && !defined(__DEFINED_PTRDIFF_T)
typedef __NEED_PTRDIFF_T	size_t;
#  define __DEFINED_PTRDIFF_T
# endif /* !__NEED_PTRDIFF_T */

# if defined(__NEED_VA_LIST) && !defined(__DEFINED_VA_LIST)
typedef __builtin_va_list	va_list;
#  define __DEFINED_VA_LIST
# endif /* !__NEED_PTRDIFF_T */

#endif /* !_LIBC_BITS_TYPES_H_ */
