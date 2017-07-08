FROM buildpack-deps:stretch

RUN apt-get update \
    && apt-get install -y --no-install-recommends qemu grub-pc-bin xorriso \
    && mkdir /chaos

WORKDIR /chaos
COPY dev /chaos/dev
COPY drivers /chaos/drivers
COPY include /chaos/include
COPY kernel /chaos/kernel
COPY lib /chaos/lib
COPY scripts /chaos/scripts
COPY Makefile /chaos/Makefile

RUN make iso
