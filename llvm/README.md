# 🧵 Compiler Refresher: Source to Assembly (with LLVM Focus)

This guide covers the traditional compiler pipeline and how it maps to LLVM, including phases, passes, and IR representations.

---

## 🛠️ Traditional Compiler Pipeline

| Phase               | Description |
|---------------------|-------------|
| **Lexical Analysis**  | Tokenizes source code. |
| **Syntax Analysis**   | Builds Abstract Syntax Tree (AST). |
| **Semantic Analysis** | Type checks, resolves symbols. |
| **IR Generation**     | Produces intermediate code (e.g., 3-address code). |
| **Optimization**      | Improves performance (e.g., loop unrolling, dead code elimination). |
| **Code Generation**   | Emits target assembly code. |
| **Assembly & Linking**| Generates object file and links it into an executable. |

---

## 🔧 LLVM Compilation Flow
```
[Source Code]
↓ (Clang: Frontend)
[LLVM IR (High-Level)]
↓ (LLVM Middle-End Optimizer)
[Optimized LLVM IR]
↓ (LLVM Backend CodeGen)
[Target Assembly]
```

---

## 🎯 LLVM Compiler Phases

### 1. Frontend (Clang)
- Parses source, builds AST, runs semantic checks.
- Converts AST to **LLVM IR** (SSA-form, typed).
- IR Example:
  ```llvm
  %1 = add i32 %a, %b

### 2. Middle-End (opt)
Applies machine-independent optimizations:
- Constant propagation
- Dead code elimination
- Loop unrolling, LICM
- Tools: `opt`, `llvm-link`

### 3. Backend (llc)
- Performs:
  - Instruction selection
  - Register allocation
  - Scheduling
- Emits target-specific assembly
- Tools: `llc`, `llvm-mc`, `clang`

## 🔄 LLVM IR Levels
| IR Level	| Description |
|-----------|-------------|
| LLVM IR	| SSA-form, high-level IR. |
| SelectionDAG	| Pattern-matched instruction graphs. |
| MIR	| Machine IR: target-specific operations. |
| Assembly	| Target assembly (e.g., x86, ARM). |

## 🧪 Example: C to LLVM IR
C Code:
```c
int add(int a, int b) {
  return a + b;
}
```
LLVM IR:
```llvm
define i32 @add(i32 %a, i32 %b) {
entry:
  %addtmp = add i32 %a, %b
  ret i32 %addtmp
}
```
## 🧰 Toolchain Commands
```bash
# 1. Generate LLVM IR from C
clang -S -emit-llvm test.c -o test.ll

# 2. Apply optimization passes
opt -O2 test.ll -o test_opt.ll

# 3. Convert IR to target assembly
llc test_opt.ll -o test.s

# 4. Assemble and link
clang test.s -o test_exec
```

## 🔍 Common LLVM Tools
| Tool	| Purpose |
|-------|---------|
| clang	| Frontend: C/C++ → LLVM IR |
| opt	| Optimizer for LLVM IR |
| llc	| LLVM IR → Target Assembly |
| llvm-as	| IR → Bitcode |
| llvm-dis	| Bitcode → IR |
| llvm-link	| Combine multiple IR files |
| clang -cc1	| Access Clang internals (advanced) |

## ✅ Typical Optimization Passes
| Pass	| Purpose |
|--|--|
| mem2reg	| Promote memory to SSA registers |
| instcombine	| Combine redundant instructions |
| gvn	| Global value numbering |
| licm	| Loop-invariant code motion |
| dce	| Dead code elimination |
| loop-unroll	| Loop unrolling |

## 📚 Resources
- [LLVM Language Reference](https://llvm.org/docs/LangRef.html)
- [Clang Internals](https://clang.llvm.org/docs/index.html)
- [LLVM Pass Documentation](https://llvm.org/docs/Passes.html)