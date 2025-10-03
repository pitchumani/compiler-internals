# Compute Architecture
* [Memory Organization](#memory-organization)
* [Cache](#cache)
* [Pipeline](#pipeline)

## Memory Organization
The memory system is structured as a hierarchy, balancing speed, cost, and capacity.
### Memory Hierarchy
* **Register**: The smallest, fastest, and most expensive memory, located directly
within the CPU. They hold data that is being processed.
* **Cache Memory (L1, L2, L3)**: Fast memory levels that store frequently accessed
data and instructions close to the CPU.
* **Main Memory (RAM)**: The computer's primary working memory, larger and slower than
cache. All executing programs must reside here.
* **Secondary Storage (HDD/SSD)**: Large, slow, non-volatile memory for long-term
data storage.
### Memory Management
* **Virtual Memory**: A technique that allows a program to use more memory than is
physically available in RAM by swapping data between main memory and secondary storage.
* **Uniform Memory Access (UMA)**: A memory architecture where all processors have
equal and uniform access times to all memory locations.
* **Non-Uniform Memory Access (NUMA)**: An architecture where memory access times
vary dependeing on the memory's location relative to the processor. Processors can
access local memory faster than remote memory.

## Pipeline
Pipelining is a technique that increases a processor's instruction
throughput by allowing multiple instructions to be in different
stages of execution simultaneously. A typical RISC instruction
pipeline consists of these stages.
* Instruction Fetch
* Instruction Decode
* Execute
* Memory Access
* Write Back

### Pipeline Hazards
A hazard occurs when the next instruction cannot execute in the
following clock cycle, which can cause the pipeline to stall or
introduce incorrect results.
* **Structural Hazard**: Occurs when two instructions need the same
hardware resource at the same time. E.g. if a pipeline has only a
single memory port, a load or store instruction cannot access it at
the same time as the next instruction being fetched.
* **Data Hazard**: Arises when an instruction depends on the result
of a previous instruction that is still in the pipeline.
** Read After Write (RAW): An instruction tries to read a register
before a preceding instruction has written its new value.
** Write After Read (WAR): An instruction tries to write a register
before a preceding instruction has read its old value.
** Write After Write (WAW): Two instructions attempt to write to the
same register at the same time.
* **Control Hazard**: Occurs with branch and jump instructions, where
the processor may not know which instruction to fetch next. The
pipeline might make a wrong prediction and fetch instruction that
later need to be discarded, wasting clock cycles.

### Hazard Resolution
Processors use techniques such as forwarding (or bypassing) to pass results
between pipeline stages and avoid stalling. Branch prediction and speculative
execution are used to minimize the control harzards.

## Cache
The cache is a small, fast memory that stores copies of frequently used data
from main memory to reduce access time. It is organized in a hierarchy (L1, L2,
L3) with varying speeds and sizes.

### Cache Mapping
Cache mapping determines where a block from main memory can be placed in the cache.
* **Direct Mapped**: Each block of main memory maps to exactly one specific line
in the cache. This is simple but can lead to frequent conflicts if two frequently
used blocks map to same cache line.
* **Fully Associative**: A block from main memory can be placed in any available
line in the cache. This reduces conflict misses but requires a more complex and
expensive hardware design to search all possible locations simultaneously.
* **Set Associative**: A compromise where the cache is divided into sets, and each
block from main memory maps to a specific set. Within that set, the block can be
placed in any available cache line.

### Cache Write Policies
* **Write-through**: Data is written to both the cache and main memory at the same
time. This is simpler and more reliable but can be slower due to main memory latency.
* **Write-back**: Data is written only to the cache. A "dirty bit" is set to indicate
that the block has been modified. The block is written to main memory only when it
is replaced from the cache.

## Architecture Comparisons
AVR, ARM, and x86 are three distinct processor architectures, each with a different
design philosophy and purpose. AVR is an 8-bit microcontroller known for its simple
RISC architecture and low power usage, ARM uses a more complex RISC design suitable
for mobile and embedded devices, and x86 is a powerful, legacy-burdened CISC
architecture primarily used in personal computers and servers. 

Architecture comparison

| Feature |	AVR (8-bit microcontrollers) |	ARM (Advanced RISC Machines)|	x86 (Intel, AMD) |
|:---|:---|:---|:---|
| Instruction Set|	8-bit RISC: A single-chip microcontroller family with a modified Harvard architecture. Instructions are 16 or 32 bits wide, and the instruction set is relatively orthogonal, making it easy for compilers. |	32/64-bit RISC: Uses a RISC instruction set, focusing on simple instructions that execute quickly. Modern ARM architecture, including ARMv8-A, added support for 64-bit instructions. |	CISC (Complex Instruction Set Computer): Employs complex, variable-length instructions, with a history of backward compatibility. Modern x86 processors still execute CISC instructions, but translate them into simpler micro-operations for internal execution. |
| Microarchitecture	| Simple, two-stage pipeline: The basic AVR core uses a single-level pipeline where one instruction is executed while the next is fetched, achieving up to 1 MIPS per MHz. |	Scalable pipeline: ARM uses deeper pipelines that vary by core. Early ARM7 cores used a simple 3-stage pipeline, while modern cores have longer pipelines (5+ stages) with more complex features for higher performance.|	Deep and complex pipelines: Modern x86 processors use very deep and sophisticated pipelines (often 14+ stages) with features like out-of-order execution, speculative execution, and dynamic scheduling to maximize performance. |
| Address Space	| Modified Harvard architecture: Has separate address spaces and buses for program memory (flash) and data memory (SRAM and registers). Some data can be read from flash memory using special instructions, but not directly addressed like in RAM. |	Unified memory space: A 32-bit ARM processor addresses a flat, 4GB address space, while 64-bit versions support much larger virtual address spaces (e.g., 48 bits on some implementations). Recent ARMv8-A architecture supports a 64-bit address space.	| Hierarchical memory space with virtual memory: Modern x86 processors use a 64-bit architecture with 48 meaningful bits for virtual addressing, providing an enormous address space managed by the operating system. The address space is split into user space and kernel space. |
| Operand Handling | Register-based: All arithmetic and logic operations are performed on 32 general-purpose 8-bit registers. Memory access is handled by separate load/store instructions, often using 16-bit indirect pointer registers (X, Y, and Z). | Load/store: Uses a load/store architecture where data processing instructions operate exclusively on registers. Memory access is performed using explicit load and store instructions. | Memory-based and register-based: Allows many instructions to operate directly on memory locations, combining memory access with a data processing operation. This offers more flexibility at the cost of complexity. |
| Power Consumption | Extremely low: Optimized for minimal power consumption, making it ideal for battery-powered or embedded applications. | Low to moderate: Designed for energy efficiency, which is why ARM dominates the mobile market. Power usage varies widely depending on the specific core and application. High: Prioritizes performance over power efficiency. | Power consumption is significantly higher than ARM, making it less suitable for most mobile applications. |
| Application | Embedded systems and microcontrollers: Best suited for simple, real-time tasks and hardware control in devices like Arduino boards, appliances, and sensors. | Mobile devices and servers: Dominates the smartphone, tablet, and increasingly, the server market due to its high performance and power efficiency. Used in devices like the Raspberry Pi. | Personal computers and servers: The dominant architecture for high-performance desktop PCs, laptops, and cloud computing data centers. |

