#ifndef _COSMOS_X86_BASE_IDT_H_
#define _COSMOS_X86_BASE_IDT_H_

#include <oskit/compiler.h>
#include <oskit/x86/seg.h>


/* The base environment provides a full-size 256-entry IDT.
   This is needed, for example, under VCPI or Intel MP Standard PCs.  */
#define IDTSZ	256

extern struct x86_gate base_idt[IDTSZ];


/* Note that there is no base_idt_init() function,
   because the IDT is used for both trap and interrupt vectors.
   To initialize the processor trap vectors, call base_trap_init().
   Inititalizing hardware interrupt vectors is platform-specific.  */


OSKIT_BEGIN_DECLS
/* Load the base IDT into the CPU.  */
extern void base_idt_load(void);
OSKIT_END_DECLS


#endif /* _COSMOS_X86_BASE_IDT_H_ */
