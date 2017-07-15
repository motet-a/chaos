/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#include <kernel/init.h>
#include <kernel/pmm.h>
#include <kernel/vmm.h>
#include <multiboot2.h>
#include <stdio.h>
#include <string.h>

struct options {
	bool test;
};

static struct options options = {0};

static struct options
parse_command_line(char const *string) {
	printf("Multiboot command line: %s\n", string);

	return (struct options){
		.test = strstr(string, "test"),
	};
}

/*
** This should probably go elsewhere, here only for example purposes.
*/
static void
multiboot_load(uintptr mb_addr)
{
	struct multiboot_tag *tag;

	tag = (struct multiboot_tag *)(mb_addr + 8);
	while (tag->type != MULTIBOOT_TAG_TYPE_END)
	{
		switch (tag->type)
		{
		case MULTIBOOT_TAG_TYPE_CMDLINE:
			options = parse_command_line(((struct multiboot_tag_string *)tag)->string);
			break;
		}
		tag = (struct multiboot_tag *)((uchar *)tag + ((tag->size + 7) & ~7));
	}
}

static void test() {
	printf("Running tests...\n");
	pmm_test();
	string_test();
	printf("Done.\n");
}

/*
** Common entry point of the kernel.
*/
int
kernel_main(uintptr mb_addr)
{
	/* Super super early hooks goes first. */
	kernel_init_level(CHAOS_INIT_LEVEL_EARLIEST, CHAOS_INIT_LEVEL_ARCH_EARLY - 1);

	/* Then goes early arch and platform stuff */
	kernel_init_level(CHAOS_INIT_LEVEL_ARCH_EARLY, CHAOS_INIT_LEVEL_PLATFORM_EARLY - 1);
	kernel_init_level(CHAOS_INIT_LEVEL_PLATFORM_EARLY, CHAOS_INIT_LEVEL_ARCH - 1);

	multiboot_load(mb_addr);

	/* Initialize the memory management */
	pmm_init();
	vmm_init();

	/* It's time to initialize arch and platform */
	kernel_init_level(CHAOS_INIT_LEVEL_ARCH, CHAOS_INIT_LEVEL_PLATFORM - 1);
	kernel_init_level(CHAOS_INIT_LEVEL_PLATFORM, CHAOS_INIT_LEVEL_LATEST);

	/* Drivers hooks would go there */

	if (options.test) {
		test();
	}

	/* We're now ready to go on */
	printf("\nWelcome to ChaOS\n\n");

	return (0);
}
