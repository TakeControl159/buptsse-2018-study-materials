import random,xlwt
from numpy import mean, median,mean, ptp, var, std
from scipy.stats import mode
#生成随机数放入列表
list1=list()
for i in range(1000):
    list1.append(random.randint(0, 10000))
print("The number of list1 is: "+str(len(list1)))
print(list1)

avge=mean(list1)
print("均值:"+str(avge))
print("中位数："+str(median(list1)))
print("众数"+str(mode(list1)))
varia=var(list1)
print("方差："+str(varia))
print("极差："+str(ptp(list1)))
print("标准差："+str(std(list1)))
print("变异系数："+str(mean(list1) / std(list1)))

#零-均值规范化
for w in range(len(list1)):
    list1[w]=(list1[w]-avge)/varia
print(list1)

#数据导出到excel
wb = xlwt.Workbook()
ws = wb.add_sheet('After_Sheet')
for e in range(40):
    for r in range(25):
        ws.write(e, r, list1[e*25+r])
wb.save("After_data.xls")