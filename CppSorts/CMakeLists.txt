cmake_minimum_required(VERSION 3.4...3.18)
project("CppSorts")
add_subdirectory(pybind11)
pybind11_add_module(cpp_sorts_with_op_counter main.cpp)