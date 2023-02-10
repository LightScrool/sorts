from openpyxl import Workbook
from openpyxl.chart import Reference, LineChart
from openpyxl.chart.series import SeriesLabel
from openpyxl.worksheet.worksheet import Worksheet


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


def main(sheet):
    for i in [2, 3, 5, 7]:
        sheet.cell(row=1, column=i).value = f'Title {i}'
        for j in range(2, 12):
            sheet.cell(row=j, column=i).value = 100 * i + j * j
    sheet.cell(row=1, column=1).value = 'Index'
    for j in range(2, 12):
        sheet.cell(row=j, column=1).value = 10 * (j - 1)

    min_row = 2
    max_row = 11
    x_axis = Reference(min_row=min_row, max_row=max_row, min_col=1, worksheet=sheet)
    values = [
        ChartValues(Reference(min_row=min_row, max_row=max_row, min_col=2, worksheet=sheet)),
        ChartValues(Reference(min_row=min_row, max_row=max_row, min_col=3, worksheet=sheet), 'ds'),
        ChartValues(Reference(min_row=min_row, max_row=max_row, min_col=5, worksheet=sheet), 'ds'),
        ChartValues(Reference(min_row=min_row, max_row=max_row, min_col=7, worksheet=sheet), 'ds'),
    ]

    draw_line_chart(values, sheet, 'J2', x_axis)
    draw_line_chart(values, sheet, 'J30', x_axis, title='Title', x_axis_title='x', y_axis_title='y')


if __name__ == '__main__':
    wb = Workbook()
    ws = wb.active
    main(ws)
    wb.save('report.xlsx')
