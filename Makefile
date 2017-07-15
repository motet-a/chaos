##############################################################################
##
##  This file is part of the Chaos Kernel, and is made available under
##  the terms of the GNU General Public License version 2.
##
##  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
##
##############################################################################

# Output
BUILD		?= build
ISO		?= chaos.iso
KERNEL		?= $(BUILD)/chaos.bin
OBJS		= $(SRC_ASM:.asm=.o) $(SRC_C:.c=.o)
arch		?= x86
ARCH		= $(arch)
PLATFORM	?= $(shell ./scripts/get_platform.sh $(ARCH))
boot_flags	?=
BOOT_FLAGS	= $(boot_flags)

# C compilation
CC		?= gcc
CFLAGS		+= \
			-m32 \
			-MMD \
			-mno-sse \
			-mno-sse2 \
			-mno-sse3 \
			-mno-sse4.1 \
			-mno-sse4.2 \
			-mno-sse4 \
			-nostdlib \
			-nostdinc \
			-fno-builtin \
			-fno-stack-protector \
			-fno-omit-frame-pointer \
			-Wall \
			-Wextra \
			-std=gnu11 \
			-O2 \
			-isystem include \
			-isystem include/lib/libc
SRC_C		:= $(shell find "arch/$(ARCH)/" "platform/$(PLATFORM)" kernel lib -name *.c)
DEP		:= $(SRC_C:.c=.d)

# Assembly
NASM		?= nasm
NASMFLAGS	+= -f elf32
SRC_ASM		:= $(shell find "arch/$(ARCH)/" -name *.asm)

# Link
LD		?= ld
LDFLAGS		+= -n --gc-sections -m elf_i386 -T arch/$(ARCH)/kernel.ld


all:		$(ISO)

iso:		$(ISO)

kernel:		$(KERNEL)

$(KERNEL):	$(OBJS)
		mkdir -p $(@D) && echo -e "  MKDIR\t $(@D)"
		$(LD) $(LDFLAGS) -o $@ $+ && echo -e "  LD\t $@"

$(ISO):		$(KERNEL)
		echo -e "  SHELL\t chaos-iso.sh $(BOOT_FLAGS)"
		./scripts/chaos-iso.sh -b "$(BOOT_FLAGS)"

clean:
		$(RM) $(OBJS)
		$(RM) -r $(BUILD)
		$(RM) $(DEP)
		$(RM) $(ISO)
		echo -e "  CLEAN"

re:		clean all

run:		$(ISO)
		echo -e "  SHELL\t qemu.sh"
		./scripts/qemu.sh -m 1G -a $(ARCH)

monitor:	$(ISO)
		echo -e "  SHELL\t qemu.sh"
		./scripts/qemu.sh -t -m 1G -a $(ARCH)

debug:		$(ISO)
		echo -e "  SHELL\t qemu.sh"
		./scripts/qemu.sh -d -m 1G -a $(ARCH)

%.o:		%.asm
		$(NASM) $(NASMFLAGS) $< -o $@ && echo -e "  NASM\t $<"

-include	$(DEP)
%.o:		%.c
		$(CC) $(CFLAGS) -c $< -o $@ && echo -e "  CC\t $<"

.PHONY:		all iso kernel clean re run monitor debug

.SILENT:	all $(KERNEL) $(ISO) clean re run monitor debug $(OBJS)
