cmake_minimum_required (VERSION 3.13)
set(CMAKE_C_COMPILER_WORKS "STATIC_LIBRARY")
project(cosmos C)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_VERBOSE_MAKEFILE ON)
include("Profile.cmake")

# headers path
include_directories(include)
load_profile("i386" "pc")

# tool chain definition
include("Toolchain.cmake")

# libc for kernel only
add_library(c STATIC ${LIBC_SRCS})

# kernel
add_executable(${CMAKE_PROJECT_NAME} ${PLATFORM_SRCS} ${ISA_SRCS} ${GENERIC_SRCS})
target_link_libraries(${CMAKE_PROJECT_NAME} c)

# run kernel in QEMU
if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(QEMU_FLAGS "-s;-S")
endif()
add_custom_command (TARGET ${CMAKE_PROJECT_NAME}
        POST_BUILD
        COMMAND /usr/local/bin/qemu-system-i386 ${QEMU_FLAGS} -kernel ${CMAKE_BINARY_DIR}/cosmos
        COMMENT "Running cosmos kernel...")




