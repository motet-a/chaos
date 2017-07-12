/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#ifndef _LIB_IO_H_
# define _LIB_IO_H_

typedef char	(*io_getc_cb)(void);
typedef int	(*io_putc_cb)(int);
typedef int	(*io_puts_cb)(char const *);

struct		io_output_callbacks
{
	io_putc_cb putc;
	io_puts_cb puts;
};

struct		io_input_callbacks
{
	io_getc_cb getc;
};

enum		io_output_types
{
	IO_OUTPUT_SERIAL,
	IO_OUTPUT_CONSOLE,
};

int	io_putc(int c);
int	io_puts(char const *str);
char	io_getc(void);

void	register_io_output_callbacks(struct io_output_callbacks *, enum io_output_types);
void	register_io_input_callbacks(struct io_input_callbacks *);

#endif /* !_LIB_IO_H_ */
