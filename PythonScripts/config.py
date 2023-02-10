from itertools import chain

TIMES_TO_RUN = 100
ARRAY_MAX_SIZE = 4100
ALMOST_SORTED_SWAP_STEP = 50
ARR_SIZES = list(chain(range(50, 300, 50), range(300, ARRAY_MAX_SIZE + 1, 100)))
CALCULATED_DATA_FILE = 'sorts_performance_result.json'
