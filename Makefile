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
KERNEL		?= $(BUILD)/boot/chaos
OBJS		= $(SRC_ASM:.asm=.o) $(SRC_C:.c=.o)

# C compilation
CC		?= gcc
INC		?= -Iinclude
CFLAGS		+= \
		-m32 \
		-MMD \
		-nostdlib \
		-nostdinc \
		-fno-builtin \
		-fno-stack-protector \
		$(INC)
SRC_C		:= $(shell find -name *.c)
DEP		:= $(SRC_C:.c=.d)

# Assembly
NASM		?= nasm
NASMFLAGS	?= -f elf32
SRC_ASM		:= $(shell find -name *.asm)

# Link
LD		?= ld
LDFLAGS		+= -n --gc-sections -m elf_i386
LINKERLD	?= linker.ld

# Tools & utilities
RM		?= rm -f
QEMU		?= qemu-system-i386
GRUB_MKRESCUE	?= grub-mkrescue
GRUB_FLAGS	?= -d /usr/lib/grub/i386-pc


all:		$(KERNEL) $(ISO)

iso:		$(ISO)

kernel:		$(KERNEL)

$(KERNEL):	$(OBJS)
		mkdir -p $(@D) && echo -e "  MKDIR\t $(@D)"
		$(LD) $(LDFLAGS) -T $(LINKERLD) -o $@ $+ && echo -e "  LD\t $@"

$(ISO):		$(KERNEL)
		mkdir -p $(BUILD)/boot/grub && echo -e "  MKDIR\t $(BUILD)/boot/grub"
		cp grub.cfg $(BUILD)/boot/grub/ && echo -e "  CP\t grub.cfg -> $(BUILD)/boot/grub/grub.cfg"
		$(GRUB_MKRESCUE) $(GRUB_FLAGS) -o $@ $(BUILD) 2> /dev/null && echo -e "  GRUB\t $@"

clean:
		$(RM) $(OBJS)
		$(RM) -r $(BUILD)
		$(RM) $(DEP)
		$(RM) $(ISO)
		echo -e "  CLEAN"

re:		clean all

run:		$(ISO)
		echo -e "  QEMU\t $(ISO)"
		$(QEMU) -serial stdio -cdrom $(ISO) -m 1G

monitor:	all
		echo -e "  QEMU\t $(ISO)"
		$(QEMU) -monitor stdio -cdrom $(ISO) -m 1G

debug:		all
		echo -e "  QEMU\t $(ISO)"
		$(QEMU) -s -d int,cpu_reset -no-reboot -serial stdio -cdrom $(ISO) -m 1G

%.o:		%.asm
		$(NASM) $(NASMFLAGS) $< -o $@ && echo -e "  NASM\t $<"

-include	$(DEP)
%.o:		%.c
		$(CC) $(CFLAGS) -c $< -o $@ && echo -e "  CC\t $<"

.PHONY:		all iso kernel clean re run monitor debug

.SILENT:	all $(KERNEL) $(ISO) clean re run monitor debug $(OBJS)
