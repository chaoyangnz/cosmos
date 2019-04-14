#!/bin/sh

rm *.o *.bin
nasm -f elf multiboot_header.asm
nasm -f elf kernel.asm

ld -o kernel.bin -T linker.ld multiboot_header.o kernel.o

qemu-system-i386 -kernel kernel.bin