#include "SortsComparison.h"

float sum(float arg1, float arg2) {
    return arg1 + arg2;
}

void printList(vector<float> list) {
    for (auto item : list) {
        std::cout << item << ' ';
    }
    std::cout << std::endl;
}

PYBIND11_MODULE(sorts_comparison, module_handle) {
    module_handle.def("sum", &sum);
    module_handle.def("print_list", &printList);
}