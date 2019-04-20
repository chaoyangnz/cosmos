#ifndef _COMPILER_H_
#define _COMPILER_H_

/*
 * XXX this is a GCC-ism that can't easily be worked around at the moment.
 * Would probably be best just to avoid using this if possible.
 */
#ifndef IS_INLINE
#define INLINE	extern __inline
#endif

/*
 * Other handy attributes that are specific to GCC,
 * and are only in _some_ versions of GCC.
 */
#ifdef HAVE_PURE
#define SYS_PURE	__attribute__((__const__))
#else
#define SYS_PURE
#endif

#ifdef HAVE_NORETURN
#define NORETURN	__attribute__((__noreturn__))
#else
#define NORETURN
#endif

#endif /* _SYS_COMPILER_H_ */
