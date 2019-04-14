#!/bin/sh

OUT=boot.bin

nasm boot.asm -f bin -o $OUT
qemu-system-i386 -drive file=$OUT,format=raw,index=0,media=disk
# qemu-system-i386 -drive file=$OUT,format=raw,index=0,if=floppy
# qemu-system-i386 -hda $OUT
# qemu-system-i386 -fda $OUT