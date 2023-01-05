#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"

using namespace llvm;

// 用LLVM提供的C++ API，创建了一个最简单的模块(Module)，并打印出了它的IR代码。

int main() {

    LLVMContext context;
    Module* module = new Module("HelloModule", context);

    module->print(outs(), nullptr);

    return 0;
}