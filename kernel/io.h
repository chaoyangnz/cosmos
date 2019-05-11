#ifndef COSMOS_IO_H
#define COSMOS_IO_H

#include <stdint.h>

extern void outb(uint16_t port, uint8_t data);
extern uint8_t inb(uint16_t port);

#endif //COSMOS_IO_H
