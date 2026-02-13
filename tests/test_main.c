#include <assert.h>
#include "nexus_cpu.h"

int main(void)
{
    nexus_cpu_t cpu;
    nexus_cpu_reset(&cpu);

    assert(cpu.pc == 0x0000);
    assert(cpu.sp == 0xFFFF);
    assert(cpu.flags == 0);

    for (int i = 0; i < 8; ++i) {
        assert(cpu.regs[i] == 0);
    }

    cpu.memory[0] = 0x10; cpu.memory[1] = 0x05; //LOADI R0, 5
    cpu.memory[2] = 0x20; cpu.memory[3] = 0x03; //ADDI R0, 3
    cpu.memory[4] = 0x01; //HALT
    cpu.memory[5] = 0x00; //NOP

    nexus_cpu_step(&cpu);
    //Ocekivani rezultat za R0 je 8
    assert(cpu.regs[0] == 8);

    nexus_cpu_reset(&cpu);

    cpu.memory[0] = 0x30;
    nexus_cpu_step(&cpu);
    assert(cpu.halted == true); //proveravamo da li procesor haltuje za nevazeci opcode

    nexus_cpu_reset(&cpu);

    cpu.memory[0] = 0x10; cpu.memory[1] = 0x5; //LOADI R0, 0
    cpu.memory[2] = 0x20; cpu.memory[3] = 0xFF; //ADDI R0, 0x80
    cpu.memory[4] = 0x01;
    nexus_cpu_step(&cpu);
    assert(cpu.regs[0] == 4);

    return 0;
}
