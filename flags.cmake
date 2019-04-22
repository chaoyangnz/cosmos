set(ASM_FLAGS "-f elf")
set(C_FLAGS "-m32 -std=gnu99 -ffreestanding -nostdlib -nostdinc -nostartfiles -fno-zero-initialized-in-bss -Og -Wall -Wextra ")
set(CMAKE_C_FLAGS_DEBUG "-gdwarf-2")
set(LINKER_FLAGS "")