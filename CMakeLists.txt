cmake_minimum_required (VERSION 3.13)
set(CMAKE_C_COMPILER_WORKS "STATIC_LIBRARY")
project(cosmos C)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_VERBOSE_MAKEFILE ON)

file(GLOB_RECURSE KERNEL_SRCS "kernel/*.c" "kernel/*.asm")
file(GLOB_RECURSE LIBC_SRCS "libc/*.c" "libc/*.asm")

# headers path
include_directories(include)

# tool chain definition
include("flags.cmake")
include("toolchain.cmake")

# libc for kernel only
add_library(c STATIC ${LIBC_SRCS})
target_link_libraries(c -L/usr/local/Cellar/i386-elf-gcc/8.2.0/lib/gcc/i386-elf/8.2.0 -lgcc)

# kernel
add_executable(${CMAKE_PROJECT_NAME} ${KERNEL_SRCS})
target_link_libraries(${CMAKE_PROJECT_NAME} c)


# run kernel in QEMU
if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(QEMU_FLAGS "-s;-S")
endif()
add_custom_command (TARGET ${CMAKE_PROJECT_NAME}
        POST_BUILD
        COMMAND /usr/local/bin/qemu-system-i386 -m 512M -monitor stdio -no-reboot -no-shutdown ${QEMU_FLAGS} -kernel ${CMAKE_BINARY_DIR}/cosmos
        COMMENT "Running cosmos kernel...")

# Grub
#add_custom_command (TARGET ${CMAKE_PROJECT_NAME}
#        POST_BUILD
#        COMMAND cp cosmos ${CMAKE_SOURCE_DIR}/iso/boot/
#        COMMENT "COPY kernel to iso folder")
#
#add_custom_command(TARGET ${CMAKE_PROJECT_NAME}
#        POST_BUILD
#        COMMAND mkisofs -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -A os -input-charset utf8 -quiet -boot-info-table -o cosmos.iso ${CMAKE_SOURCE_DIR}/iso
#        COMMENT "Generate ISO image")
#
#if(CMAKE_BUILD_TYPE MATCHES Debug)
#    set(QEMU_FLAGS "-s;-S")
#endif()
#add_custom_command (TARGET ${CMAKE_PROJECT_NAME}
#        POST_BUILD
#        COMMAND /usr/local/bin/qemu-system-i386 -cdrom cosmos.iso
#        COMMENT "Running cosmos kernel...")
