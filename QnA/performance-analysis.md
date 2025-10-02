# Performance, Code Size & Library Improvements

## Cycles Per Instruction (CPI) and Instructions Per Cycle (IPC)
For processor performance analysis, Cycles Per Instruction (CPI) and Instructions
Per Cycle (IPC) are reciprocal metrics that describe how efficiently a CPU executes
instructions. Analysts use these metrics to pinpoint inefficiencies in software and
architecture. A high IPC or low CPI indicates efficient performance, while a low
IPC or high CPI signifies bottlenecks.

### What factors affect CPI and IPC?
The values of CPI and IPC are not static but vary based on the interaction between
hardware and software. Key factors include:
* **Instruction mix:** The proportion of different types of instructions (e.g., integer,
floating-point, memory access) affects the average CPI and IPC, as some instructions
require more cycles to execute than others.
* **Pipeline hazards:** Modern processors use pipelines to execute multiple instructions
in parallel. Hazards like data dependencies or control hazards (from branches) can cause
the pipeline to stall, increasing CPI and decreasing IPC.
* **Memory hierarchy:** Cache misses force the CPU to retrieve data from slower main
memory, causing significant stalls. The resulting latency increases CPI.
* **Architectural design:** A processor's microarchitecture, such as the number of
execution units and the effectiveness of branch prediction, directly influences its
potential for parallelism and thus its maximum IPC.
* **Instruction-level parallelism (ILP):** A program's ability to expose independent
instructions that can be executed in parallel is a primary driver of high IPC in
superscalar processors.

### How to use CPI and IPC for performance analysis
Instead of relying on a single clock frequency, analysts use CPI and IPC to get a deeper
understanding of processor performance for a given workload.
* **Overall performance:** The total execution time of a program can be expressed as:
```
Execution Time = (Instructions / Program) * CPI * Clock Cycle Time.
```
This is equivalent to:
```
Execution Time = (Instructions / Program) / (IPC * Clock Rate).
```

* **Identifying bottlenecks:** Monitoring CPI and IPC during program execution can reveal
bottlenecks. For example, a sudden drop in IPC could indicate memory-access issues or
pipeline stalls caused by a specific section of code.
* **Comparing different CPUs:** While comparing raw IPC or CPI between different processors
is not always meaningful, it can be effective when running the same binary on different
generations of the same architecture. For example, a higher IPC for the same program on
a newer Intel Core i7 suggests generational improvements in efficiency.

## Valgrind
Valgrind is a powerful instrumentation framework that includes several tools useful for
performance analysis, primarily through detailed profiling. While it's commonly known for
memory error detection (Memcheck), its profiling tools provide insights into CPU and cache
usage, helping identify performance bottlenecks.

Here's how Valgrind is used for performance analysis:
### Callgrind
* Purpose: This tool generates a call graph of your program, counting function calls,
the number of CPU instructions executed within each call, and memory accesses.
* Usage:
```
valgrind --tool=callgrind ./your_program [program_arguments]
```
* Analysis: The output can be visualized with tools like KCachegrind, providing a
graphical representation of the call hierarchy and identifying functions consuming
the most CPU cycles and memory. This helps pinpoint computationally expensive sections
of your code.
### Cachegrind:
* Purpose: Cachegrind simulates the L1/L2 caches and counts cache misses and hits. This
helps in understanding how efficiently your program utilizes the CPU cache. 
* Usage:
```
valgrind --tool=cachegrind ./your_program [program_arguments]

```
* Analysis: By identifying functions with high cache miss rates, you can optimize data
access patterns to improve cache locality and overall performance. Callgrind includes
cache simulation features, making it a comprehensive option for both CPU and cache profiling.

### Massif:
* Purpose: Massif is a heap memory profiler that provides detailed information about
heap memory usage over time. This helps in identifying memory-intensive parts of your
program and potential memory leaks that might impact performance.
* Usage:
```
valgrind --tool=massif ./your_program [program_arguments]
```
* Analysis: Massif generates a graph of heap usage, showing allocations and deallocations.
This can reveal inefficient memory management strategies or unexpected memory growth that
could lead to performance degradation.

## General Considerations:
* **Performance Overhead:** Valgrind instruments your program, which can significantly
slow down execution (4 to 50 times slower). This overhead must be considered when
interpreting results, as it can affect timing measurements.
* **Debugging Information:** For optimal results, compile your program with debugging
information enabled (-g flag in GCC/Clang) to allow Valgrind to provide precise source
code locations for performance issues.
* **Targeted Analysis:** Focus on specific areas of your code that are suspected
performance bottlenecks rather than profiling the entire application, especially for
large programs.

## 1. Performance Analysis
### Q1. You apply -O3 to a program and see a 20% slowdown. What might cause it?
**A: Possible causes:**
* Aggressive inlining increased code size → instruction cache misses.
* Loop unrolling/vectorization overhead on small loops.
* Alignment changes affecting cache/pipeline.
* Increased register pressure → spilling.
* Mis-predicted branch transformations.
* Performance regression in hot path not covered by benchmarks.

### Q2. How would you measure whether a compiler optimization improved performance?
**A:**
* Run representative benchmarks (micro + real-world).
* Use perf to gather metrics (cycles, instructions, cache misses, branch misses).
* Compare IPC and CPI before/after.
* Check variance across runs.
* Ensure correctness is preserved with regression tests.

### Q3. What’s the performance impact of register spilling?
**A:**
 Each spill involves memory access (store/load), which is far slower than register use. Can introduce extra cache misses and stall pipelines.
### Q4. Why might vectorization not always help?
**A:**
* Small data sizes (overhead outweighs benefit).
* Misaligned memory accesses.
* Strided/irregular memory access patterns.
* Increased register pressure → spills.
* Branch-heavy loops.

## 2. Code Size
### Q5. Why does inlining sometimes hurt performance?
**A:**
Increases code size → instruction cache pressure, TLB misses. Can degrade performance even if call overhead was eliminated.

### Q6. How does loop unrolling affect code size and performance?
**A:**
* Benefits: reduces loop overhead, enables better ILP and vectorization.
* Costs: larger binary size, potential cache pressure.
* Tradeoff depends on loop iteration count and target architecture cache sizes.

### Q7. How would you reduce code size in an embedded system?
**A:**
* Use -Os (optimize for size).
* Avoid aggressive inlining.
* Use function deduplication/LTO.
* Use smaller ISAs (ARM Thumb, RISC-V compressed).
* Remove dead code via section GC (--gc-sections).

## 3. Library Improvements (libc/libm/malloc/atomics/crypto)
### Q8. How would you make memcpy faster on Qualcomm’s CPU?
**A:**
* Use SIMD instructions (NEON/SVE).
* Align to cache line boundaries.
* Prefetching for large copies.
* Unroll loops for throughput.
* Select small-copy fallback path.
* Benchmark across sizes to pick thresholds.

### Q9. Why is memmove slower than memcpy?
**A:**
Must handle overlapping memory regions correctly. Often requires direction checks and possibly temporary buffers, adding overhead.

### Q10. How would you improve malloc performance on a multithreaded system?
**A:**
* Use thread-local caches (per-thread arenas).
* Reduce lock contention (lock-free fast path).
* Align allocations to cache lines.
* Avoid fragmentation via segregated free lists.
* Consider specialized allocators (jemalloc, tcmalloc).

### Q11. Why are constant-time operations important in crypto libraries?
**A:**
Prevent side-channel attacks (timing attacks). Branches/data-dependent execution may leak secret information if execution time varies.

### Q12. How are math library (libm) functions optimized for performance?
**A:**
* Polynomial or rational approximations.
* SIMD acceleration for vector math.
* Fast path for common ranges, slow path for edge cases.
* Trade precision for speed (fast-math mode).

## 4. Compiler ↔ Micro-Architecture Tradeoffs
### Q13. How does instruction scheduling help performance?
**A:**
Reorders instructions to avoid stalls (e.g., hide latency of loads behind independent ALU ops). Matches schedule to pipeline characteristics.**

### Q14. If you notice frequent branch mispredictions in generated code, what can be done?
**A:**
* Compiler: convert branches to conditional moves (cmov).
* Rearrange code to favor common paths (likely/unlikely hints).
* Inline small conditionals.
* Use PGO to guide layout.

### Q15. Why does function alignment matter?
**A:** Misaligned functions may cause I-cache inefficiency. Aligning to cache line boundaries reduces fetch stalls.

## 5. Tools & Methodologies
### Q16. How would you profile a performance regression in malloc?
**A:**
* Run benchmarks with perf record/report.
* Measure lock contention, syscalls, and cache misses.
* Use heap profiling tools (e.g., valgrind --tool=massif).
* Compare allocation/free distribution and fragmentation.

### Q17. What does perf stat ./a.out tell you?
**A:** High-level counters: cycles, instructions, IPC, cache misses, branches, branch-misses. Helps correlate compiler/library changes to hardware effects.

### Q18. How would you validate a proposed compiler optimization for libm?
**A:**
* Micro-benchmarks for specific functions (e.g., sin, log).
* Compare accuracy (ULPs) vs speed.
* Check across different input ranges.
* Run full regression suite for correctness.
* Measure across multiple CPUs (not just target).

## 6. Real-World Scenarios

### Q19. Why might SPECint benchmarks improve but SPECfp regress after an optimization?
**A:**
SPECint (integer workloads) benefit from branch/inlining optimizations. SPECfp (floating-point heavy) may suffer due to code size increase or register pressure.

### Q20. You optimized memcpy with vectorization, but performance regressed on small inputs. Why?
**A:**
Setup overhead of SIMD instructions outweighs benefit. Scalar copy may be faster for <64B data. Correct solution: hybrid scalar/vector path.

### 🎯 How to Practice
* Write C snippets, compile with -O2 vs -O3, inspect assembly (objdump -d).
* Run perf stat on microbenchmarks (memcpy, malloc, math loops).
* Be prepared to explain tradeoffs clearly: "Inlining helps performance but hurts code size due to I-cache pressure."