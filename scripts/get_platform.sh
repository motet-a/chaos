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

if [ $# -ne 1 ]; then
	echo "Usage: $0 <arch>"
	exit 1
fi

case $1 in
	x86) echo "pc";;
	*)
		echo "unknown"
		exit 1
esac
