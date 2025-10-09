#ifndef LLVM_ANALYSIS_DUMP_VARIABLES_H_
#define LLVM_ANALYSIS_DUMP_VARIABLES_H_

#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Passes/PassPlugin.h"

namespace llvm {

class DumpVariables : public PassInfoMixin<DumpVariables> {
public:
    DumpVariables() = default;
    void checkGlobals(Module &M);
    void checkFunction(Function &F);
    PreservedAnalyses run(Module &M, ModuleAnalysisManager &) {
        errs() << "DumpVariables pass - Module: " << M.getName() << "\n";
        checkGlobals(M);
        for (auto &F : M) checkFunction(F);
        return PreservedAnalyses::all();
    }
};

}  // namespace llvm

#endif // LLVM_ANALYSIS_DUMP_VARIABLES_H_
