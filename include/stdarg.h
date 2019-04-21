#ifndef _SYS_C_STDARG_H_
#define _SYS_C_STDARG_H_

#define __va_size(type) ((sizeof(type)+3) & ~0x3)

#ifndef _VA_LIST_
#define _VA_LIST_
typedef	char * va_list;
#endif

#define	va_start(pvar, lastarg)			\
	((pvar) = (char*)(void*)&(lastarg) + __va_size(lastarg))
#define	va_end(pvar)
#define	va_arg(pvar,type)			\
	((pvar) += __va_size(type),		\
	 *((type *)((pvar) - __va_size(type))))

#endif /* _SYS_X86_C_STDARG_H_ */
