import cpp_sorts_with_op_counter
import json
import timeit
from data_generator import generate_data
from config import (
    TIMES_TO_RUN,
    ARRAY_MAX_SIZE,
    ALMOST_SORTED_SWAP_STEP,
    ARR_SIZES,
    CALCULATED_DATA_FILE as OUTPUT_FILE
)

SORTS = {
    'selection_sort': cpp_sorts_with_op_counter.selection_sort,
    'bubble_sort': cpp_sorts_with_op_counter.bubble_sort,
    'bubble_sort_better_one': cpp_sorts_with_op_counter.bubble_sort_better_one,
    'bubble_sort_better_two': cpp_sorts_with_op_counter.bubble_sort_better_two,
    'insertion_sort': cpp_sorts_with_op_counter.insertion_sort,
    'binary_insertion_sort': cpp_sorts_with_op_counter.binary_insertion_sort,
    'counting_sort': cpp_sorts_with_op_counter.counting_sort,
    'radix256_sort': cpp_sorts_with_op_counter.radix256_sort,
    'merge_sort': cpp_sorts_with_op_counter.merge_sort,
    'quick_sort': cpp_sorts_with_op_counter.quick_sort,
    'heap_sort': cpp_sorts_with_op_counter.heap_sort,
    'shell_sort': cpp_sorts_with_op_counter.shell_sort,
    'ciur_sort': cpp_sorts_with_op_counter.ciur_sort,
}
data = None


def helper3(func, argument, expected_result):
    if argument == expected_result:
        raise RuntimeError('Массив уже отсортирован!')
    start_time = timeit.default_timer()
    result = func(argument)
    time_of_execution = timeit.default_timer() - start_time
    if result[0] != expected_result:
        if type(result[0]) == list:
            raise RuntimeError('Массив отсортирован неверно!')
        raise RuntimeError('Функция не вернула массив!')
    return result[1], time_of_execution


def helper2(func, array):
    expected_result = array.copy()
    expected_result.sort()

    operations_quantity_data = list()
    time_of_execution_data = list()
    for _ in range(TIMES_TO_RUN):
        oq, toe = helper3(func, array, expected_result)
        operations_quantity_data.append(oq)
        time_of_execution_data.append(toe)

    operations_quantity = sum(operations_quantity_data) / len(operations_quantity_data)
    time_of_execution = sum(time_of_execution_data) / len(time_of_execution_data) / 1e-9

    return {
        'operations': int(operations_quantity),
        'time_ns': time_of_execution
    }


def helper1(sort_name):
    func = SORTS[sort_name]
    result = dict()
    for array_name in data.keys():
        array = data[array_name]
        result[array_name] = dict()
        for i in ARR_SIZES:
            print(f'{sort_name} -> {array_name} -> {i}')
            result[array_name][i] = helper2(func, array[0:i])
    return result


def calculate_sorts_performance():
    result = dict()
    for sort_name in SORTS.keys():
        result[sort_name] = helper1(sort_name)
    return result


def main():
    sorts_performance = calculate_sorts_performance()
    with open(OUTPUT_FILE, 'w') as outfile:
        json.dump(sorts_performance, outfile, indent=2)


if __name__ == '__main__':
    data = generate_data(ARRAY_MAX_SIZE, ALMOST_SORTED_SWAP_STEP)
    main()
