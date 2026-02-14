#ifndef NEXUS_CPU_H
#define NEXUS_CPU_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t  regs[8];
    uint16_t pc;
    uint16_t sp;
    uint8_t  flags;
    uint8_t  memory[65536];
    bool halted;
} nexus_cpu_t;

void nexus_cpu_reset(nexus_cpu_t *cpu);
int nexus_cpu_step(nexus_cpu_t *cpu);

#endif
