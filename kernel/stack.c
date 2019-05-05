#include <kernel/stack.h>

stack_t stack;
addr_t stack_bottom = &stack[0];
addr_t stack_top = &stack[STACK_SIZE-1];