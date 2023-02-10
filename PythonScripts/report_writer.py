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


def get_list_of_values(data: dict, get_value: callable) -> list:
    answer = []
    for size in ARR_SIZES:
        answer.append(get_value(data[str(size)]))
    return answer


def write_sort(data: dict, sort_name: str, sheet: Worksheet, get_value: callable):
    sheet.append([sort_name])
    for array in data.keys():
        sheet.append([ARRAYS_NAMES[array], *get_list_of_values(data[array], get_value)])


def write_data(data: dict, sheet: Worksheet, get_value: callable):
    sheet.append(['Размер массива', *ARR_SIZES])
    for sort_id in data.keys():
        write_sort(data[sort_id], SORTS_NAMES[sort_id], sheet, get_value)


def main():
    data = read_data()

    wb = Workbook()
    wb.remove(wb.active)
    wb.create_sheet('Графики', 0)
    wb.create_sheet('Измерения времени', 1)
    wb.create_sheet('Измерения эл оп', 2)
    write_data(data, wb['Измерения времени'], lambda x: int(x['time_ns']))
    write_data(data, wb['Измерения эл оп'], lambda x: int(x['operations']))
    wb.save(OUTPUT_FILE)


if __name__ == '__main__':
    main()
