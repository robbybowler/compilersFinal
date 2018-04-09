cmake_minimum_required(VERSION 3.9)
project(compiler)

set(CMAKE_CXX_STANDARD 11)

add_executable(compiler main.cpp Node.cpp Node.h Symbol.cpp Symbol.h Scanner.cpp Scanner.h StateMachine.cpp StateMachine.h Token.cpp Token.h Debug.h Parser.cpp Parser.h ParserTest.cpp MachineCodeTest.cpp)