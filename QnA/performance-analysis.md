# Performance, Code Size & Library Improvements
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