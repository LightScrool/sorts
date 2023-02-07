import timeit
import sorts_comparison


def measure_time(func, data):
    start_time = timeit.default_timer()
    func(data)
    time_of_ex = timeit.default_timer() - start_time
    return time_of_ex


data = [5, 9, 3, 2, 1, 8, 7, 4, 0, 6]
print(measure_time(sorts_comparison.selection_sort, data))
