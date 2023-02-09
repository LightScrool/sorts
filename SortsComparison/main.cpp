#include "SortsComparison.h"

int op_counter;

template<typename T>
void swap(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
    op_counter += 7; // 3x =; 4x get
}

template<typename T>
int binarySearch(T value, const vector<T> &data, int l, int r) {
    while (l < r - 1) {
        op_counter += 10; // while; -; <; +; /; =; if; get; <; =
        int m = (l + r) / 2;
        if (data[m] < value) {
            l = m;
        } else {
            r = m;
        }
    }
    return r;
}

template<typename T>
int getMax(const vector<T> &data) {
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
    return {data, op_counter};
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
    return {data, op_counter};
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
    return {data, op_counter};
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
    return {data, op_counter};
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
    return {data, op_counter};
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
    return {data, op_counter};
}

pair<vector<int>, int> countingSort(vector<int> data) {
    op_counter = 0;

    int counts_size = getMax(data) + 1;
    op_counter += 2; // +; get

    vector<int> counts(counts_size);
    op_counter += 2 * counts_size; // vector

    for (int element : data) {
        ++counts[element];
        op_counter += 7; // 4foreach; get; ++;
    }

    ++op_counter; // =
    for (int i = 1; i < counts_size; ++i) {
        op_counter += 9; // for; <; ++; -; get; get; +=
        counts[i] += counts[i - 1];
    }

    vector<int> result(data.size());
    op_counter += 2 * data.size() + 1; // vector; get

    op_counter += 3; // get; -; =
    for (int i = data.size() - 1; i >= 0; --i) {
        op_counter += 13; // for; >=; --; get; get; --; get; get; get; get; =
        --counts[data[i]];
        result[counts[data[i]]] = data[i];
    }

    return {result, op_counter};
}

int getDigit256(int num, int i) {
    op_counter += 3;
    return (num >> (i * 8)) % 256;
}

int getPower256(const vector<int> &data) {
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

        vector<int> counts(256);
        op_counter += 256 * 2 + 1; // vector; =

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

        vector<int> round_result(data.size());
        op_counter += 256 * 2 + 5; // vector; get; =; get; -; =
        for (int j = data.size() - 1; j >= 0; --j) {
            op_counter += 13; // for; >=; --; get; =; get; --; get; get; get; =
            int digit = getDigit256(data[j], i);
            --counts[digit];
            round_result[counts[digit]] = data[j];
        }

        data = round_result;
        op_counter += data.size(); // copy
    }

    return {data, op_counter};
}

void merge(vector<int>::iterator begin, vector<int>::iterator border, vector<int>::iterator end) {
    op_counter += 2; // -; =
    int size = end - begin;
    vector<int> merged(size);
    op_counter += 2 * size; // vector

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
    return {data, op_counter};
}

int partition(vector<int> &arr, int start, int end) {
    int pivot = arr[start];

    int count = 0;
    op_counter += 5; // get; =; =; +; =
    for (int i = start + 1; i <= end; ++i) {
        op_counter += 7; // for; <=; ++; if; get; <=
        if (arr[i] <= pivot) {
            ++count;
            op_counter += 2;
        }
    }

    int pivotIndex = start + count;
    swap(arr[pivotIndex], arr[start]);

    int i = start, j = end;
    op_counter += 6; // +; =; get; get; =; =;
    while (i < pivotIndex && j > pivotIndex) {
        op_counter += 4; // while; <; >; &&
        while (arr[i] <= pivot) {
            op_counter += 5; // while; get; <=; ++
            ++i;
        }
        while (arr[j] > pivot) {
            op_counter += 5; // while; get; <=; --
            --j;
        }
        op_counter += 4; // if; <; >; &&
        if (i < pivotIndex && j > pivotIndex) {
            op_counter += 2;
            swap(arr[i++], arr[j--]);
        }
    }

    return pivotIndex;
}

void quickSortInner(vector<int> &arr, int start, int end) {
    op_counter += 2; // if; >=
    if (start >= end) {
        return;
    }
    op_counter += 3; // =; -; +
    int p = partition(arr, start, end);
    quickSortInner(arr, start, p - 1);
    quickSortInner(arr, p + 1, end);
}

pair<vector<int>, int> quickSort(vector<int> data) {
    op_counter = 0;
    op_counter += 2; // get; -
    quickSortInner(data, 0, data.size() - 1);
    return {data, op_counter};
}

template<class ValueType>
class Heap {
private:
    vector<ValueType> data_;

    void swap(int index1, int index2) {
        op_counter += 7;
        ValueType temp = data_[index1];
        data_[index1] = data_[index2];
        data_[index2] = temp;
    }

    int getLeft(int parent) {
        op_counter += 5;
        int res = (parent << 1) + 1;
        return res < size() ? res : -1;
    }

    int getRight(int parent) {
        op_counter += 5;
        int res = (parent << 1) + 2;
        return res < size() ? res : -1;
    }

    int getMinChild(int parent) {
        int left = getLeft(parent);
        int right = getRight(parent);
        op_counter += 4; // =; =; if; ==
        if (left == -1) {
            return right;
        }
        op_counter += 2; // if; ==
        if (right == -1) {
            return left;
        }
        op_counter += 4; // get; get; >; ?
        return data_[left] > data_[right] ? right : left;
    }

    bool requiresBalance(int parent) {
        int min_child = getMinChild(parent);
        op_counter += 7; // =; if; ==; ||; >; get; get
        if (min_child == -1 || data_[min_child] > data_[parent]) {
            return false;
        }
        return true;
    }

    void heapify(int i) {
        int left_child, right_child, min;
        while (true) {
            left_child = getLeft(i);
            right_child = getRight(i);
            min = i;
            op_counter += 18; // while; =; =; =; 2x(if; !=; &&; get; get; <); if; ==
            if (left_child != -1 && data_[left_child] < data_[min]) {
                min = left_child;
                ++op_counter;
            }
            if (right_child != -1 && data_[right_child] < data_[min]) {
                min = right_child;
                ++op_counter;
            }
            if (min == i) {
                break;
            }
            swap(i, min);
            i = min;
            ++op_counter;
        }
    }

public:
    Heap() = default;

    explicit Heap(vector<ValueType> source) : Heap() {
        data_ = source;
        op_counter += data_.size() + 3; // copy; =; get; /
        for (int i = size() / 2; i >= 0; --i) {
            op_counter += 4; // for; >=; --
            heapify(i);
        }
    };

    ~Heap() = default;

    size_t size() const {
        return data_.size();
    };

    ValueType extract() {
        ValueType value_to_return = data_[0];

        int last = data_.size() - 1;
        swap(0, last);
        data_.pop_back();

        int i = 0;
        op_counter += 7; // get; =; get; -; =; pop(1); =
        while (requiresBalance(i)) {
            op_counter += 3; // while; =; =
            int max_child = getMinChild(i);
            swap(max_child, i);
            i = max_child;
        }

        return value_to_return;
    };
};

pair<vector<int>, int> heapSort(vector<int> data) {
    op_counter = 0;
    Heap<int> heap(data);
    ++op_counter; // =
    for (int &i : data) {
        op_counter += 6; // 4foreach; get; =
        i = heap.extract();
    }
    return {data, op_counter};
}

void shellSortInner(vector<int> &data, int gap) {
    ++op_counter; // =
    for (int i = gap; i < data.size(); ++i) {
        op_counter += 8; // for; get; <; ++; get; =; =
        int insert_value = data[i];
        int j = i;
        while (j >= gap && data[j - gap] > insert_value) {
            op_counter += 11; // while; >=; &&; get; >; get; =; -; get; -; =
            data[j] = data[j - gap];
            j -= gap;
        }
        data[j] = insert_value;
        op_counter += 2;
    }
}

pair<vector<int>, int> shellSort(vector<int> data) {
    op_counter = 0;
    op_counter += 3; // get; /; =
    for (int gap = data.size() / 2; gap > 0; gap /= 2) {
        op_counter += 4; // for; >; /; =
        shellSortInner(data, gap);
    }
    return {data, op_counter};
}

pair<vector<int>, int> ciurSort(vector<int> data) {
    op_counter = 0;
    vector<int> ciurSequence{1750, 701, 301, 132, 57, 23, 10, 4, 1};
    op_counter += 18; // vector
    for (int gap : ciurSequence) {
        op_counter += 4; // 4foreach
        shellSortInner(data, gap);
    }
    return {data, op_counter};
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
    module_handle.def("quick_sort", &quickSort);
    module_handle.def("heap_sort", &heapSort);
    module_handle.def("shell_sort", &shellSort);
    module_handle.def("ciur_sort", &ciurSort);
}