#include "llvm/IR/Function.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"

using namespace llvm;

int main() {
    LLVMContext context;

    // Create a module
    Module *module = new Module("HelloModule", context);

    // Add a function
    Type *voidType = Type::getVoidTy(context);
    FunctionType *functionType = FunctionType::get(voidType, false);

    Function *function = Function::Create(
        functionType, GlobalValue::ExternalLinkage, "HelloFunction", module);

    // print IR
    verifyFunction(*function); // 检测创建的函数是否符合语言规范
    module->print(outs(), nullptr);
    return 0;
}