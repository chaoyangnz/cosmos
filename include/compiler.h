#ifndef _COMPILER_H_
#define _COMPILER_H_

/*
 * Other handy attributes that are specific to GCC,
 * and are only in _some_ versions of GCC.
 */
#ifdef HAVE_PURE
#define PURE	__attribute__((__const__))
#else
#define PURE
#endif

#ifdef HAVE_NORETURN
#define NORETURN	__attribute__((__noreturn__))
#else
#define NORETURN
#endif

#define PACKED	__attribute__((packed))
#define BOOT_SECTION __attribute__((section (".boot")))
#define BOOT_BSS_SECTION __attribute__((section (".boot_bss")))

#endif /* _SYS_COMPILER_H_ */
