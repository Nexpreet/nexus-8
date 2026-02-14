#include "nexus_cpu.h"
#include "nexus_isa.h"

void nexus_cpu_reset(nexus_cpu_t *cpu)
{
    for (int i = 0; i < 8; ++i) {
        cpu->regs[i] = 0;
    }

    cpu->pc = 0x0000;
    cpu->sp = 0xFFFF;
    cpu->flags = 0;

    for (int i = 0; i < 65536; ++i) {
        cpu->memory[i] = 0;
    }

    cpu->halted = false;
}

int nexus_cpu_step(nexus_cpu_t *cpu) {

    if (cpu->halted) return 1;

    if (cpu->pc > 0xFFFE) {
        cpu->halted = true;
        return -1;
    }

    //fetch
    uint8_t lo = cpu->memory[cpu->pc];
    uint8_t hi = cpu->memory[cpu->pc + 1];

    instruction_t instruction = (instruction_t)((hi << 8) | lo);
    cpu->pc += 2;
    //decode and execute

    uint8_t opcode = get_opcode(instruction);
    uint8_t rd = get_rd(instruction);


    switch (opcode) {

        case OP_NOP: return 0;

        case OP_HALT: {
            cpu->halted = true;
            return 1;
        }

        case OP_LOADI: {
            int8_t immediate = get_imm6_s(instruction);
            cpu->regs[rd] = (uint8_t)immediate;
            return 0;
        }

        case OP_ADDI: {
            int8_t immediate = get_imm6_s(instruction);
            cpu->regs[rd] += immediate;
            return 0;
        }
        case OP_ADD: {
            uint8_t rs = get_rs(instruction);
            cpu->regs[rd] += cpu->regs[rs];
            return 0;
        }
        default: {
            cpu->halted = true;
            return -2;
        }

    }
}
