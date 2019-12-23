/*
 * setjmp/longjmp buffer for i386.
 */
#ifndef	C_SETJMP_H
#define	C_SETJMP_H

#define __JMPBUF_LEN	9	/* Sized to match freebsd setjmp buffer */

typedef int jmp_buf[__JMPBUF_LEN];

#endif	//C_SETJMP_H
