#ifndef _C_STDDEF_H_
#define _C_STDDEF_H_

#include <stdint.h>

#ifndef _SIZE_T
#define _SIZE_T
typedef uint32_t size_t;
#endif

#ifndef _WCHAR_T
#define _WCHAR_T
typedef uint16_t	wchar_t;	/* Unicode wide character */
#endif

#ifndef NULL
#define NULL 0
#endif

/*
 * A size_t is the proper type for
 * expressing the difference between two
 * addr_t entities.
 */
typedef int32_t		        ssize_t;

#ifndef OFFSETOF
#define	offsetof(type, member)	((size_t)(&((type *)0)->member))
#endif

#endif /* _C_STDDEF_H_ */
