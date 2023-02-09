import cpp_sorts_with_op_counter
import json
import timeit
from itertools import chain
from data_generator import generate_data

TIMES_TO_RUN = 3  # TODO: increase
ARRAY_MAX_SIZE = 4100
CHANGE_STEP = 50
DATA = generate_data(ARRAY_MAX_SIZE, CHANGE_STEP)
SORTS = {
    'selection_sort': cpp_sorts_with_op_counter.selection_sort,
    'bubble_sort': cpp_sorts_with_op_counter.bubble_sort,
    'bubble_sort_better_one': cpp_sorts_with_op_counter.bubble_sort_better_one,
    'bubble_sort_better_two': cpp_sorts_with_op_counter.bubble_sort_better_two,
    'insertion_sort': cpp_sorts_with_op_counter.insertion_sort,
}


def helper3(func, argument, expected_result):
    if argument == expected_result:
        raise RuntimeError('Массив уже отсортирован!')
    start_time = timeit.default_timer()
    result = func(argument)
    time_of_execution = timeit.default_timer() - start_time
    if result[0] != expected_result:
        raise RuntimeError('Массив отсортирован неверно!')
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
    for array_name in DATA.keys():
        array = DATA[array_name]
        result[array_name] = dict()
        for i in chain(range(50, 300, 50), range(300, 4100 + 1, 100)):
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
    with open('sorts_performance_result.json', 'w') as outfile:
        json.dump(sorts_performance, outfile, indent=2)


if __name__ == '__main__':
    main()
