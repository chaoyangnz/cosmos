/*
 * setjmp/longjmp buffer for i386.
 */
#ifndef	_SYS_X86_C_SETJMP_H_
#define	_SYS_X86_C_SETJMP_H_

#define __JMPBUF_LEN	9	/* Sized to match freebsd setjmp buffer */

typedef int jmp_buf[__JMPBUF_LEN];

#endif	/* _SYS_X86_C_SETJMP_H_ */
