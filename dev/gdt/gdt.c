/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#include <dev/dev.h>
#include <dev/gdt.h>
#include <asm.h>

static struct gdt_entry gdt[GDT_SIZE] __aligned(16) =
{
	[GDT_NULL_ENTRY]	= GDT_ENTRY(0x0, 0x0, 0x0),
	[GDT_KERNEL_CODE]	= GDT_ENTRY(0xC09A, 0x0, 0xFFFFFFFF),
	[GDT_KERNEL_DATA]	= GDT_ENTRY(0xC092, 0x0, 0xFFFFFFFF),
	[GDT_USER_CODE]		= GDT_ENTRY(0xC0FA, 0x0, 0xFFFFFFFF),
	[GDT_USER_DATA]		= GDT_ENTRY(0xC0F2, 0x0, 0xFFFFFFFF)
};

static struct table_desc_ptr gdt_ptr;

static void
gdt_init(enum init_level il __unused)
{
	/* Ensure the gdt is 16-bytes aligned */
	assert_eq((uintptr)gdt & 0xF, 0);

	gdt_ptr.limit = sizeof(gdt) - 1;
	gdt_ptr.base = (uintptr)&gdt;

	gdt_flush(&gdt_ptr);
}

NEW_DEV_HOOK(gdt, &gdt_init, CHAOS_INIT_LEVEL_DEV_EARLY);
