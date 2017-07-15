##############################################################################
##
##  This file is part of the Chaos Kernel, and is made available under
##  the terms of the GNU General Public License version 2.
##
##  Copyright (C) 2017 - Antoine Motet
##
##############################################################################

FROM buildpack-deps:stretch

RUN apt-get update \
    && apt-get install -y --no-install-recommends qemu grub-pc-bin xorriso nasm clang \
    && mkdir /chaos

WORKDIR /chaos
COPY arch /chaos/arch
COPY platform /chaos/platform
COPY include /chaos/include
COPY kernel /chaos/kernel
COPY lib /chaos/lib
COPY scripts /chaos/scripts
COPY Makefile /chaos/Makefile

RUN make clean
RUN CC=clang make kernel
RUN make clean
RUN make test_iso
