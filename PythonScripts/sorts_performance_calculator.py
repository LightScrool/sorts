import cpp_modules.cpp_sorts_with_op_counter as sort_functions
import os
import json
import timeit
from data_generator import generate_data
from config import (
    TIMES_TO_RUN,
    ARRAY_MAX_SIZE,
    ALMOST_SORTED_SWAP_STEP,
    ARR_SIZES,
    CALCULATED_DATA_FILE, RESULTS_FOLDER
)

SORTS = {
    'selection_sort': sort_functions.selection_sort,
    'bubble_sort': sort_functions.bubble_sort,
    'bubble_sort_better_one': sort_functions.bubble_sort_better_one,
    'bubble_sort_better_two': sort_functions.bubble_sort_better_two,
    'insertion_sort': sort_functions.insertion_sort,
    'binary_insertion_sort': sort_functions.binary_insertion_sort,
    'counting_sort': sort_functions.counting_sort,
    'radix256_sort': sort_functions.radix256_sort,
    'merge_sort': sort_functions.merge_sort,
    'quick_sort': sort_functions.quick_sort,
    'heap_sort': sort_functions.heap_sort,
    'shell_sort': sort_functions.shell_sort,
    'ciur_sort': sort_functions.ciur_sort,
}


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


def helper1(sort_name, data):
    func = SORTS[sort_name]
    result = dict()
    for array_name in data.keys():
        array = data[array_name]
        result[array_name] = dict()
        for i in ARR_SIZES:
            print(f'Performing "{sort_name}" on "{array_name}" data, size = {i}')
            result[array_name][str(i)] = helper2(func, array[0:i])
    return result


def calculate_sorts_performance():
    data = generate_data(ARRAY_MAX_SIZE, ALMOST_SORTED_SWAP_STEP)
    result = dict()
    for sort_name in SORTS.keys():
        result[sort_name] = helper1(sort_name, data)
    return result


def save_data(data: dict):
    if not os.path.exists(RESULTS_FOLDER):
        os.mkdir(RESULTS_FOLDER)
    output_file = RESULTS_FOLDER + os.sep + CALCULATED_DATA_FILE
    with open(output_file, 'w') as outfile:
        json.dump(data, outfile, indent=2)


def main():
    sorts_performance = calculate_sorts_performance()
    save_data(sorts_performance)


if __name__ == '__main__':
    main()
