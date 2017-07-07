/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#ifndef _LIBC_STDARG_H_
# define _LIBC_STDARG_H_

# define __NEED_VA_LIST
# include <bits/types.h>

# define va_start(v, l)		__builtin_va_start(v, l)
# define va_arg(v, l)		__builtin_va_arg(v, l)
# define va_copy(v, l)		__builtin_va_copy(v, l)
# define va_end(v, l)		__builtin_va_end(v, l)

#endif /* !_LIBC_STDARG_H_ */
