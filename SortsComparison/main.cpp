#include "SortsComparison.h"

void printList(const vector<int> &list) {
    for (auto item : list) {
        std::cout << item << ' ';
    }
    std::cout << std::endl;
}

int selectionSort(vector<int> &data) {
    int oc = 0; // operations counter
    ++oc;
    for (int i = 0; i < data.size(); ++i) {
        int min = i;
        oc += 6;
        for (int j = i + 1; j < data.size(); ++j) {
            min = (data[j] < data[min]) ? j : min;
            oc += 8;
        }
        oc += 2;
        if (i != min) {
            int temp = data[i];
            data[i] = data[min];
            data[min] = temp;
            oc += 7;
        }
    }
    return oc;
}

PYBIND11_MODULE(sorts_comparison, module_handle) {
    module_handle.def("selection_sort", &selectionSort);
    module_handle.def("print_list", &printList);
}