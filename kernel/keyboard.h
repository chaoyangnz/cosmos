#ifndef COSMOS_KEYBOARD_H
#define COSMOS_KEYBOARD_H

#include <stdint.h>

#define KBD_DATA_PORT   0x60

/* Alphabet */
#define KBD_SC_A        0x1e
#define KBD_SC_B        0x30
#define KBD_SC_C        0x2e
#define KBD_SC_D        0x20
#define KBD_SC_E        0x12
#define KBD_SC_F        0x21
#define KBD_SC_G        0x22
#define KBD_SC_H        0x23
#define KBD_SC_I        0x17
#define KBD_SC_J        0x24
#define KBD_SC_K        0x25
#define KBD_SC_L        0x26
#define KBD_SC_M        0x32
#define KBD_SC_N        0x31
#define KBD_SC_O        0x18
#define KBD_SC_P        0x19
#define KBD_SC_Q        0x10
#define KBD_SC_R        0x13
#define KBD_SC_S        0x1f
#define KBD_SC_T        0x14
#define KBD_SC_U        0x16
#define KBD_SC_V        0x2f
#define KBD_SC_W        0x11
#define KBD_SC_X        0x2d
#define KBD_SC_Y        0x15
#define KBD_SC_Z        0x2c

/* Numeric keys */
#define KBD_SC_1        0x02
#define KBD_SC_2        0x03
#define KBD_SC_3        0x04
#define KBD_SC_4        0x05
#define KBD_SC_5        0x06
#define KBD_SC_6        0x07
#define KBD_SC_7        0x08
#define KBD_SC_8        0x09
#define KBD_SC_9        0x0a
#define KBD_SC_0        0x0b

/* Special keys */
#define KBD_SC_ENTER    0x1c
#define KBD_SC_SPACE    0x39
#define KBD_SC_BS       0x0e
#define KBD_SC_LSHIFT   0x2a
#define KBD_SC_RSHIFT   0x36
#define KBD_SC_DASH     0x0c
#define KBD_SC_EQUALS   0x0d
#define KBD_SC_LBRACKET 0x1a
#define KBD_SC_RBRACKET 0x1b
#define KBD_SC_BSLASH   0x2b
#define KBD_SC_SCOLON   0x27
#define KBD_SC_QUOTE    0x28
#define KBD_SC_COMMA    0x33
#define KBD_SC_DOT      0x34
#define KBD_SC_FSLASH   0x35
#define KBD_SC_TILDE    0x29
#define KBD_SC_CAPSLOCK 0x3a
#define KBD_SC_TAB      0x0f

extern uint8_t keyboard__read_scan_code();
extern char keyboard__scan_code_to_ascii(uint8_t scan_code);

#endif //COSMOS_KEYBOARD_H
