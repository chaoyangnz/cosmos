#!/bin/sh

rm *.o *.bin
nasm -f elf multiboot.asm
nasm -f elf kernel.asm

ld -o kernel.bin -T linker.ld multiboot.o kernel.o

qemu-system-i386 -kernel kernel.bin