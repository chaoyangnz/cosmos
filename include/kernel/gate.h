#ifndef COSMOS_GATE_H
#define COSMOS_GATE_H


/*
 * Trap, interrupt, or call gate.
 */
typedef struct {
    uint32_t	offset_low      :16,	/* gdt_address 0..15 */
            selector        :16,
            word_count      :8,
            access          :8,
            offset_high     :16;	/* gdt_address 16..31 */
} x86_gate_t;



#endif //COSMOS_GATE_H
