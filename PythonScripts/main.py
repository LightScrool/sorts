from config import CALCULATED_DATA_FILE, REPORT_FILE
from sorts_performance_calculator import calculate_sorts_performance, save_data
from report_writer import write_report


def main():
    data = calculate_sorts_performance()
    print('Saving data...')
    save_data(data)
    print(f'Data was saved in file "{CALCULATED_DATA_FILE}"')
    print('Writing report...')
    write_report(data)
    print(f'Report was saved in file "{REPORT_FILE}"')


if __name__ == '__main__':
    main()
