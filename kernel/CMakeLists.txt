cmake_minimum_required (VERSION 2.6)
project (kernel)

LOAD_PROFILE("i386" "pc")

enable_language(C)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_COMPILER /usr/local/bin/i386-elf-gcc)
SET (CMAKE_C_FLAGS                "-g -std=gnu99 -ffreestanding -Og -Wall -Wextra")
SET (CMAKE_C_FLAGS_DEBUG          "-g -std=gnu99 -ffreestanding -Og -Wall -Wextra")
SET (CMAKE_C_FLAGS_RELEASE        "-g -std=gnu99 -ffreestanding -O2 -Wall -Wextra")

enable_language(ASM_NASM)
set(CMAKE_ASM_NASM_COMPILER /usr/local/bin/nasm)
set(CMAKE_ASM_NASM_FLAGS "-g -F dwarf -f elf")

set(CMAKE_LINKER /usr/local/bin/i386-elf-ld)
set(CMAKE_C_LINK_FLAGS "-T linker.ld")

include_directories( . )
add_executable(kernel main.c console.c arch/i386/eden.asm arch/i386/multiboot.asm)