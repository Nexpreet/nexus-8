//
// Created by luka on 2/13/26.
//

#ifndef NEXUS_ISA_H
#define NEXUS_ISA_H

#include <stdint.h>

typedef uint16_t instruction_t;

enum {

    OP_NOP = 0x0,
    OP_HALT = 0x1,
    OP_LOADI = 0x2,
    OP_ADDI = 0x3,
    OP_ADD = 0x4

};

static inline uint8_t get_opcode(instruction_t instruction) {
    return (instruction >> 12) & 0xF;
}

static inline uint8_t get_rd(instruction_t instruction) {
    return (instruction >> 9) & 0x7;
}

static inline uint8_t get_rs(instruction_t instruction) {
    return (instruction >> 6) & 0x7;
}

static inline uint8_t get_imm6_u(instruction_t instruction) {
    return (instruction & 0x3F);
}

static inline int8_t get_imm6_s(instruction_t instruction) {
    uint8_t imm6 = get_imm6_u(instruction);

    return (imm6 & 0x20) ? (int8_t)(imm6 | 0xC0) : (int8_t)imm6;
}

static inline instruction_t encode_register(uint8_t opcode, uint8_t rd, uint8_t rs) {
    return (instruction_t)((opcode & 0xF) << 12) | (instruction_t)((rd & 0x7) << 9) | (instruction_t)((rs & 0x7) << 6);
}

static inline instruction_t encode_immediate(uint8_t opcode, uint8_t rd, int8_t imm6) {

    uint8_t uimm6 = get_imm6_u(imm6);
    return (instruction_t)((opcode & 0xF) << 12) | (instruction_t)((rd & 0x7) << 9) | (instruction_t)uimm6;
}



#endif //NEXUS_ISA_H