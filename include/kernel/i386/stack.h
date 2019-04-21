#ifndef _COSMOS_X86_BASE_STACK_H_
#define _COSMOS_X86_BASE_STACK_H_

#define BASE_STACK_SIZE		65536

extern char base_stack_start[], base_stack_end[];

/* For the sake of unix mode, where stacks are not always BASE_STACK_SIZE. */
extern int  base_stack_size;

#endif /* _COSMOS_X86_BASE_STACK_H_ */
