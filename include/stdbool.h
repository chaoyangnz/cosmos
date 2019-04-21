#ifndef _C_STDBOOL_H
#define _C_STDBOOL_H

/*
 * Just yer ordinary boolean type.
 * On the i386, bytes are fast, so we use it;
 * on other architectures this will generally be an int.
 */
typedef unsigned char		bool_t;

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
