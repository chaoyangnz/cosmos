#ifndef _C_ASSERT_H_
#define _C_ASSERT_H_

#ifdef NDEBUG

#define assert(ignore) ((void)0)

#else

#include <oskit/compiler.h>


extern void panic(const char *format, ...) SYS_NORETURN;


#define assert(expression)  \
	((void)((expression) ? 0 : \
		(panic(__FILE__":%u: failed assertion `"#expression"'", \
			__LINE__), 0)))

#endif

#endif /* _C_ASSERT_H_ */
