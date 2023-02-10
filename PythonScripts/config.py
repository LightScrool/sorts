from itertools import chain

TIMES_TO_RUN = 100
ARRAY_MAX_SIZE = 4100
ALMOST_SORTED_SWAP_STEP = 50
ARR_SIZES = list(chain(range(50, 300, 50), range(300, ARRAY_MAX_SIZE + 1, 100)))
CALCULATED_DATA_FILE = 'sorts_performance_result.json'
REPORT_FILE = 'report.xlsx'
SORTS_NAMES = {
    'selection_sort': 'Сортировка выбором',
    'bubble_sort': 'Сортировка пузырьком',
    'bubble_sort_better_one': 'Сортировка пузырьком (Айверсон 1)',
    'bubble_sort_better_two': 'Сортировка пузырьком (Айверсон 2)',
    'insertion_sort': 'Сортировка вставками',
    'binary_insertion_sort': 'Сортировка бин вставками',
    'counting_sort': 'Сортировка подсчётом',
    'radix256_sort': 'Цифровая сортировка',
    'merge_sort': 'Сортировка слиянием',
    'quick_sort': 'Быстрая сортировка',
    'heap_sort': 'Сортировка кучей',
    'shell_sort': 'Сортировка Шелла',
    'ciur_sort': 'Сортировка Шелла (Циур)',
}
ARRAYS_NAMES = {
    'zero_to_5': 'Случайные числа 0-5',
    'zero_to_4000': 'Случайные числа до 0-4000',
    'almost_sorted': 'Почти отсортировный',
    'reversed_list': 'Обратно отсортировный',
}
X_AXIS_TITLE = "Размер входных данных"
Y_AXIS_TITLE_TIME = "Время выполнения, нс"
CALC_TIME_SHEET_NAME = "Измерения времени"
CALC_OP_SHEET_NAME = 'Измерения эл оп'
CHART_SORT_SHEET_NAME = "Графики по сортировкам"
CHART_ARR_SHEET_NAME = "Графики по данным"
CHART_WIDTH = 15.5
CHART_HEIGHT = 9
CHART_HORIZONTAL_MARGIN = 10
CHART_VERTICAL_MARGIN = 22
