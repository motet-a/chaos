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
boot_args=${CHAOS_BOOT_ARGS:-}
echo $boot_args

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
grub_cfg="$TEMP/boot/grub/grub.cfg"
cat > $grub_cfg << EOF
set timeout=0

menuentry "ChaOS" {
EOF

echo "  multiboot2 /boot/chaos.bin ${boot_args}" >> $grub_cfg
echo "}" >> $grub_cfg

GRUB_OUTPUT=$(mktemp)
output_iso_path="${PROJECT_DIR}/chaos.iso"

echo -e "  GRUB\t ${output_iso_path}"

if ! grub-mkrescue -o "$output_iso_path" "$TEMP" &> "$GRUB_OUTPUT" ; then
	cat "$GRUB_OUTPUT"
	exit 1
fi

rm -rf "$GRUB_OUTPUT"

rm -rf "$TEMP"
