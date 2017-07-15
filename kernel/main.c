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
#include <stdio.h>

typedef struct {
	uint32 total_size;
} multiboot_info_t;

extern const multiboot_info_t *multiboot_info;

/*
** Common entry point of the kernel.
*/
int
kernel_main()
{
	/* Super super early hooks goes first. */
	kernel_init_level(CHAOS_INIT_LEVEL_EARLIEST, CHAOS_INIT_LEVEL_ARCH_EARLY - 1);

	/* Then goes early arch and platform stuff */
	kernel_init_level(CHAOS_INIT_LEVEL_ARCH_EARLY, CHAOS_INIT_LEVEL_PLATFORM_EARLY - 1);
	kernel_init_level(CHAOS_INIT_LEVEL_PLATFORM_EARLY, CHAOS_INIT_LEVEL_ARCH - 1);

	/* Initialize the memory management */
	pmm_init();

	/* It's time to initialize arch and platform */
	kernel_init_level(CHAOS_INIT_LEVEL_ARCH, CHAOS_INIT_LEVEL_PLATFORM - 1);
	kernel_init_level(CHAOS_INIT_LEVEL_PLATFORM, CHAOS_INIT_LEVEL_LATEST);

	/* Drivers hooks would go there */

	/* We're now ready to go on */
	printf("\nWelcome to ChaOS\n\n");
	printf("mbi %p\n", multiboot_info);
	return (0);
}
