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

function print_usage {
	echo "Usage: $0 [OPTIONS]"
	echo "-d			debug mode"
	echo "-t			monitor mode"
	echo "-m <MB>			memory (in MB)"
	echo "-h			print this help menu"
	exit 1
}

DEBUG=0
MONITOR=0
MEMORY=512

while getopts dthm: FLAG; do
	case $FLAG in
		d) DEBUG=1;;
		t) MONITOR=1;;
		m) MEMORY="$OPTARG";;
		h) print_usage;;
		\?)
			echo "Unknown option"
			print_usage
	esac
done

shift $((OPTIND-1))

QEMU="qemu-system-i386"
ISO="$PROJECT_DIR/chaos.iso"

ARGS="-m $MEMORY -cdrom $ISO"

if [ $DEBUG == 1 ]; then
	ARGS+=" -s -d int,cpu_reset -no-reboot"
fi

if [ $MONITOR == 1 ]; then
	ARGS+=" -monitor stdio"
else
	ARGS+=" -serial stdio"
fi

if [ ! -f "$ISO" ]; then
	RULES="chaos.iso"
	echo -e "  MAKE\t $RULES"
	make -C "$PROJECT_DIR" --no-print-directory $RULES
fi

if ! which "$QEMU" &> /dev/null; then
	echo -e "  ERROR\t You must install $QEMU first"
	exit 1
fi

echo -e "  QEMU\t chaos.iso"
$QEMU $ARGS $@
