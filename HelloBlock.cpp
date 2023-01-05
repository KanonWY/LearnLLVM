#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"

using namespace llvm;

int main() {

    LLVMContext context;
    IRBuilder<> builder(context);
    // Create a module
    Module *module = new Module("HelloModule", context);

    // Add a function
    Type *voidType = Type::getVoidTy(context);
    FunctionType *functionType = FunctionType::get(voidType, false);
    Function *function = Function::Create(
        functionType, GlobalValue::ExternalLinkage, "HelloFunction", module);

    BasicBlock *block = BasicBlock::Create(context, "entry", function);
    builder.SetInsertPoint(block);

    verifyFunction(*function);
    module->print(outs(), nullptr);
    return 0;
}