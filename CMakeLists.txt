cmake_minimum_required(VERSION 3.22)
project(ReadOnce_MCNets)

set(CMAKE_CXX_STANDARD 20)

add_executable(ReadOnce_MCNets main.cpp Node.cpp Node.h Agent.cpp Agent.h Operator.cpp Operator.h Rule.cpp Rule.h MCNet.cpp MCNet.h)
