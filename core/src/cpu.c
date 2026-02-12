#include "nexus_cpu.h"

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
}

void nexus_cpu_step(nexus_cpu_t *cpu)
{
    (void)cpu;
}
