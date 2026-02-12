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

    return 0;
}
