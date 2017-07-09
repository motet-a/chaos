#!/bin/sh -e

cd "$(dirname "$0")"
cd ..

docker build -t chaos -f scripts/Dockerfile .

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
