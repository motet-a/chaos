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

# C compilation
CC		?= gcc
INC		?= -Iinclude
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
			-std=gnu89 \
			-pedantic \
			-O2 \
			$(INC)
SRC_C		:= $(shell find -name *.c)
DEP		:= $(SRC_C:.c=.d)

# Assembly
NASM		?= nasm
NASMFLAGS	+= -f elf32
SRC_ASM		:= $(shell find -name *.asm)

# Link
LD		?= ld
LDFLAGS		+= -n --gc-sections -m elf_i386 -T scripts/kernel.ld

# Tools & utilities
RM		?= rm -f
QEMU		?= qemu-system-i386


all:		$(KERNEL) $(ISO)

iso:		$(ISO)

kernel:		$(KERNEL)

$(KERNEL):	$(OBJS)
		mkdir -p $(@D) && echo -e "  MKDIR\t $(@D)"
		$(LD) $(LDFLAGS) -o $@ $+ && echo -e "  LD\t $@"

$(ISO):		$(KERNEL)
		echo -e "  SHELL\t chaos-iso.sh"
		./scripts/chaos-iso.sh

clean:
		$(RM) $(OBJS)
		$(RM) -r $(BUILD)
		$(RM) $(DEP)
		$(RM) $(ISO)
		echo -e "  CLEAN"

re:		clean all

run:		$(ISO)
		echo -e "  SHELL\t qemu-x86.sh"
		./scripts/qemu-x86.sh -m 1G

monitor:	all
		echo -e "  SHELL\t qemu-x86.sh"
		./scripts/qemu-x86.sh -t -m 1G

debug:		all
		echo -e "  SHELL\t qemu-x86.sh"
		./scripts/qemu-x86.sh -d -m 1G

%.o:		%.asm
		$(NASM) $(NASMFLAGS) $< -o $@ && echo -e "  NASM\t $<"

-include	$(DEP)
%.o:		%.c
		$(CC) $(CFLAGS) -c $< -o $@ && echo -e "  CC\t $<"

.PHONY:		all iso kernel clean re run monitor debug

.SILENT:	all $(KERNEL) $(ISO) clean re run monitor debug $(OBJS)
