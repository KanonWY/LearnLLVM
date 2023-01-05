#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"

// blog.csdn.net/Zhanglin_Wu/article/details/125253018
// https://llvm.org/docs/LangRef.html#linkage

// LLVM提供了Module::getOrInsertGlobal()函数来创建全局变量，以及Module::getNamedGlobal()来找到一个全局变量。
// 创建全局变量之后，我们可以配置它的属性，如链接类型、内存对齐模型等。

// 用LLVM提供的C++ API，创建了一个全局变量(Global Variable)

using namespace llvm;

int main() {

    LLVMContext context;
    IRBuilder<> builder(context);

    // Create a module
    Module* module = new Module("HelloModule", context);

    // Add a global var
    module->getOrInsertGlobal("helloGlobalVariable", Type::getInt32Ty(context));
    GlobalVariable* globalVariable =
        module->getNamedGlobal("helloGlobalVariable");

    globalVariable->setLinkage(GlobalValue::CommonLinkage);
    globalVariable->setAlignment(MaybeAlign(4));

    // Add a function
    Type* voidType = Type::getVoidTy(context);
    FunctionType* functionType = FunctionType::get(voidType, false);
    Function* function = Function::Create(
        functionType, GlobalValue::ExternalLinkage, "HelloFunction", module);

    // Create a block
    BasicBlock* block = BasicBlock::Create(context, "entry", function);
    builder.SetInsertPoint(block);

    // Print the IR
    verifyFunction(*function);
    module->print(outs(), nullptr);

    return 0;
}