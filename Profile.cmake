function(load_profile ISA PLATFORM)
    # Obtain sources for the ISA
    file(GLOB ISA_SRCS "kernel/arch/${ISA}/*.c" "kernel/arch/${ISA}/*.asm")
    file(GLOB PLATFORM_SRCS "kernel/arch/${ISA}/${PLATFORM}/*.c" "kernel/arch/${ISA}/${PLATFORM}/*.asm")

    # Load flags associated with ISA and Profile
    include("kernel/arch/${ISA}/flags.cmake")
    include("kernel/arch/${ISA}/${PLATFORM}/flags.cmake")

    # Now export our output variables
    set(ISA_SRCS ${ISA_SRCS} PARENT_SCOPE)
    set(PLATFORM_SRCS ${PLATFORM_SRCS} PARENT_SCOPE)
    set(PLATFORM_LAYOUT "${CMAKE_SOURCE_DIR}/kernel/arch/${ISA}/${PLATFORM}/layout.ld" PARENT_SCOPE)

    # And specific flags
    set(ISA_C_FLAGS ${ISA_C_FLAGS} PARENT_SCOPE)
    set(ISA_ASM_FLAGS ${ISA_ASM_FLAGS} PARENT_SCOPE)


    file(GLOB GENERIC_SRCS "kernel/*.c")
    set(GENERIC_SRCS ${GENERIC_SRCS} PARENT_SCOPE)

    file(GLOB LIBC_SRCS "libc/**/*.c")
    set(LIBC_SRCS ${LIBC_SRCS} PARENT_SCOPE)
endfunction(load_profile)