#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#include "nexus_cpu.h"
#include "nexus_isa.h"

#define MAX_STEPS 1000

/*
 * DISCLAIMER: Testove je napisao chatgpt jer ZAISTA ne mogu
 */

static void write_ins_le(nexus_cpu_t *cpu, uint16_t addr, instruction_t ins)
{
    cpu->memory[addr]     = (uint8_t)(ins & 0xFF);
    cpu->memory[addr + 1] = (uint8_t)((ins >> 8) & 0xFF);
}

static void run_until_halt(nexus_cpu_t *cpu)
{
    for (int i = 0; i < MAX_STEPS && !cpu->halted; ++i) {
        nexus_cpu_step(cpu);
    }
    assert(cpu->halted && "CPU did not halt");
}

static void test_loadi_addi(void)
{
    nexus_cpu_t cpu;
    nexus_cpu_reset(&cpu);

    write_ins_le(&cpu, 0, encode_immediate(OP_LOADI, 1, 5));
    write_ins_le(&cpu, 2, encode_immediate(OP_ADDI,  1, 3));
    write_ins_le(&cpu, 4, encode_register(OP_HALT,   0, 0));

    run_until_halt(&cpu);

    assert(cpu.pc == 6);
    assert(cpu.regs[1] == 8);
}

static void test_add_rr(void)
{
    nexus_cpu_t cpu;
    nexus_cpu_reset(&cpu);

    write_ins_le(&cpu, 0, encode_immediate(OP_LOADI, 1, 5));
    write_ins_le(&cpu, 2, encode_immediate(OP_LOADI, 2, 3));
    write_ins_le(&cpu, 4, encode_register(OP_ADD,    1, 2));
    write_ins_le(&cpu, 6, encode_register(OP_HALT,   0, 0));

    run_until_halt(&cpu);

    assert(cpu.pc == 8);
    assert(cpu.regs[1] == 8);
}

static void test_signed_imm6(void)
{
    nexus_cpu_t cpu;
    nexus_cpu_reset(&cpu);

    write_ins_le(&cpu, 0, encode_immediate(OP_LOADI, 0, 5));
    write_ins_le(&cpu, 2, encode_immediate(OP_ADDI,  0, -1));
    write_ins_le(&cpu, 4, encode_register(OP_HALT,   0, 0));

    run_until_halt(&cpu);

    assert(cpu.regs[0] == 4);
}

static void test_nop(void)
{
    nexus_cpu_t cpu;
    nexus_cpu_reset(&cpu);

    write_ins_le(&cpu, 0, encode_immediate(OP_LOADI, 0, 9));
    write_ins_le(&cpu, 2, encode_register(OP_NOP,    0, 0));
    write_ins_le(&cpu, 4, encode_immediate(OP_ADDI,  0, 1));
    write_ins_le(&cpu, 6, encode_register(OP_HALT,   0, 0));

    run_until_halt(&cpu);

    assert(cpu.pc == 8);
    assert(cpu.regs[0] == 10);
}

static void test_invalid_opcode(void)
{
    nexus_cpu_t cpu;
    nexus_cpu_reset(&cpu);

    instruction_t bad = (instruction_t)(0xF << 12);

    write_ins_le(&cpu, 0, bad);

    for (int i = 0; i < 10 && !cpu.halted; ++i) {
        nexus_cpu_step(&cpu);
    }

    assert(cpu.halted);
}

static void test_edge_imm6_values()
{
    nexus_cpu_t cpu;
    nexus_cpu_reset(&cpu);

    write_ins_le(&cpu, 0, encode_immediate(OP_LOADI, 0, 31));
    write_ins_le(&cpu, 2, encode_immediate(OP_LOADI,  1, -32));
    write_ins_le(&cpu, 4, encode_immediate(OP_LOADI,   2, -1));
    write_ins_le(&cpu, 6, encode_register(OP_HALT,   0, 0));

    run_until_halt(&cpu);

    assert(cpu.regs[0] == 31);
    assert(cpu.regs[1] == (uint8_t)-32);
    assert(cpu.regs[2] == 255);
}

int main(void)
{
    test_loadi_addi();
    test_add_rr();
    test_signed_imm6();
    test_nop();
    test_invalid_opcode();
    test_edge_imm6_values();

    puts("All Sprint 2 tests passed.");
    return 0;
}
