#ifndef _COSMOS_X86_BASE_STACK_H_
#define _COSMOS_X86_BASE_STACK_H_

#include <stdint.h>

#define STACK_SIZE 4 * 1024

typedef uint8_t stack_t[STACK_SIZE];

extern stack_t stack;
extern uint8_t *stack_bottom;
extern uint8_t *stack_top;

#endif /* _COSMOS_X86_BASE_STACK_H_ */
