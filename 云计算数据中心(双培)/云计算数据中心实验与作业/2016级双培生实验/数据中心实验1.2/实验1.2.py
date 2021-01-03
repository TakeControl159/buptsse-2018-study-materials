import xlrd
import pandas as pd
# 获取一个Book对象
book1 = xlrd.open_workbook("1.xlsx")
book2 = xlrd.open_workbook("2.xlsx")
# 获取一个sheet对象
table1 = book1.sheets()[0]
table2 = book2.sheets()[0]
#获取行数
nrows1 = table1.nrows
nrows2 = table2.nrows
#获取列数
ncols1 = table1.ncols
ncols2 = table2.ncols
#比较
all_list1=list()
all_list2=list()
list1=list()
list2=list()
if nrows1==nrows2 and ncols1==ncols2:
    for the_row in range(nrows1):
        for the_col in range(ncols1):
            all_list1.append(table1.cell_value(the_row, the_col))#把excel表格中的数据导入至列表
            all_list2.append(table2.cell_value(the_row, the_col))
            if abs(table1.cell_value(the_row, the_col)-table2.cell_value(the_row, the_col))>=100:#把有明显区别的单元格坐标存储在列表
                if table2.cell_value(the_row, the_col)>table1.cell_value(the_row, the_col):
                    list2.append([the_row,the_col])
                else:
                    list1.append([the_row,the_col])
print("The list1 is:")
print(list1)
print("================================================================================================================================================")
print("The list2 is:")
print(list2)
print("The number of list1 is:  "+str(len(list1)))
print("The number of list2 is:  "+str(len(list2)))
print("================================================================================================================================================")
s1=pd.Series(all_list1) #转为series类型
s2=pd.Series(all_list2)
corr=s1.corr(s2) #计算相关系数
print("两个文件的的相关性系数为："+str(corr))
