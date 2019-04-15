#!/bin/sh

BUILD_DIR=./bin

rm ${BUILD_DIR}/*
nasm -f elf arch/i386/multiboot.asm -o ${BUILD_DIR}/multiboot.o
nasm -f elf arch/i386/kernel.asm -o ${BUILD_DIR}/kernel.o

i386-elf-gcc -c main.c -o ${BUILD_DIR}/main.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

i386-elf-ld -o ${BUILD_DIR}/kernel.bin -T linker.ld ${BUILD_DIR}/multiboot.o ${BUILD_DIR}/kernel.o ${BUILD_DIR}/main.o

qemu-system-i386 -kernel ${BUILD_DIR}/kernel.bin