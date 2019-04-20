#ifndef _C_STDLIB_H_
#define _C_STDLIB_H_

#include <stddef.h>
#include <sys/i386/types.h>
#include "compiler.h"


#define RAND_MAX 0x7fffffff

#define MB_CUR_MAX	1	/* We don't do locales, so it's always 1. */
#define MB_LEN_MAX	1



/*
 * These function prototypes are roughly in the same order
 * as their descriptions in the ISO/ANSI C standard, section 7.10.
 */

#define atoi(str) ((int)atol(str))
long atol(const char *__str);
long strtol(const char *__p, char **__out_p, int __base);
unsigned long strtoul(const char *__p, char **__out_p, int __base);
double   strtod (const char *, char **);
double   atof (const char *);

int rand(void);
void srand(unsigned __seed);

/* Don't macro expand protos please. */
#ifndef MALLOC_IS_MACRO
void *malloc(size_t __size);
void *calloc(size_t __nelt, size_t __eltsize);
void *realloc(void *__buf, size_t __new_size);
void free(void *__buf);

/* OSKit additions */
void *mustmalloc(size_t __size);
void *mustcalloc(size_t __nelt, size_t __eltsize);

#endif /* MALLOC_IS_MACRO */

void abort(void) NORETURN;
void exit(int __status) NORETURN;

/* OSKit additions */
void panic(const char *__format, ...) NORETURN;

int atexit(void (*__function)(void));

char *getenv(const char *__name);

void qsort(void *__array, size_t __nelt, size_t __eltsize,
	   int (*__cmp)(void *, void *));

#define abs(n) __builtin_abs(n)




#endif /* _C_STDLIB_H_ */
