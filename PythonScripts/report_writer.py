import json
from openpyxl import Workbook
from openpyxl.chart import Reference, LineChart
from openpyxl.chart.series import SeriesLabel
from openpyxl.worksheet.worksheet import Worksheet
from config import (
    CALCULATED_DATA_FILE as INPUT_FILE,
    REPORT_FILE as OUTPUT_FILE,
    SORTS_NAMES,
    ARR_SIZES,
    ARRAYS_NAMES
)


class ChartValues:
    def __init__(self, ref: Reference, title: str = None):
        self.ref = ref
        self.title = title


def draw_line_chart(
        data: list[ChartValues],
        sheet: Worksheet,
        position,
        x_axis: Reference = None,
        title: str = None,
        x_axis_title: str = None,
        y_axis_title: str = None
):
    chart = LineChart()

    if x_axis_title is not None:
        chart.x_axis.title = x_axis_title

    if title is not None:
        chart.title = title

    if y_axis_title is not None:
        chart.y_axis.title = y_axis_title

    if x_axis is not None:
        chart.set_categories(x_axis)

    for item in data:
        chart.add_data(item.ref)
        if item.title is not None:
            chart.series[-1].title = SeriesLabel(v=item.title)

    sheet.add_chart(chart, position)


def read_data() -> dict:
    with open(INPUT_FILE, 'r') as file:
        data = json.load(file)
    return data


def write_sizes(sheet: Worksheet, column=1):
    sheet.cell(row=1, column=column).value = "Размер"
    sheet.merge_cells(start_row=1, end_row=2, start_column=column, end_column=column)
    row = 3
    for size in ARR_SIZES:
        sheet.cell(row=row, column=column).value = size
        row += 1


def write_arr_names(sheet: Worksheet, start_column: int):
    i = 0
    for name in ARRAYS_NAMES.values():
        sheet.cell(row=2, column=start_column + i).value = name
        i += 1


def get_list_of_values(data: dict, get_value: callable) -> list:
    answer = []
    for size in ARR_SIZES:
        answer.append(get_value(data[str(size)]))
    return answer


def write_values(data: dict, get_value: callable, sheet: Worksheet, column: int):
    start_row = 3
    values = get_list_of_values(data, get_value)
    row = start_row
    for value in values:
        sheet.cell(row=row, column=column).value = value
        row += 1


def write_sort(data: dict, sort_name: str, sheet: Worksheet, get_value: callable, margin: int = 0):
    start_row = 1
    start_column = 1 + margin

    sheet.cell(row=1, column=start_column).value = sort_name
    sheet.merge_cells(start_row=start_row, end_row=start_row, start_column=start_column, end_column=start_column + 3)

    write_arr_names(sheet, start_column)

    column = start_column
    for arr_key in ARRAYS_NAMES.keys():
        write_values(data[arr_key], get_value, sheet, column)
        column += 1


def write_data(data: dict, sheet: Worksheet, get_value: callable):
    write_sizes(sheet)
    margin = 1
    for sort_id in data.keys():
        write_sort(data[sort_id], SORTS_NAMES[sort_id], sheet, get_value, margin)
        margin += 4


def main():
    data = read_data()

    wb = Workbook()
    wb.remove(wb.active)
    wb.create_sheet('Графики', 1)
    wb.create_sheet('Измерения времени', 0)
    wb.create_sheet('Измерения эл оп', 2)
    write_data(data, wb['Измерения времени'], lambda x: int(x['time_ns']))
    write_data(data, wb['Измерения эл оп'], lambda x: int(x['operations']))
    wb.save(OUTPUT_FILE)


if __name__ == '__main__':
    main()
