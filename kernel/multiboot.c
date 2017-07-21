/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#include <kernel/options.h>
#include <kernel/multiboot.h>
#include <multiboot2.h>
#include <stdio.h>

/*
** Goes through the multiboot structure, printing and evaluating it's content.
*/
void
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

