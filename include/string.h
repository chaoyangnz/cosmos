#ifndef _C_STRING_H_
#define _C_STRING_H_

#include <stddef.h>
#include "compiler.h"



size_t strlen(const char *__s);
char *strcpy(char *__dest, const char *__src);
char *strncpy(char *__dest, const char *__src, size_t __n);
char *strdup(const char *__s);
char *strcat(char *__dest, const char *__src);
char *strncat(char *__dest, const char *__src, size_t __n);
int strcmp(const char *__a, const char *__b);
int strncmp(const char *__a, const char *__b, size_t __n);

char *strchr(const char *__s, int __c);
char *strrchr(const char *__s, int __c);
char *strstr(const char *__haystack, const char *__needle);
char *strtok(char *__s, const char *__delim);
char *strtok_r(char *__s, const char *__delim, char **__last);
char *strpbrk(const char *__s1, const char *__s2);
size_t strspn(const char *__s1, const char *__s2);
size_t strcspn(const char *__s1, const char *__s2);

void *memmove(void *__to, const void *__from, unsigned int __n);
void *memset(void *__to, int __ch, unsigned int __n);

#if	!defined(__GNUC__) || defined(SYS_ARM32_SHARK)
void *memcpy(void *__to, const void *__from, unsigned int __n);
int memcmp(const void *s1v, const void *s2v, size_t size);
#else
#define memcpy __builtin_memcpy
#define memcmp __builtin_memcmp
#endif

void * memchr(const void *b, int c, size_t len);

char *strerror(int __errno);

/*
 * Traditional BSD string functions,
 * not defined in ANSI or POSIX but included in Unix CAE.
 * It is preferable to use the ANSI functions in <string.h> in new code.
 */

int bcmp(const void *s1, const void *s2, size_t n);
void bcopy(const void *from, void *to, size_t n);
void bzero(void *to, size_t n);

int ffs(int i);

char *index(const char *s, int c);
char *rindex(const char *s, int c);

int strcasecmp(const char *s1, const char *s2);
int strncasecmp(const char *s1, const char *s2, size_t n);

/* This isn't in the CAE manual... */
char *strsep(char **stringp, const char *delim);



#endif /* _C_STRING_H_ */
