cmake_minimum_required(VERSION 3.4...3.18)
project("SortsComparison")
add_subdirectory(pybind11)
pybind11_add_module(sorts_comparison main.cpp)