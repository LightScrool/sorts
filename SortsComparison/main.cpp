#include "SortsComparison.h"

int op_counter;

template <typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
    op_counter += 7; // 3x =; 4x get
}

pair<vector<int>, int> selectionSort(vector<int> data) {
    op_counter = 0;
    ++op_counter; // i =
    for (int i = 0; i < data.size(); ++i) {
        int min = i;
        op_counter += 8; // for; get; <; ++i; min =; i + 1; j =
        for (int j = i + 1; j < data.size(); ++j) {
            min = (data[j] < data[min]) ? j : min;
            op_counter += 10; // for; get; <; ++j; get; get; <; ?; min =
        }
        op_counter += 2; // if; !=
        if (i != min) {
            swap(data[i], data[min]);
            op_counter += 2; // get, get
        }
    }
    return pair<vector<int>, int>(data, op_counter);
}

pair<vector<int>, int> bubbleSort(vector<int> data) {
    op_counter = 0;
    ++op_counter; // i =
    for (int i = 0; i < data.size(); ++i) {
        op_counter += 6; // for; get; <; ++; =
        for (int j = 0; j < data.size() - i - 1; ++j) {
            op_counter += 12; // for; get; -; -; <; ++; if; get; +; get; >
            if (data[j] > data[j + 1]) {
                swap(data[j], data[j + 1]);
                op_counter += 3; // get; +; get
            }
        }
    }
    return pair<vector<int>, int>(data, op_counter);
}

pair<vector<int>, int> bubbleSortBetterOne(vector<int> data) {
    op_counter = 0;
    int i = 0;
    bool flag = true;
    op_counter += 2; // =; =
    while (flag) {
        flag = false;
        op_counter += 3; // while; =; =
        for (int j = 0; j < data.size() - i - 1; ++j) {
            op_counter += 12; // for; get; -; -; <; ++; if; get; +; get; >
            if (data[j] > data[j + 1]) {
                swap(data[j], data[j + 1]);
                flag = true;
                op_counter += 4; // get; +; get; =
            }
        }
        ++i;
        op_counter += 2;
    }
    return pair<vector<int>, int>(data, op_counter);
}

pair<vector<int>, int> bubbleSortBetterTwo(vector<int> data) {
    op_counter = 0;
    int first_sorted = data.size();
    op_counter += 2; // get, =
    while (first_sorted > 1) {
        op_counter += 4; // while; >; =; =
        int new_first_sorted = 0;
        for (int j = 0; j < first_sorted - 1; ++j) {
            op_counter += 10; // for; -; <; ++; if; get; +; get; >
            if (data[j] > data[j + 1]) {
                swap(data[j], data[j + 1]);
                new_first_sorted = j + 1;
                op_counter += 5; // get; +; get; +; =
            }
        }
        first_sorted = new_first_sorted;
        ++op_counter;
    }
    return pair<vector<int>, int>(data, op_counter);
}

PYBIND11_MODULE(cpp_sorts_with_op_counter, module_handle) {
    module_handle.def("selection_sort", &selectionSort);
    module_handle.def("bubble_sort", &bubbleSort);
    module_handle.def("bubble_sort_better_one", &bubbleSortBetterOne);
    module_handle.def("bubble_sort_better_two", &bubbleSortBetterTwo);
}