#ifndef _C_STDBOOL_H
#define _C_STDBOOL_H

#include <sys/i386/types.h>
/*
 *	Define the basic boolean constants if not defined already.
 */
#ifndef	true
#define true	((bool_t) 1)
#endif

#ifndef	false
#define false	((bool_t) 0)
#endif

#define bool _Bool

#define __bool_true_false_are_defined 1

#endif
