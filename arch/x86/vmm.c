/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#include <arch/x86/asm.h>
#include <arch/x86/vmm.h>
#include <stdio.h>
#include <string.h>

status_t
map_virt_to_phys(virt_addr_t va, phys_addr_t pa)
{
	struct pagedir_entry *pde;
	struct pagetable_entry *pte;
	struct page_table *pt;
	bool allocated_pde;

	allocated_pde = false;
	assert(IS_PAGE_ALIGNED(va));
	assert(IS_PAGE_ALIGNED(pa));
	pde = GET_PAGE_DIRECTORY->entries + GET_PD_IDX(va);
	pt = GET_PAGE_TABLE(GET_PD_IDX(va));
	if (pde->present == false)
	{
		pde->value = alloc_frame();
		if (pde->value == NULL_FRAME) {
			pde->value = 0;
			return (ERR_NO_MEMORY);
		}
		pde->present = true;
		pde->rw = true;
		invlpg(pt);
		memset(pt, 42, PAGE_SIZE); /* Clean the new page with random shitty values */
		allocated_pde = true;
	}
	pte = pt->entries + GET_PT_IDX(va);
	/* Return NULL if the page is already mapped */
	if (pte->present)
	{
		if (allocated_pde) {
			munmap(pt, PAGE_SIZE);
		}
		return (ERR_ALREADY_MAPPED);
	}
	pte->value = pa;
	pte->present = true;
	pte->rw = true;
	pte->accessed = false;
	pte->dirty = 0;
	invlpg(va);

	/* Clean the new page with random shitty values */
	memset((void *)((uintptr)va & ~PAGE_SIZE_MASK), 42, PAGE_SIZE);
	return (OK);
}

status_t
map_page(virt_addr_t va)
{
	phys_addr_t pa;
	status_t s;

	pa = alloc_frame();
	if (pa != NULL_FRAME)
	{
		s = map_virt_to_phys(va, pa);
		if (s == OK) {
			return (OK);
		}
		free_frame(pa);
		return (s);
	}
	return (ERR_NO_MEMORY);
}

void
munmap(virt_addr_t va, size_t size)
{
	virt_addr_t ori_va;
	struct pagedir_entry *pde;
	struct pagetable_entry *pte;

	assert(IS_PAGE_ALIGNED(va));
	assert(IS_PAGE_ALIGNED(size));
	ori_va = va;
	while (va < ori_va + size)
	{
		pde = GET_PAGE_DIRECTORY->entries + GET_PD_IDX(va);
		pte = GET_PAGE_TABLE(GET_PD_IDX(va))->entries + GET_PT_IDX(va);
		if (pde->present && pte->present)
		{
			free_frame(pte->frame << 12u);
			pte->value = 0;
			invlpg(va);
		}
		va += PAGE_SIZE;
	}
}

extern struct vaspace default_vaspace;

void
arch_vmm_init(void)
{
	default_vaspace.arch.pagedir = get_cr3();
}

/* Unit tests functions */

/*
** Print the virtual memory state.
** Only used for debugging.
*/
__unused void
x86_print_mem_state(void)
{
	uint i;
	uint j;
	struct page_dir *pd;
	struct page_table *pt;

	i = 0;
	pd = GET_PAGE_DIRECTORY;
	while (i < 1024u)
	{
		if (pd->entries[i].present)
		{
			printf("[%4u] [%#p -> %#p] %s %c %c %c %c %c\n",
				i,
				i << 22u,
				pd->entries[i].frame << 12ul,
				&"RO\0RW"[pd->entries[i].rw * 3],
				"ku"[pd->entries[i].user],
				"-w"[pd->entries[i].wtrough],
				"-d"[pd->entries[i].cache],
				"-a"[pd->entries[i].accessed],
				"-H"[pd->entries[i].size]);
			if (pd->entries[i].size == false && i != 1023)
			{
				pt = GET_PAGE_TABLE(i);
				j = 0;
				while (j < 1024u)
				{
					if (pt->entries[j].present)
					{
						printf("\t[%4u] [%#p -> %#p] %s %c %c %c %c %c\n",
							j,
							(i << 22u) | (j << 12u),
							pt->entries[j].frame << 12ul,
							&"RO\0RW"[pt->entries[j].rw * 3],
							"ku"[pt->entries[j].user],
							"-w"[pt->entries[j].wtrough],
							"-d"[pt->entries[j].cache],
							"-a"[pt->entries[j].accessed],
							"-d"[pt->entries[j].dirty]);
					}
					++j;
				}
			}
		}
		++i;
	}
}

static bool
is_allocated(virt_addr_t va)
{
	struct pagedir_entry *pde;
	struct pagetable_entry *pte;

	assert(IS_PAGE_ALIGNED(va));
	pde = GET_PAGE_DIRECTORY->entries + GET_PD_IDX(va);
	pte = GET_PAGE_TABLE(GET_PD_IDX(va))->entries + GET_PT_IDX(va);
	return (pde->present && pte->present);
}

void
vmm_test(void)
{
	assert(!is_allocated((virt_addr_t)0xDEADB000));
	assert_eq(map_page((virt_addr_t)0xDEADB000), OK);
	assert(is_allocated((virt_addr_t)0xDEADB000));
	assert(!is_allocated((virt_addr_t)0xDEADA000));
	assert(!is_allocated((virt_addr_t)0xDEADC000));
	assert_eq(*(char *)0xDEADB000, 42);
	*(char *)0xDEADB000 = 43;
	assert_eq(*(char *)0xDEADB000, 43);
	assert_eq(map_page((virt_addr_t)0xDEADB000), ERR_ALREADY_MAPPED);

	/* Munmap */
	munmap((virt_addr_t)0xDEADB000, PAGE_SIZE);
	assert(!is_allocated((virt_addr_t)0xDEADB000));

	/* Mmap */
	assert_eq(mmap((virt_addr_t)0xDEADA000, 3 * PAGE_SIZE), (virt_addr_t)0xDEADA000);
	assert(!is_allocated((virt_addr_t)0xDEAD9000));
	assert(is_allocated((virt_addr_t)0xDEADA000));
	assert(is_allocated((virt_addr_t)0xDEADB000));
	assert(is_allocated((virt_addr_t)0xDEADC000));
	assert(!is_allocated((virt_addr_t)0xDEADD000));

	/* Overlapping mmap */
	assert_eq(mmap((virt_addr_t)0xDEAD8000, 5 * PAGE_SIZE), NULL);
	assert(!is_allocated((virt_addr_t)0xDEAD7000));
	assert(!is_allocated((virt_addr_t)0xDEAD8000));
	assert(!is_allocated((virt_addr_t)0xDEAD9000));
	assert(is_allocated((virt_addr_t)0xDEADA000));
	assert(is_allocated((virt_addr_t)0xDEADB000));
	assert(is_allocated((virt_addr_t)0xDEADC000));
	assert(!is_allocated((virt_addr_t)0xDEADD000));

	/* Sized munmap */
	munmap((virt_addr_t)0xDEADA000, 3 * PAGE_SIZE);
	assert(!is_allocated((virt_addr_t)0xDEAD9000));
	assert(!is_allocated((virt_addr_t)0xDEADA000));
	assert(!is_allocated((virt_addr_t)0xDEADB000));
	assert(!is_allocated((virt_addr_t)0xDEADC000));
	assert(!is_allocated((virt_addr_t)0xDEADD000));
}
