from config import REPORT_FILE
from sorts_performance_calculator import calculate_sorts_performance
from report_writer import write_report


def main():
    data = calculate_sorts_performance()
    print('Writing report...')
    write_report(data)
    print(f'Report was saved in file "{REPORT_FILE}"')


if __name__ == '__main__':
    main()
