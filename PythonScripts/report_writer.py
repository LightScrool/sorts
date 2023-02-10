from openpyxl import Workbook
from openpyxl.chart import Reference, LineChart


def fill_with_data(sheet):
    for i in [2, 3, 5, 7]:
        sheet.cell(row=1, column=i).value = f'Title {i}'
        for j in range(2, 12):
            sheet.cell(row=j, column=i).value = 100 * i + j * j
    sheet.cell(row=1, column=1).value = 'Index'
    for j in range(2, 12):
        sheet.cell(row=j, column=1).value = 10 * (j - 1)


def draw_charts(sheet):
    chart = LineChart()
    # -----

    chart.set_categories(Reference(range_string='Sheet!$A$2:$A$11'))
    chart.add_data(Reference(range_string='Sheet!$B$2:$C$11'))
    chart.add_data(Reference(range_string='Sheet!$E$2:$E$11'))
    chart.add_data(Reference(range_string='Sheet!$G$2:$G$11'))

    # -----
    sheet.add_chart(chart, 'J2')


if __name__ == '__main__':
    wb = Workbook()
    ws = wb.active
    fill_with_data(ws)
    draw_charts(ws)
    wb.save('report.xlsx')
