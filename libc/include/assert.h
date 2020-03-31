#ifndef C_ASSERT_H
#define C_ASSERT_H

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

#endif //C_ASSERT_H
