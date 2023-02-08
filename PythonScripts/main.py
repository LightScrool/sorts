import sorts_comparison
import timeit

TIMES_TO_RUN = 100


def perform_sort(func, argument, expected_result):
    start_time = timeit.default_timer()
    result = func(argument)
    time_of_execution = timeit.default_timer() - start_time
    if result[0] != expected_result:
        raise RuntimeError('Массив отсортирован неверно!')
    return result[1], time_of_execution


def get_performance(func, array):
    expected_result = array.copy()
    expected_result.sort()

    operations_quantity_data = list()
    time_of_execution_data = list()
    for _ in range(TIMES_TO_RUN):
        oq, toe = perform_sort(func, array, expected_result)
        operations_quantity_data.append(oq)
        time_of_execution_data.append(toe)

    operations_quantity = sum(operations_quantity_data) / len(operations_quantity_data)
    time_of_execution = sum(time_of_execution_data) / len(time_of_execution_data) / 1e-9

    return operations_quantity, time_of_execution


data = [5, 9, 3, 2, 1, 8, 7, 4, 0, 6]
print(get_performance(sorts_comparison.selection_sort, data))
