#ifndef _C_STDDEF_H_
#define _C_STDDEF_H_

#include <sys/i386/types.h>

//#ifndef _SIZE_T
//#define _SIZE_T
//typedef size_t size_t;
//#endif
//
//#ifndef _WCHAR_T
//#define _WCHAR_T
//typedef wchar_t wchar_t;
//#endif

#ifndef NULL
#define NULL 0
#endif

#ifndef offsetof
#define	offsetof(type, member)	((size_t)(&((type *)0)->member))
#endif

#endif /* _C_STDDEF_H_ */
