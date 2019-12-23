##################### CROSS COMPILING TOOL CHAIN ############################
set(_CMAKE_TOOLCHAIN_PREFIX "i386-elf")

# BINUTILS
set(CMAKE_AR "/usr/local/bin/i386-elf-ar")
set(CMAKE_RANLIB  "/usr/local/bin/i386-elf-ranlib")

# NASM ASSEMBLER
enable_language(ASM_NASM)
set(CMAKE_ASM_NASM_COMPILER /usr/local/bin/nasm)
set(CMAKE_ASM_NASM_OBJECT_FORMAT "elf")
if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_ASM_NASM_FLAGS "-g -F dwarf")
endif()
set(CMAKE_ASM_NASM_COMPILE_OBJECT "${CMAKE_ASM_NASM_COMPILER} ${CMAKE_ASM_NASM_FLAGS} ${ASM_FLAGS} -o <OBJECT> <SOURCE>")

# C COMPILER
enable_language(C)
set(CMAKE_C_COMPILER /usr/local/bin/i386-elf-gcc)
set(CMAKE_C_SYSROOT_FLAG "")
set(CMAKE_C_FLAGS "${C_FLAGS}")
set(CMAKE_C_LINK_FLAGS "")
set(CMAKE_CXX_COMPILER /usr/local/bin/i386-elf-g++)

# LINKER
set(CMAKE_LINKER /usr/local/bin/i386-elf-ld)
set(CMAKE_EXE_LINKER_FLAGS "-Wl,-T${CMAKE_SOURCE_DIR}/layout.ld")