# ChaOS [![Build Status](https://travis-ci.org/Arignir/chaos.svg?branch=master)](https://travis-ci.org/Arignir/chaos)

ChaOS is a fun project that i'm doing to entertain myself during 2017's summer vacations.

It's a unix-like featureless kernel, that only supports x86 (Intel 32 bits). My goal is to have a basic shell that can handle simple commands like `ls`, `cat` and `echo`.

# Build Dependencies
* `nasm`
* `make`
* `gcc` or `clang`
* `grub-mkrescue` (generally packed with other binaries as `grub-pc-bin`)
* `qemu` and `xorriso` (cpu emulator) *optional*

If you are using `apt-get` as your package manager (`Debian`, `Ubuntu` etc.), you can use this command to install all dependencies:
```bash
apt-get install qemu grub-pc-bin xorriso nasm
```

If you are using `pacman` as your package manager (`ArchLinux`, `Manjaro` etc.), you can use this command instead:
```bash
pacman -Sy qemu grub libisoburn nasm
```

If you are using an other package manager, well... Good luck! :p

# Building an iso

To build the kernel, run
```bash
make kernel
```

To build a complete iso with grub installed (suitable for USB flash drives), run
```bash
make iso
```

# Testing with QEMU

If you want to run ChaOS through QEMU even if it's boring & useless right now, run
```bash
make run
```

# :rocket: Wanna participate?

Fork with me!
