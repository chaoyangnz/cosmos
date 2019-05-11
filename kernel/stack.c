#include "stack.h"

stack_t stack;
uint8_t *stack_bottom = &stack[0];
uint8_t *stack_top = &stack[STACK_SIZE-1];