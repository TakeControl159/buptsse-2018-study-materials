import numpy as np
import xlrd
from  matplotlib.pyplot import*
file1 = 'D:\\untitled2\\venv\\train_data.xlsx'
file2 = 'D:\\untitled2\\venv\\test_data.xlsx'
wb = xlrd.open_workbook(filename=file1)
ws = wb.sheet_by_name('Sheet1')
dataset = []
for r in range(ws.nrows):
    col = []
    for c in range(ws.ncols):
        col.append(ws.cell(r, c).value)
    dataset.append(col)
wb2 = xlrd.open_workbook(filename=file2)
ws2 = wb2.sheet_by_name('Sheet1')
dataset2 = []
for r in range(ws2.nrows):
    col = []
    for c in range(ws2.ncols):
        col.append(ws2.cell(r, c).value)
    dataset2.append(col)
print(dataset)
print(dataset2)
w = [0, 0]
n = 1
b = 0
for j in range(0,1000000):
    for i in range(0, dataset.__len__()):
        if (dataset[i][0] * w[0] + dataset[i][1] * w[1] + b) * dataset[i][2] <= 0:
            w[0] = w[0] + n * dataset[i][2] * dataset[i][0]
            w[1] = w[1] + n * dataset[i][2] * dataset[i][1]
            b = b + n * dataset[i][2]
            i = 0


print(w)
print(b)
data = []
train_data_row = []
train_data_cols = []
for i in range(0,20):
    data.append(i)
for j in range(0,20):
    train_data_row.append(dataset[j][0])
    train_data_cols.append(dataset[j][1])
print(train_data_row)
print(train_data_cols)
figure()
scatter(train_data_row, train_data_cols)
plot([0, -1*(b/w[1])], [2, -1*(b + 2*w[0])/w[1]])
show()
for i in range(0, 5):
    if -1*(dataset2[i][0]*w[0] + b)/w[1] > dataset2[i][1]:
        print(dataset2[i])
        print("1")
    if -1*(dataset2[i][0]*w[0] + b)/w[1] < dataset2[i][1]:
        print(dataset2[i])
        print("-1")
