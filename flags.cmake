set(ASM_FLAGS "-f elf")
set(C_FLAGS "-m32 -std=gnu99 -ffreestanding -nostdlib -nostdinc -nostartfiles -fno-aggressive-loop-optimizations -fno-zero-initialized-in-bss -O0 -Wall -Wextra")
set(CMAKE_C_FLAGS_DEBUG "-ggdb")
set(LINKER_FLAGS "")