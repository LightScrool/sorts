import sorts_comparison
import timeit

TIMES_TO_RUN = 100


def measure_performance(func, argument):
    start_time = timeit.default_timer()
    operations_quantity = func(argument)
    time_of_execution = timeit.default_timer() - start_time
    return operations_quantity, time_of_execution


def multi_measure_performance(func, argument):
    operations_quantity_data = list()
    time_of_execution_data = list()
    for _ in range(TIMES_TO_RUN):
        oq, toe = measure_performance(func, argument)
        operations_quantity_data.append(oq)
        time_of_execution_data.append(toe)
    operations_quantity = sum(operations_quantity_data) / len(operations_quantity_data)
    time_of_execution = sum(time_of_execution_data) / len(time_of_execution_data)
    return operations_quantity, time_of_execution


data = [5, 9, 3, 2, 1, 8, 7, 4, 0, 6]
print(multi_measure_performance(sorts_comparison.selection_sort, data))
