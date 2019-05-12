# cosmos

## what is it?
Cosmos is my world in bare bone - a kernel running as you like. This is my own attempt to gain back my interest in system programming.

<img src="https://i.imgur.com/brGYFWq.gif" width="400" />

## Current status and roadmap
- [x] set up development environment powered by QEMU, CMake, CLion, GCC cross compiling toolchain and NASM
- [x] minimal C standard library (libc) for kernel development
- [x] handover the boot from multiboot and enable x86 protect mode
- [x] setup GDT and segments for flat memory model
- [x] setup page directory, page table and enable paging
- [x] relocate the kernel to higher half virtual address space (start from 3G)
- [x] setup IDT and remap PIC IRQs to interrupts 32 ~ 47
- [x] VGA frame buffer driver
- [x] PS/2 keyboard driver
- [ ] physical memory manager and page frame allocator
- [ ] virtual memory manager and separate virtual memory space per process
- [ ] user land
- [ ] system calls
- [ ] file system
- [ ] consistent device driver interface and device manager


## install tools

```
# Install cmake, qemu
brew install qemu cmake cdrtools

# install cross build toolchain
brew install i386-elf-binutils i386-elf-gcc i386-elf-gdb i386-elf-grub
```

## Build & Run

```
cmake -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles" .
cd cmake-build-release
make
```

## Debug

Once the kernel is running, you can use GDB to remote debug in port `1234`. CLion has a good support of visual debugging.
Create a Remote Debug config, and set break points in code. It rolls!

## Credits

- Libc: derived from oskit
- ASCII art: http://patorjk.com/software/taag/#p=display&f=Double&t=COSMOS