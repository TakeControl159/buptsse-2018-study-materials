# -*- coding: utf-8 -*-
"""
Created on Fri Dec 28 08:42:02 2018

@author: Yan
"""

import pandas as pd    #用于读取文件

import matplotlib.pyplot as plt

#将预测结果划分为0/-1/1
def sign(v):
    if v>0:
        return 1
    if v<0:
         return -1
    else:
        return 0

data = pd.read_csv('train_data.CSV')
print("************初始训练数据文件**********")
print(data)
# 样本输入
X = data.iloc[:,:2].values#所有行，前两列即[0,2)
# 样本标签
y = data.iloc[:,2].values
train_datas = data.iloc[:,:].values
print("************训练数据**********")
print(X)
print("************标签**********")
print(y)
#可视化训练数据
plt.scatter(X[:9, 0], X[:9, 1], color='blue', marker='o', label='+1')
plt.scatter(X[9:, 0], X[9:, 1], color='red', marker='x', label='-1')
plt.xlabel('x1')
plt.ylabel('y1')
plt.legend(loc = 'upper left')
plt.title('train Data')
plt.show()

#初始化参数
weight = [0, 0]  # 将权重初始化为0
bias = 0  # 偏置量初始化为0
learning_rate = 0.5  # 学习速率

#进行训练
for i in range(100):
    worse=0
    for train in train_datas:
        x1, x2, y =train
        predict = sign(weight[0] * x1 + weight[1] * x2 + bias)  # 预测结果
        print("train data: x: (%d, %d) y: %d  ==> predict: %d" % (x1, x2, y, predict))
        #如果有错误点，则更新参数
        if y !=predict: 
            worse+=1 
            weight[0] = weight[0] + learning_rate * y * x1  # 更新权重
            weight[1] = weight[1] + learning_rate * y * x2
            bias = bias + learning_rate * y  # 更新偏置量
            print("update weight and bias: "),
            print(weight[0], weight[1], bias)
    if worse==0:break#没有错误点则退出训练
    
print("stop training: ")
print(weight[0], weight[1], bias)#将训练出参数打印在屏幕上

#根据上述训练出的参数，求出两个点，方便后续画线
x11 = 2
x21 = -(weight[0] * x11 + bias)/weight[1]

x12 = 8
x22 =-(weight[0] * x12 + bias)/weight[1]


plt.scatter(X[:9, 0], X[:9, 1], color='blue', marker='o', label='+1')
plt.scatter(X[9:, 0], X[9:, 1], color='red', marker='x', label='-1')
plt.plot([x11,x12], [x21,x22],'r')#第一个[]中是两个点的横坐标，第二个[]是纵坐标
plt.xlabel('x1')
plt.ylabel('y1')
plt.legend(loc = 'upper left')
plt.title('train Data classify')
plt.show()


# 测试样本输入
test_data = pd.read_csv('test_data .CSV')
print("************测试数据文件**********")
print(test_data.iloc[:,:2].values)
plt.scatter(X[:, 0], X[:, 1], color='blue', marker='o')
plt.xlabel('x1')
plt.ylabel('x2')
plt.title('test Data')
plt.show()

#对测试数据进行分类
for testData in test_data.iloc[:,:2].values:
    x1,x2=testData
    predict = sign(weight[0] * x1 + weight[1] * x2 + bias) 
    if predict>0:
        plt.scatter(x1,x2, color='blue', marker='o', label='+1')
    else:
        plt.scatter(x1,x2, color='red', marker='x', label='-1')
    
x11 = -2.5
x21 = -(weight[0] * x11 + bias)/weight[1]
# 直线第二个坐标（x2，y2）
x12 = 9
x22 =-(weight[0] * x12 + bias)/weight[1]
plt.plot([x11,x12], [x21,x22],'r')

plt.xlabel('x1')
plt.ylabel('x2')
plt.legend(loc = 'upper left')
plt.title('test Data classify')
plt.show()
    
