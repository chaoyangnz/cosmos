//
// Created by Chao Yang on 2019-04-22.
//

#include <kernel/util.h>
#include <stddef.h>

uint32_t
bytes_to_u32(uintptr_t addr) {
    uint32_t u32 = 0;
    for(int i = 0; i < 4; i++) {
        uint8_t* ptr =  (void*)(addr + i);
        u32 |=  ((*ptr) << (i * 8));
    }
    return u32;
}

uint64_t
bytes_to_u64(uintptr_t addr) {
    uint64_t u64 = 0;
    uint8_t* ptr;
    for(size_t i = 0; i < 8; i++) {
        ptr = (void*)(addr + i);
        u64 |= ((*ptr) << (i << 3));
    }
    return u64;
}