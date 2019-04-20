#include <stdio.h>

/*
 * This function provides a dump of the function call stack on an i386.  It
 * starts with its caller's frame, and goes back until either the
 * maximum number of levels is exceeded, or its hits a null fp or eip.
 *
 * The prototype is in <oskit/debug.h>
 */

#define MAX_ST_LEVELS 16

/*
 * dump current stack trace to specified printf function
 */
void dump_stack_trace_bis(int (*__printf)(const char *,...), int max_st_levels)
{
	unsigned int *fp, i;
	
	asm volatile ("movl %%ebp,%0" : "=r" (fp));

	__printf("Backtrace: fp=%x", (int) fp);
	for (i = 0; i < max_st_levels; i++) {
		if ((i % 8) == 0)
			__printf("\n");
			
		fp = (int *)(*fp);
		
		if (!(*(fp + 1) && *fp))
			break;

		__printf(" %08x", *(fp + 1));
	}
	__printf("\n");
}

/*
 * dump current stack trace
 */
void dump_stack_trace(void)
{
	dump_stack_trace_bis(printf, MAX_ST_LEVELS);
}

/*
 * store a backtrace
 */
void
store_stack_trace(unsigned *backtrace, int max_len)
{
        unsigned *ebp;
        unsigned i;

        asm volatile("movl %%ebp,%0" : "=r" (ebp));

        for (i = 0; ebp && i < max_len - 1; i++)
        {
		backtrace[i] = ebp[1];
		ebp = (unsigned*)ebp[0];
	}
	backtrace[i] = 0;
}

/*
 * dump a stored backtrace
 */
void 
dump_stored_stack_trace(int (*__printf)(const char *,...), 
		unsigned *backtrace,
		int max_st_levels)
{
	unsigned int i;
	
	__printf("Backtrace:");

	for (i = 0; backtrace[i] && i < max_st_levels; i++)
		__printf(" %08x", backtrace[i]);

	__printf("\n");
}
