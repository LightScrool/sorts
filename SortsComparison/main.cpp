#include "SortsComparison.h"

int op_counter;

template <typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
    op_counter += 3;
}

pair<vector<int>, int> selectionSort(vector<int> data) {
    op_counter = 0; // operations counter
    ++op_counter;
    for (int i = 0; i < data.size(); ++i) {
        int min = i;
        op_counter += 6;
        for (int j = i + 1; j < data.size(); ++j) {
            min = (data[j] < data[min]) ? j : min;
            op_counter += 8;
        }
        op_counter += 2;
        if (i != min) {
            swap(data[i], data[min]);
            op_counter += 4;
        }
    }
    return pair<vector<int>, int>(data, op_counter);
}

PYBIND11_MODULE(cpp_sorts_with_op_counter, module_handle) {
    module_handle.def("selection_sort", &selectionSort);
}