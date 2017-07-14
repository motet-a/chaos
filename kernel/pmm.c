/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#include <kernel/pmm.h>
#include <string.h>
#include <stdio.h>

static uchar				frame_bitmap[FRAME_BITMAP_SIZE];

/*
** This is a pretty naive frame allocator using a bitmap to memorize which
** frames are free and which one are not.
**
** It can definitely be optimised, but that's not the point at this moment.
*/

/*
** Allocates a new frame and returns it, or NULL_FRAME if there is no physical
** memory left.
*/
phys_addr_t
alloc_frame(void)
{
	size_t i;
	size_t j;

	i = 0;
	while (i < NB_FRAMES)
	{
		if (frame_bitmap[i] != 0xFFu) {
			j = 0u;
			while (j < 7u) {
				if ((frame_bitmap[i] & (1 << j)) == 0) {
					break;
				}
				++i;
			}
			frame_bitmap[i] |= (1 << j);
			return (PAGE_SIZE * (i * 8u + j));
		}
		++i;
	}
	return (NULL_FRAME);
}

/*
** Frees a given frame.
*/
void
free_frame(phys_addr_t frame)
{
	/* Ensure the address is page-aligned */
	assert_eq(frame & PAGE_SIZE_MASK, 0);

	/* Ensure the given physical address is taken */
	assert_neq(frame_bitmap[GET_FRAME_IDX(frame)] & GET_FRAME_MASK(frame), 0);

	/* Set the bit corresponding to this frame to 0 */
	frame_bitmap[GET_FRAME_IDX(frame)] &= ~(GET_FRAME_MASK(frame));
}

void
pmm_init(void)
{
	memset(frame_bitmap, 0, sizeof(frame_bitmap));
	printf("[OK]\tPhysical Memory Managment\n");
}
