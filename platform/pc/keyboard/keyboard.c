/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#include <kernel/init.h>
#include <arch/x86/asm.h>
#include <arch/x86/devices/keyboard.h>
#include <lib/interrupts.h>
#include <stdio.h>

/*
** This is mainly here for debug until we get some better keyboard handling
*/
static char const fr_azerty_charset[128] =
{
  0,
  [16] = 'a',
  [17] = 'z',
  [18] = 'e',
  [19] = 'r',
  [20] = 't',
  [21] = 'y',
  [22] = 'u',
  [23] = 'i',
  [24] = 'o',
  [25] = 'p',
  [30] = 'q',
  [31] = 's',
  [32] = 'd',
  [33] = 'f',
  [34] = 'g',
  [35] = 'h',
  [36] = 'j',
  [37] = 'k',
  [38] = 'l',
  [39] = 'm',
  [44] = 'w',
  [45] = 'x',
  [46] = 'c',
  [47] = 'v',
  [48] = 'b',
  [49] = 'n',
};

static void
keyboard_int_handler(void)
{
	char code;

	code = inb(KEYBOARD_IO_PORT);
	if (code & 0x80) {
		code &= ~0x80;
		code = fr_azerty_charset[(unsigned)code];
		printf("Keyboard released: %c\n", code);
	}
	else {
		code = fr_azerty_charset[(uint)code];
		printf("Keyboard pressed: %c\n", code);
	}
}

static void
keyboard_init(enum init_level il __unused)
{
	register_int_handler(KEYBOARD_INT_HANDLER, &keyboard_int_handler);
}

NEW_INIT_HOOK(keyboard, &keyboard_init, CHAOS_INIT_LEVEL_DEV_EARLY);
