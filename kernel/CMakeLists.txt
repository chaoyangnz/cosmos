cmake_minimum_required (VERSION 3.13)
project(cosmos)


set(CMAKE_SYSTEM_NAME "cosmos")

set(CMAKE_VERBOSE_MAKEFILE ON)

FUNCTION(LOAD_PROFILE ISA PLATFORM)
    # Obtain sources for the ISA
    FILE(GLOB ISA_SRCS "arch/${ISA}/*.c" "arch/${ISA}/*.asm")
    FILE(GLOB PLATFORM_SRCS "arch/${ISA}/${PLATFORM}/*.c" "arch/${ISA}/${PLATFORM}/*.asm")

    # Load flags associated with ISA and Profile
    INCLUDE("arch/${ISA}/flags.cmake")
    INCLUDE("arch/${ISA}/${PLATFORM}/flags.cmake")

    # Now export our output variables
    SET(ISA_SRCS ${ISA_SRCS} PARENT_SCOPE)
    SET(PLATFORM_SRCS ${PLATFORM_SRCS} PARENT_SCOPE)
    SET(PLATFORM_LAYOUT "${CMAKE_SOURCE_DIR}/arch/${ISA}/${PLATFORM}/layout.ld" PARENT_SCOPE)

    # And specific flags
    SET(ISA_C_FLAGS ${ISA_C_FLAGS} PARENT_SCOPE)
    SET(ISA_ASM_FLAGS ${ISA_ASM_FLAGS} PARENT_SCOPE)
ENDFUNCTION(LOAD_PROFILE)


FILE(GLOB GENERIC_SRCS "*.c")

LOAD_PROFILE("i386" "pc")


enable_language(ASM_NASM)
set(CMAKE_ASM_NASM_COMPILER /usr/local/bin/nasm)
set(CMAKE_ASM_NASM_OBJECT_FORMAT "elf")
set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> ${ISA_ASM_FLAGS} ${PLATFORM_ASM_FLAGS} -o <OBJECT> <SOURCE>")

enable_language(C)
set(CMAKE_C_COMPILER /usr/local/bin/i386-elf-gcc)
set(CMAKE_C_SYSROOT_FLAG "")
set(CMAKE_C_FLAGS "${ISA_C_FLAGS} ${PLATFORM_C_FLAGS}")
set(CMAKE_C_LINK_FLAGS "")

set(CMAKE_LINKER /usr/local/bin/i386-elf-ld)
set(CMAKE_EXE_LINKER_FLAGS "-Wl,-T${PLATFORM_LAYOUT}")


include_directories( . )
add_executable(${CMAKE_PROJECT_NAME} ${PLATFORM_SRCS} ${ISA_SRCS} ${GENERIC_SRCS})

add_custom_command (TARGET ${CMAKE_PROJECT_NAME}
        POST_BUILD
        COMMAND /usr/local/bin/qemu-system-i386 -kernel ${CMAKE_BINARY_DIR}/cosmos
        COMMENT "Running cosmos kernel...")
