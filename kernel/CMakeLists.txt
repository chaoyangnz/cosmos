cmake_minimum_required (VERSION 3.13)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
project(cosmos)


set(CMAKE_SYSTEM_NAME Generic)

set(CMAKE_VERBOSE_MAKEFILE ON)

function(load_profile ISA PLATFORM)
    # Obtain sources for the ISA
    file(GLOB ISA_SRCS "arch/${ISA}/*.c" "arch/${ISA}/*.asm")
    file(GLOB PLATFORM_SRCS "arch/${ISA}/${PLATFORM}/*.c" "arch/${ISA}/${PLATFORM}/*.asm")

    # Load flags associated with ISA and Profile
    include("arch/${ISA}/flags.cmake")
    include("arch/${ISA}/${PLATFORM}/flags.cmake")

    # Now export our output variables
    set(ISA_SRCS ${ISA_SRCS} PARENT_SCOPE)
    set(PLATFORM_SRCS ${PLATFORM_SRCS} PARENT_SCOPE)
    set(PLATFORM_LAYOUT "${CMAKE_SOURCE_DIR}/arch/${ISA}/${PLATFORM}/layout.ld" PARENT_SCOPE)

    # And specific flags
    set(ISA_C_FLAGS ${ISA_C_FLAGS} PARENT_SCOPE)
    set(ISA_ASM_FLAGS ${ISA_ASM_FLAGS} PARENT_SCOPE)
endfunction(load_profile)


file(GLOB GENERIC_SRCS "*.c")

load_profile("i386" "pc")

# NASM ASSEMBLER SETTINGS
enable_language(ASM_NASM)
set(CMAKE_ASM_NASM_COMPILER /usr/local/bin/nasm)
set(CMAKE_ASM_NASM_OBJECT_FORMAT "elf")
if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_ASM_NASM_FLAGS "-g -F dwarf")
endif()
set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> ${CMAKE_ASM_NASM_FLAGS} ${ISA_ASM_FLAGS} ${PLATFORM_ASM_FLAGS} -o <OBJECT> <SOURCE>")

# C COMPILER SETTINGS
enable_language(C)
set(CMAKE_C_COMPILER /usr/local/bin/i386-elf-gcc)
set(CMAKE_C_SYSROOT_FLAG "")
set(CMAKE_C_FLAGS "${ISA_C_FLAGS} ${PLATFORM_C_FLAGS}")
set(CMAKE_C_LINK_FLAGS "")

# LINKER SETTINGS
set(CMAKE_LINKER /usr/local/bin/i386-elf-ld)
set(CMAKE_EXE_LINKER_FLAGS "-Wl,-T${PLATFORM_LAYOUT}")


include_directories( . ../oskit/include/oskit/c )
add_executable(${CMAKE_PROJECT_NAME} ${PLATFORM_SRCS} ${ISA_SRCS} ${GENERIC_SRCS})

# RUN KERNEL IN QEMU
if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(QEMU_FLAGS "-s;-S")
endif()
add_custom_command (TARGET ${CMAKE_PROJECT_NAME}
        POST_BUILD
        COMMAND /usr/local/bin/qemu-system-i386 ${QEMU_FLAGS} -kernel ${CMAKE_BINARY_DIR}/cosmos
        COMMENT "Running cosmos kernel...")
