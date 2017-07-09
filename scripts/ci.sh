#!/bin/sh -e

##############################################################################
##
##  This file is part of the Chaos Kernel, and is made available under
##  the terms of the GNU General Public License version 2.
##
##  Copyright (C) 2017 - Antoine Motet
##
##############################################################################

set -e -u

SCRIPT_DIR="$(dirname "${BASH_SOURCE[0]}")"
PROJECT_DIR="$SCRIPT_DIR/../"

cd "$PROJECT_DIR"

docker build -t chaos -f ./scripts/Dockerfile .

docker run --rm --name chaos -d chaos \
	qemu-system-i386 \
		-nographic \
		-serial stdio \
		-monitor none \
		-boot d \
		-cdrom chaos.iso

sleep 2

logs=$(docker logs chaos)
docker stop chaos

echo $logs

case "$logs" in
	*"Init finished"*) exit;;
	*) exit 1;;
esac
