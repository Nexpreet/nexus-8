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

void nexus_cpu_step(nexus_cpu_t *cpu) {
    while (!(cpu->halted)){

        uint8_t opcode = cpu->memory[cpu->pc]; //cita opcode
        uint8_t operand = cpu->memory[cpu->pc + 1]; //cita operand

        cpu->pc += 2; //step Program Counter za dva

        if (opcode == OP_HALT)cpu->halted = true;
        else if (opcode == OP_NOP) continue;
        else if (is_addi(opcode)) {
            cpu->regs[reg_from_opcode(opcode, OP_ADDI_BASE)] += operand;
        }
        else if (is_loadi(opcode)) {
            cpu->regs[reg_from_opcode(opcode, OP_LOADI_BASE)] = operand;
        }
        else {
            cpu->halted = true;
        }
    }
}
