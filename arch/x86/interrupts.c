/* ------------------------------------------------------------------------ *\
**
**  This file is part of the Chaos Kernel, and is made available under
**  the terms of the GNU General Public License version 2.
**
**  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
**
\* ------------------------------------------------------------------------ */

#include <arch/x86/interrupts.h>
#include <string.h>

/* Defined in idt.asm */
extern struct idt_entry idt[X86_INT_MAX];

static inline void
idt_set_present(struct idt_entry *entry, bool p)
{
	entry->flags &= ~(1u << 7u);
	entry->flags |= p << 7u;
}

static inline void
idt_set_dpl(struct idt_entry *entry, enum dpl dpl)
{
	assert(dpl >= 0 && dpl <= 3);
	entry->flags &= ~(3u << 5u);
	entry->flags |= dpl << 5u;
}

static inline void
idt_set_type(struct idt_entry *entry, enum idt_entry_type type)
{
	entry->flags &= ~0xF;
	entry->flags |= type;
}

static inline void
idt_set_callback(struct idt_entry *entry, uintptr ep)
{
	entry->callback_low = ep & 0x0000FFFFu;
	entry->callback_high = (ep & 0xFFFF0000u) >> 16u;
}

static inline void
idt_set_segment_sel(struct idt_entry *entry, uint16 sel)
{
	entry->selector = sel;
}

void
idt_set_vector(uint8 vec, uintptr callback, uint16 sel, enum dpl dpl, enum idt_entry_type type)
{
	struct idt_entry *entry;

	entry = idt + vec;
	memset(entry, 0, sizeof(*entry));
	idt_set_present(entry, true);
	idt_set_dpl(entry, dpl);
	idt_set_type(entry, type);
	idt_set_callback(entry, callback);
	idt_set_segment_sel(entry, sel);
}


