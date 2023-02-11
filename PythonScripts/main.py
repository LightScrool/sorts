import os
from config import RESULTS_FOLDER, CALCULATED_DATA_FILE, REPORT_FILE
from sorts_performance_calculator import calculate_sorts_performance, save_data
from report_writer import write_report, save_report


def main():
    data = calculate_sorts_performance()
    print('Saving data...')
    save_data(data)
    print(f'Data was saved in file "{RESULTS_FOLDER + os.sep + CALCULATED_DATA_FILE}"')
    print('Writing report...')
    report = write_report(data)
    save_report(report)
    print(f'Report was saved in file "{RESULTS_FOLDER + os.sep + REPORT_FILE}"')


if __name__ == '__main__':
    main()
