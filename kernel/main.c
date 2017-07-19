/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#include <kernel/init.h>
#include <kernel/thread.h>
#include <kernel/options.h>
#include <multiboot2.h>
#include <stdio.h>
#include <string.h>

/*
** Goes through the multiboot structure, printing and evaluating it's content.
**
** TODO: Put this in a multiboot.c compilation  unit.
*/
static void
multiboot_load(uintptr mb_addr)
{
	struct multiboot_tag *tag;

	printf("Multiboot\n");
	tag = (struct multiboot_tag *)(mb_addr + 8);
	while (tag->type != MULTIBOOT_TAG_TYPE_END)
	{
		switch (tag->type)
		{
		case MULTIBOOT_TAG_TYPE_CMDLINE:
			printf("\tArguments: [%s]\n", ((struct multiboot_tag_string *)tag)->string);
			options_parse_command_line(((struct multiboot_tag_string *)tag)->string);
			break;
		}
		tag = (struct multiboot_tag *)((uchar *)tag + ((tag->size + 7) & ~7));
	}
	printf("\n");
}

/*
** Common entry point of the kernel.
*/
int
kernel_main(uintptr mb_addr)
{
	/* Create the boot thread */
	thread_init();

	/* Super super early hooks goes first. */
	kernel_init_level(CHAOS_INIT_LEVEL_EARLIEST, CHAOS_INIT_LEVEL_ARCH_EARLY - 1);

	/* Then goes early arch and platform stuff */
	kernel_init_level(CHAOS_INIT_LEVEL_ARCH_EARLY, CHAOS_INIT_LEVEL_PLATFORM_EARLY - 1);
	kernel_init_level(CHAOS_INIT_LEVEL_PLATFORM_EARLY, CHAOS_INIT_LEVEL_PMM - 1);

	/* Load the multiboot structure */
	multiboot_load(mb_addr);

	/* Initialize the memory management */
	kernel_init_level(CHAOS_INIT_LEVEL_PMM, CHAOS_INIT_LEVEL_VMM - 1);
	kernel_init_level(CHAOS_INIT_LEVEL_VMM, CHAOS_INIT_LEVEL_ARCH - 1);

	/* It's time to initialize arch and platform */
	kernel_init_level(CHAOS_INIT_LEVEL_ARCH, CHAOS_INIT_LEVEL_PLATFORM - 1);
	kernel_init_level(CHAOS_INIT_LEVEL_PLATFORM, CHAOS_INIT_LEVEL_LATEST);

	/* Drivers hooks would go there */

	/* Print hello message */
	printf("\nWelcome to ChaOS\n\n");

	thread_dump();

	/* We're now ready to go on */
	thread_become_idle();

	return (0);
}
