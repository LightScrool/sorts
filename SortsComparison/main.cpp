#include "SortsComparison.h"

int op_counter;

template <typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
    op_counter += 7; // 3x =; 4x get
}

template<typename T>
int binarySearch(T value, const vector<T>& data, int l, int r) {
    while (l < r - 1) {
        op_counter += 10; // while; -; <; +; /; =; if; get; <; =
        int m = (l + r) / 2;
        if (data[m] < value) {
            l = m;
        }
        else {
            r = m;
        }
    }
    return r;
}

template<typename T>
int getMax(const vector<T>& data) {
    op_counter += 2; // get, =
    T max = data[0];
    for (T element : data) {
        op_counter += 6; // 4foreach; if; >
        if (element > max) {
            max = element;
            ++op_counter;
        }
    }
    return max;
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
    return { data, op_counter };
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
    return { data, op_counter };
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
    return { data, op_counter };
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
    return { data, op_counter };
}

pair<vector<int>, int> insertionSort(vector<int> data) {
    op_counter = 0;
    ++op_counter; // =
    for (int i = 1; i < data.size(); ++i) {
        op_counter += 9; // for; get; <; ++; get; =; -; =
        int insert_value = data[i];
        int j = i - 1;
        while (j >= 0 && data[j] > insert_value) {
            op_counter += 10; // while; >; &&; get; >; get; =; get; --
            data[j + 1] = data[j];
            --j;
        }
        data[j + 1] = insert_value;
        op_counter += 2;
    }
    return { data, op_counter };
}

pair<vector<int>, int> binaryInsertionSort(vector<int> data) {
    op_counter = 0;
    ++op_counter; // =
    for (int i = 1; i < data.size(); ++i) {
        op_counter += 9; // for; get; <; ++; get; =; -; =
        int place_to_insert = binarySearch(data[i], data, -1, i);
        for (int j = i - 1; j >= place_to_insert; --j) {
            op_counter += 6; // for; >=; --; get; get
            swap(data[j], data[j + 1]);
        }
    }
    return { data, op_counter };
}

pair<vector<int>, int> countingSort(vector<int> data) {
    op_counter = 0;
    
    int counts_size = getMax(data) + 1;
    op_counter += 2; // +; get

    std::vector<int> counts;
    counts.resize(counts_size, 0);
    op_counter += 2 * counts_size; // выделение памяти; зануление

    for (int element : data) {
        ++counts[element];
        op_counter += 7; // 4foreach; get; ++;
    }

    ++op_counter; // =
    for (int i = 1; i < counts_size; ++i) {
        op_counter += 9; // for; <; ++; -; get; get; +=
        counts[i] += counts[i - 1];
    }

    std::vector<int> result;
    result.resize(data.size());
    op_counter += 1 + data.size(); // выделение памяти; get

    op_counter += 3; // get; -; =
    for (int i = data.size() - 1; i >= 0; --i) {
        op_counter += 13; // for; >=; --; get; get; --; get; get; get; get; =
        --counts[data[i]];
        result[counts[data[i]]] = data[i];
    }

    return { result, op_counter };
}

int getDigit256(int num, int i) {
    op_counter += 3;
    return (num >> (i * 8)) % 256;
}

int getPower256(const vector<int>& data) {
    op_counter += 2; // =; =
    int num = getMax(data);
    int count = 0;
    while (num != 0) {
        op_counter += 6; // while; !=; >>; =; ++
        num >>= 8;
        ++count;
    }
    return count;
}

pair<vector<int>, int> radix256Sort(vector<int> data) {
    op_counter = 0;
    int power = getPower256(data);
    op_counter += 2; // =; =
    for (int i = 0; i < power; ++i) {
        op_counter += 4; // for; <; ++

        vector<int> counts;
        counts.resize(256, 0);
        op_counter += 256 * 2 + 1; // выделение памяти; зануление; =

        for (int j = 0; j < data.size(); ++j) {
            op_counter += 10; // for; get; <; ++; get; =; get; ++
            int digit = getDigit256(data[j], i);
            ++counts[digit];
        }

        ++op_counter; // =
        for (int j = 1; j < 256; ++j) {
            op_counter += 10; // for; get; <; ++; get; =; get; ++
            counts[j] += counts[j - 1];
        }

        vector<int> round_result;
        round_result.resize(data.size());
        op_counter += 256 + 5; // выделение памяти; get; =; get; -; =
        for (int j = data.size() - 1; j >= 0; --j) {
            op_counter += 13; // for; >=; --; get; =; get; --; get; get; get; =
            int digit = getDigit256(data[j], i);
            --counts[digit];
            round_result[counts[digit]] = data[j];
        }

        data = round_result;
        op_counter += data.size(); // copy
    }

    return { data, op_counter };
}

void merge(vector<int>::iterator begin, vector<int>::iterator border, vector<int>::iterator end) {
    op_counter += 2; // -; =
    int size = end - begin;
    vector<int> merged;
    merged.resize(size);
    op_counter += size; // выделение памяти

    op_counter += 3; // =; =; =
    auto left_cur = begin;
    auto right_cur = border;

    int index = 0;
    while (left_cur != border || right_cur != end) {
        op_counter += 20; // while; !=; ||; !=; 2x(if; !=; &&; ==; ||; get; <=; get)
        if (left_cur != border && (right_cur == end || *left_cur <= *right_cur)) {
            op_counter += 7; // get; get; =; ++; ++
            merged[index] = *left_cur;
            ++left_cur;
            ++index;
        }
        if (right_cur != end && (left_cur == border || *right_cur <= *left_cur)) {
            op_counter += 7; // get; get; =; ++; ++
            merged[index] = *right_cur;
            ++right_cur;
            ++index;
        }
    }

    op_counter += 2; // =; =
    auto current = begin;
    for (int i = 0; i < size; ++i) {
        op_counter += 9; // for; <; ++; get; =; get; ++
        *current = merged[i];
        ++current;
    }
}

void mergeSortInner(vector<int>::iterator begin, vector<int>::iterator end) {
    op_counter += 8; // +; ==; if; -; =; +; /; = 
    if (begin + 1 == end) {
        return;
    }

    int size = end - begin;
    auto border = begin + size / 2;

    mergeSortInner(begin, border);
    mergeSortInner(border, end);

    merge(begin, border, end);
}

pair<vector<int>, int> mergeSort(vector<int> data) {
    op_counter = 2; // get; get
    mergeSortInner(data.begin(), data.end());
    return { data, op_counter };
}

PYBIND11_MODULE(cpp_sorts_with_op_counter, module_handle) {
    module_handle.def("selection_sort", &selectionSort);
    module_handle.def("bubble_sort", &bubbleSort);
    module_handle.def("bubble_sort_better_one", &bubbleSortBetterOne);
    module_handle.def("bubble_sort_better_two", &bubbleSortBetterTwo);
    module_handle.def("insertion_sort", &insertionSort);
    module_handle.def("binary_insertion_sort", &binaryInsertionSort);
    module_handle.def("counting_sort", &countingSort);
    module_handle.def("radix256_sort", &radix256Sort);
    module_handle.def("merge_sort", &mergeSort);
}