# Instruction Scheduling
Instruction scheduling optimization is a compiler optimization technique that reorders
the sequence of machine code instructions to minimize the total number of cycles
required to execute a program, particularly on pipelined processors. The goal is to
maximize instruction-level parallelism (ILP) by hiding latencies and keeping the
processor's execution units busy. This involves respecting data and control
dependencies between instructions while finding an optimal or near-optimal
execution order.

## Key aspects of instruction scheduling:
* **Data Dependencies:** Instructions that rely on the results of previous instructions
must maintain their relative order to ensure correctness.
* **Control Dependencies:** Branching instructions affect the flow of execution, and
reordering must preserve the program's logic.
* **Processor Architecture:** Instruction scheduling is highly dependent on the target
processor's pipeline structure, number of functional units, and instruction latencies.
* **Types of Scheduling:**
  * Local Scheduling: Within a single basic block (straight-line code).
  * Global Scheduling: Across basic block boundaries, potentially moving instructions across branches.
  * Modulo Scheduling: A technique for software pipelining, optimizing loops by overlapping iterations.

