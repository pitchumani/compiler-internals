#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Verifier.h" // For verifying generated IR

int main() {
    llvm::LLVMContext context;
    llvm::Module *module = new llvm::Module("my_module", context);
    llvm::IRBuilder<> builder(context);

    // Define main function: int main() { return 42; }
    llvm::FunctionType *funcType = llvm::FunctionType::get(builder.getInt32Ty(), false);
    llvm::Function *mainFunc = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "main", module);

    llvm::BasicBlock *entryBlock = llvm::BasicBlock::Create(context, "entry", mainFunc);
    builder.SetInsertPoint(entryBlock);

    llvm::Value *retVal = builder.getInt32(42); // Create a constant integer 42
    builder.CreateRet(retVal); // Create a return instruction

    // Verify the generated module
    llvm::verifyModule(*module);

    // Print the LLVM IR to stdout
    module->print(llvm::outs(), nullptr);

    delete module;
    return 0;
}

