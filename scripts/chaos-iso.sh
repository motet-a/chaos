#!/usr/bin/env bash

##############################################################################
##
##  This file is part of the Chaos Kernel, and is made available under
##  the terms of the GNU General Public License version 2.
##
##  Copyright (C) 2017 - Benjamin Grange <benjamin.grange@epitech.eu>
##
##############################################################################

set -e -u

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$SCRIPT_DIR/../"
BUILD_DIR="$PROJECT_DIR/build/"
RULES=kernel

if [ ! -f "$BUILD_DIR/chaos.bin" ]; then
	echo -e "  MAKE\t $RULES"
	make -C "$PROJECT_DIR" --no-print-directory "$RULES"
fi

if ! which xorriso grub-mkrescue &> /dev/null; then
	echo -e "  ERROR\t You must install xorriso and grub-mkrescue first"
	exit 1
fi

TEMP=$(mktemp -d)

mkdir -p "$TEMP/boot/grub"
cp "$BUILD_DIR/chaos.bin" "$TEMP/boot/chaos.bin"
cat > "$TEMP/boot/grub/grub.cfg" << EOF
set timeout=0

menuentry "ChaOS" {
	multiboot2 /boot/chaos.bin
	boot
}
EOF

GRUB_OUTPUT=$(mktemp)
echo -e "  GRUB\t chaos.iso"

if ! grub-mkrescue -o "$PROJECT_DIR/chaos.iso" "$TEMP" &> "$GRUB_OUTPUT" ; then
	cat "$GRUB_OUTPUT"
	exit 1
fi

rm -rf "$GRUB_OUTPUT"

rm -rf "$TEMP"
