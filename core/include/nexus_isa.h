//
// Created by luka on 2/13/26.
//

#ifndef NEXUS_ISA_H
#define NEXUS_ISA_H

#include <stdint.h>

enum {
    //Low byte operandi
    OP_NOP = 0x00,
    OP_HALT = 0x01,

    //High byte opcode
    OP_LOADI_BASE = 0x10, //od 0x10 do 0x17
    OP_ADDI_BASE = 0x20 // od 0x20 do 0x27
};

static inline uint8_t reg_from_opcode(uint8_t opcode, uint8_t base) {

    return (uint8_t)(opcode - base);
}

static inline int is_loadi(uint8_t opcode) {
    return opcode >= OP_LOADI_BASE && opcode < (OP_LOADI_BASE + 8);
}

static inline int is_addi(uint8_t opcode) {
    return opcode >= OP_ADDI_BASE && opcode < (OP_ADDI_BASE + 8);
}

#endif //NEXUS_ISA_H