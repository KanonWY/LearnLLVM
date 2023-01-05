#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"

#include <vector>

using namespace llvm;

int main() {
    LLVMContext context;
    IRBuilder<> builder(context);

    Module* module = new Module("Test.c", context);

    std::vector<Type*> parameters(1, builder.getInt32Ty());
    FunctionType* functionType =
        FunctionType::get(builder.getInt32Ty(), parameters, false);

    Function* function = Function::create(
        functionType, GlobalValue::ExternalLinkage, "Test", module);

    // add an argument to the function

    Value* arg = function->getArg(0);
    arg->setName("a");

    // Add some basic blocks to the function
    BasicBlock* entryBlock = BasicBlock::Create(context, "entry", function);
    BasicBlock* thenBlock = BasicBlock::Create(context, "if.then", function);
    BasicBlock* elseBlock = BasicBlock::Create(context, " if.else", function);
    BasicBlock* returnBlock = BasicBlock::Create(context, "if.end", function);

    builder.SetInsertPoint(entryBlock);
    Value* bPtr =
        builder.CreateAlloca(builder.getInt32Ty(), nullptr, "b.address");

    ConstantInt* value33 = builder.getInt32(33);

    return 0;
}