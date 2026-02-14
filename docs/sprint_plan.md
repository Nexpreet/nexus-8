# NEXUS-8 — Microcoded CPU in C
## Sprint Roadmap (12 weeks)

### Project Charter (User Request)
Design and implement a custom 8-bit microcoded CPU in C, including:
- A defined ISA (Instruction Set Architecture)
- A microcoded control unit
- An assembler
- Optional 5-stage pipeline simulation
- Basic interrupt capability (simulated)
- Debuggable internal state and repeatable tests

Constraints:
- Learn concepts from books/courses, then implement using original logic.
- Work in weekly sprints with working artifacts at the end of each sprint.

---

## Architecture Vision (High-Level)
Target characteristics:
- 8-bit data width
- 16-bit address space (or smaller early on, expandable)
- 4–8 general purpose registers
- Von Neumann memory model
- Stack support
- Microcoded control unit
- Optional pipeline (final milestone)
- Memory-mapped I/O (simulated)

Quality goals:
- Deterministic execution
- Clean state dump / tracing
- Simple, testable modules
- Clear written specs (ISA + microcode format)

---

# Sprint Plan

## Sprint 1 — Minimal Virtual CPU Loop
**Goal:** Working fetch–decode–execute loop with minimal ISA.
**Deliverable:** Runs simple programs from a byte array.
**Study:** Patterson & Hennessy, COD: Ch.1 and 2.1–2.4 (or NAND2Tetris Weeks 1–2).
**Definition of Done:**
- PC, registers, RAM exist
- HALT works
- Executes ≥4 instructions
- State dump after execution

---

## Sprint 2 — ISA Specification v1
**Goal:** Define instruction formats and encoding rules.
**Deliverable:** Written ISA spec (Markdown/PDF) + encoding diagrams.
**Study:** Patterson & Hennessy: Ch.2.5–2.9.
**Definition of Done:**
- Instruction width + formats defined
- Operand encoding defined
- Immediate strategy defined
- Example binaries provided

---

## Sprint 3 — ALU + Flags
**Goal:** Implement ALU subsystem and flags model.
**Deliverable:** ALU module + tests.
**Study:** Harris & Harris, Digital Design & Computer Architecture (Arithmetic/ALU sections) or Ben Eater ALU videos.
**Definition of Done:**
- ADD/SUB/AND/OR/XOR
- Zero/Carry/Overflow flags documented
- Test programs validate flags

---

## Sprint 4 — Stack + Calls
**Goal:** Add stack pointer + basic call/return mechanism.
**Deliverable:** PUSH/POP/CALL/RET working with a nontrivial program.
**Study:** CS:APP Ch.3 (machine-level) + COD procedures section.
**Definition of Done:**
- Stack behavior documented
- Recursive or nested-call program runs
- Memory map defined

---

## Sprint 5 — Microcoded Control Unit
**Goal:** Replace opcode switch logic with microcode execution.
**Deliverable:** Microinstruction format + microcode store + microcoded execution.
**Study:** Tanenbaum, Structured Computer Organization (microprogramming chapter) or Hamacher microprogrammed control.
**Definition of Done:**
- Instructions execute via micro-ops
- Microcode table externalized
- Microinstruction format documented

---

## Sprint 6 — Assembler (2-Pass)
**Goal:** Build a basic assembler for your ISA.
**Deliverable:** Text assembly → binary output (labels supported).
**Study:** Cooper & Torczon (compiler/assembler topics) + skim Dragon Book lexical section if needed.
**Definition of Done:**
- Labels + symbol table work
- Errors reported clearly
- Sample programs assemble and run

---

## Sprint 7 — Interrupt System (Simulated)
**Goal:** Add interrupt vector table + enable flag + ISR flow.
**Deliverable:** External interrupt simulation + return-from-interrupt behavior.
**Study:** COD exceptions/interrupts section + 8086 interrupt overview (as inspiration).
**Definition of Done:**
- Interrupt triggers and jumps to vector
- ISR runs and returns correctly
- Interrupt enable/disable behaves as documented

---

## Sprint 8 — Memory-Mapped I/O (Simulated Devices)
**Goal:** Add memory-mapped I/O region and at least one device.
**Deliverable:** Console output or timer device.
**Study:** Tanenbaum I/O chapter + OSDev Wiki (MMIO).
**Definition of Done:**
- I/O addresses reserved in memory map
- Reads/writes interact with simulated device
- Spec includes address ranges and behavior

---

## Sprint 9 — Pipeline Simulation v1
**Goal:** Convert to a 5-stage pipeline model (cycle-accurate).
**Deliverable:** Pipeline stages simulated per cycle.
**Study:** COD pipelining chapter.
**Definition of Done:**
- IF/ID/EX/MEM/WB modeled
- Cycle stepping works
- Basic program runs with pipeline

---

## Sprint 10 — Hazards & Forwarding
**Goal:** Implement hazard detection + stalls + forwarding.
**Deliverable:** Correct execution with hazards present.
**Study:** COD hazard detection/forwarding sections.
**Definition of Done:**
- Data hazards handled
- Control hazards handled (baseline strategy)
- Tests demonstrate stall/forward correctness

---

## Sprint 11 — Performance Analysis
**Goal:** Measure CPI, stall cycles, throughput.
**Deliverable:** Small report + benchmark programs.
**Study:** COD performance metrics.
**Definition of Done:**
- CPI measured and reported
- Comparison: pipelined vs non-pipelined
- Results reproducible

---

## Sprint 12 — Architecture Whitepaper + Portfolio Package
**Goal:** Write the formal spec + results as a portfolio artifact.
**Deliverable:** Whitepaper + repo structure polished.
**Definition of Done:**
- ISA spec included
- Microcode format included
- Pipeline model included (if implemented)
- Known limitations + future work listed
