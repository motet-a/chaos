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
#include <kernel/unit-tests.h>
#include <string.h>
#include <stdio.h>

/*
** This is a pretty naive frame allocator using a bitmap to memorize which
** frames are free and which ones are not.
**
** It can definitely be optimised, but that's not the point at this moment.
*/

static uchar				frame_bitmap[FRAME_BITMAP_SIZE];
static size_t				next_frame;

/*
** Allocates a new frame and returns it, or NULL_FRAME if there is no physical
** memory left.
**
** The idea is that next_frame contains the index in frame_bitmap of our first
** looking address, the one most likely to be free.
** The search is done in two steps, the first one from next_frame to NB_FRAMES, and
** the second one from 0 to next_frame. If after these two steps no
** free frame have been found, then NULL_FRAME is returned. However, if one have been found,
** it also sets next_frame to the index of the following address.
*/
phys_addr_t
alloc_frame(void)
{
	size_t i;
	size_t j;
	size_t final;
	bool pass;

	i = next_frame;
	final = FRAME_BITMAP_SIZE;
	pass = false;
look_for_address:
	while (i < final)
	{
		if (frame_bitmap[i] != 0xFFu) {
			j = 0u;
			while (j < 7u && (frame_bitmap[i] & (1 << j)) != 0) {
				++j;
			}
			frame_bitmap[i] |= (1 << j);
			next_frame = i;
			return (PAGE_SIZE * (i * 8u + j));
		}
		++i;
	}
	if (!pass)
	{
		final = next_frame;
		i = 0;
		pass = true;
		goto look_for_address;
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
	next_frame = GET_FRAME_IDX(frame);
}

/*
** Initializes the frame allocator.
*/
static void
pmm_init(enum init_level il __unused)
{
	next_frame = 0u;
	memset(frame_bitmap, 0, sizeof(frame_bitmap));
	printf("[OK]\tPhysical Memory Managment\n");
}

/*
** Some unit tests for the frame allocator.
**
** TODO Write a unit-test framework within the kernel,
** so that we can test all of this through Travis.
*/
static void
pmm_test(void)
{
	assert_eq(alloc_frame(), 0x0000);
	assert_eq(alloc_frame(), 0x1000);
	assert_eq(alloc_frame(), 0x2000);
	free_frame(0x1000);
	assert_eq(alloc_frame(), 0x1000);
	free_frame(0x0000);
	free_frame(0x1000);
	free_frame(0x2000);
	while (alloc_frame() != NULL_FRAME);
	assert_eq(alloc_frame(), NULL_FRAME);
	free_frame(1234 * 0x1000);
	assert_eq(alloc_frame(), 1234 * 0x1000);
	assert_eq(alloc_frame(), NULL_FRAME);
	free_frame(0xfffff000);
	assert_eq(alloc_frame(), 0xfffff000);
	assert_eq(alloc_frame(), NULL_FRAME);
	free_frame(0x0);
	assert_eq(alloc_frame(), 0x0);
	assert_eq(alloc_frame(), NULL_FRAME);
}

NEW_INIT_HOOK(pmm, &pmm_init, CHAOS_INIT_LEVEL_PMM);
NEW_UNIT_TEST(pmm, &pmm_test, UNIT_TEST_LEVEL_MEMORY);
