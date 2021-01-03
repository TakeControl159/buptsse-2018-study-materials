Python 3.6.5 (v3.6.5:f59c0932b4, Mar 28 2018, 16:07:46) [MSC v.1900 32 bit (Intel)] on win32
Type "copyright", "credits" or "license()" for more information.
>>> import xlrd
>>> workbook=xlrd.open_workbook(r'F:\train_data.xlsx')
>>> worksheet=workbook.sheet_by_name('Sheet1')
>>> x=list()
>>> y=list()
>>> l=list()
>>> for i in range(0,20):
	x.append(worksheet.cell(i,0).value)
	y.append(worksheet.cell(i,1),value)
	l.append(worksheet.cell(i,2),value)

	
Traceback (most recent call last):
  File "<pyshell#7>", line 3, in <module>
    y.append(worksheet.cell(i,1),value)
NameError: name 'value' is not defined
>>> for i in range(0,20):
	x.append(worksheet.cell(i,0).value)
	y.append(worksheet.cell(i,1).value)
	l.append(worksheet.cell(i,2).value)

	
>>> a=zip(x,y)
>>> A=list(a)
>>> w=[3,4]
>>> b=5
>>> s=0.1
>>> for i in range(0,20):
	if (w[0]*A[i][0]+w[1]*A[i][1]+b)*l[i]<=0:
		w[0]=w[0]+A[i][0]*l[i]*s
		w[1]=w[1]+A[i][1]*l[i]*s
		b=b+l[i]*s

		
>>> result=tuple(w,b)
Traceback (most recent call last):
  File "<pyshell#17>", line 1, in <module>
    result=tuple(w,b)
TypeError: tuple() takes at most 1 argument (2 given)
>>> print(w,b)
[0.3183079000000002, 2.5848386999999997] 4.100000000000003
>>> workbook2=xlrd.open_workbook(r'F:\test_data.xlsx')
Traceback (most recent call last):
  File "<pyshell#19>", line 1, in <module>
    workbook2=xlrd.open_workbook(r'F:\test_data.xlsx')
  File "C:\Users\li\AppData\Local\Programs\Python\Python36-32\lib\site-packages\xlrd\__init__.py", line 111, in open_workbook
    with open(filename, "rb") as f:
FileNotFoundError: [Errno 2] No such file or directory: 'F:\\test_data.xlsx'
>>> workbook2=xlrd.open_workbook(r'F:\test_data.xlsx')
Traceback (most recent call last):
  File "<pyshell#20>", line 1, in <module>
    workbook2=xlrd.open_workbook(r'F:\test_data.xlsx')
  File "C:\Users\li\AppData\Local\Programs\Python\Python36-32\lib\site-packages\xlrd\__init__.py", line 111, in open_workbook
    with open(filename, "rb") as f:
FileNotFoundError: [Errno 2] No such file or directory: 'F:\\test_data.xlsx'
>>> 
