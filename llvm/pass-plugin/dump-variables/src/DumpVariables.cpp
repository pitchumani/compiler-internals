#include "DumpVariables.h"

using namespace llvm;

void DumpVariables::checkGlobals(Module &M) {
    errs() << "Globals:\n";
    for (GlobalVariable &G : M.globals()) {
        errs() << "  - " << G.getName() << " (";
        G.getValueType()->print(errs());
        errs() << ")\n";
    }
}

void DumpVariables::checkFunction(Function &F) {
    errs() << "Function: " << F.getName() << "\n";
    errs() << "  Variables:\n";
    for (BasicBlock &bb : F) {
        for (Instruction &inst : bb) {
            if (auto *allocaInst = dyn_cast<AllocaInst>(&inst)) {
                if (allocaInst->hasName())
                    errs() << "  " << allocaInst->getName() << " (";
                else
                    errs() << "  <unnamed> (";
                allocaInst->getAllocatedType()->print(errs());
                errs() << ")\n";
            }
        }
    }
}

// This is the entry point LLVM uses to register your pass
extern "C" ::llvm::PassPluginLibraryInfo llvmGetPassPluginInfo() {
    return {
        LLVM_PLUGIN_API_VERSION, "DumpVariablesPass", LLVM_VERSION_STRING,
        [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, ModulePassManager &MPM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                    if (Name == "dumpVars") {
                        MPM.addPass(DumpVariables());
                        return true;
                    }
                    return false;
                });
        }
    };
}

