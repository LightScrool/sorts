#include "SortsComparison.h"

void printList(const vector<int> &list) {
    for (auto item : list) {
        std::cout << item << ' ';
    }
    std::cout << std::endl;
}

void selectionSort(vector<int> &data) {
    for (int i = 0; i < data.size(); i++) {
        int min = i;
        for (int j = i + 1; j < data.size(); j++) {
            min = (data[j] < data[min]) ? j : min;
        }

        if (i != min) {
            int temp = data[i];
            data[i] = data[min];
            data[min] = temp;
        }
    }
}

PYBIND11_MODULE(sorts_comparison, module_handle) {
    module_handle.def("selection_sort", &selectionSort);
    module_handle.def("print_list", &printList);
}