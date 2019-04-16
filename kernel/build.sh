#!/bin/sh

BUILD_DIR=./bin
ASM="nasm -g -F dwarf -f elf"
CC="i386-elf-gcc -g -std=gnu99 -ffreestanding -Og -Wall -Wextra"
LD="i386-elf-ld -T linker.ld"
VM="qemu-system-i386 -s -S"

rm ${BUILD_DIR}/*
${ASM} arch/i386/multiboot.asm -o ${BUILD_DIR}/multiboot.o
${ASM} arch/i386/kernel.asm -o ${BUILD_DIR}/kernel.o

${CC} -c console.c -o ${BUILD_DIR}/console.o
${CC} -c main.c -o ${BUILD_DIR}/main.o

${LD} -o ${BUILD_DIR}/kernel.bin ${BUILD_DIR}/multiboot.o ${BUILD_DIR}/kernel.o ${BUILD_DIR}/console.o ${BUILD_DIR}/main.o

${VM} -kernel ${BUILD_DIR}/kernel.bin