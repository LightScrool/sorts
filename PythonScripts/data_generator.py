import random


def generate_data(array_max_size: int, change_step: int) -> dict:
    zero_to_5 = [random.randint(0, 5) for _ in range(array_max_size)]
    zero_to_4000 = [random.randint(0, 4000) for _ in range(array_max_size)]
    reversed_list = [i for i in range(4100, 4100 - array_max_size, -1)]
    almost_sorted = [i for i in range(array_max_size)]
    i = 0
    while i + change_step < array_max_size:
        almost_sorted[i], almost_sorted[i + change_step] = almost_sorted[i + change_step], almost_sorted[i]
        i += 2 * change_step
    return {
        'zero_to_5': zero_to_5,
        'zero_to_4000': zero_to_4000,
        'almost_sorted': almost_sorted,
        'reversed_list': reversed_list,
    }
