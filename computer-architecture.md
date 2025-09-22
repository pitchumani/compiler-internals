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
