cmake_minimum_required(VERSION 3.15)

project(LearnLLVM LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# Policies ==========================
# cmake_policy(SET CMP0116 OLD)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED True)

#set(CMAKE_CXX_COMPILER "/home/kanon/llvm15/bin/clang++")
#set(CMAKE_C_COMPILER " /home/kanon/llvm15/bin/clang")

add_link_options(

    # We enforce the lld linker
    #    -fuse-ld=lld
    # -Wl,-gc-sections
    # $<$<CONFIG:RELEASE>:-s>

    # Do not link against shared libraries
    # --static
)

# LLVM setup =========================================
find_package(LLVM REQUIRED all-targets CONFIG)
find_package(MLIR REQUIRED CONFIG)
find_package(LLD REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
message(STATUS "Using MLIRConfig.cmake in: ${MLIR_DIR}")
message(STATUS "===>Using LLDConfig.cmake in: ${LLD_DIR}")
list(APPEND CMAKE_MODULE_PATH "${MLIR_CMAKE_DIR}")
list(APPEND CMAKE_MODULE_PATH "${LLVM_CMAKE_DIR}")
list(APPEND CMAKE_MODULE_PATH "${LLD_CMAKE_DIR}")

include(TableGen)
include(AddLLVM)
include(AddMLIR)
include(HandleLLVMOptions)

include_directories(SYSTEM ${LLVM_INCLUDE_DIRS})

separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

link_directories(${LLVM_BUILD_LIBRARY_DIR})
add_definitions(${LLVM_DEFINITIONS})

set(CONDITIONAL_COMPONENTS "")

if(LLVM_USE_PERF)
    list(APPEND CONDITIONAL_COMPONENTS PerfJITEvents)
endif()

llvm_map_components_to_libnames(llvm_libs
    core
    support
    jitlink
    orcjit
    ExecutionEngine
    ${CONDITIONAL_COMPONENTS}
    ${LLVM_TARGETS_TO_BUILD}
)

add_executable(testllvm main.cpp)
target_link_libraries(testllvm ${llvm_libs})

add_executable(testModule HelloModule.cpp)
target_link_libraries(testModule ${llvm_libs})

add_executable(testFunction HelloFunction.cpp)
target_link_libraries(testFunction ${llvm_libs})

add_executable(testBlock HelloBlock.cpp)
target_link_libraries(testBlock ${llvm_libs})

add_executable(testHelloGlobalVariable HelloGlobalVariable.cpp)
target_link_libraries(testHelloGlobalVariable ${llvm_libs})

add_executable(testHelloReturn HelloReturn.cpp)
target_link_libraries(testHelloReturn ${llvm_libs})

add_executable(testHelloFunctionArgs HelloFunctionArguments.cpp)
target_link_libraries(testHelloFunctionArgs ${llvm_libs})

add_executable(testHelloArithmeticStatement HelloArithmeticStatement.cpp)
target_link_libraries(testHelloArithmeticStatement ${llvm_libs})

add_executable(testHelloIfElse HelloIfElse.cpp)
target_link_libraries(testHelloIfElse ${llvm_libs})
