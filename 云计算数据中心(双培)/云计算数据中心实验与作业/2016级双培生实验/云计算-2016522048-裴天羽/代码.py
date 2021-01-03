import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
data = pd.read_csv('./Desktop/train_data.csv', header=None)
X = data.iloc[:,:2].values
y = data.iloc[:,2].values
plt.scatter(X[:10, 0], X[:10, 1], color='blue', marker='o', label='Positive')
plt.scatter(X[10:, 0], X[10:, 1], color='red', marker='x', label='Negative')
plt.xlabel('Feature 1')
plt.ylabel('Feature 2')
plt.legend(loc = 'upper left')
plt.title('Original Data')
plt.show()
u = np.mean(X, axis=0)
v = np.std(X, axis=0)
X = (X - u) / v
plt.scatter(X[:10, 0], X[:10, 1], color='blue', marker='o', label='Positive')
plt.scatter(X[10:, 0], X[10:, 1], color='red', marker='x', label='Negative')
plt.xlabel('Feature 1')
plt.ylabel('Feature 2')
plt.legend(loc = 'upper left')
plt.title('Normalization data')
plt.show()
X = np.hstack((np.ones((X.shape[0],1)), X))
w = np.random.randn(3,1)
x1 = -2
y1 = -1 / w[2] * (w[0] * 1 + w[1] * x1)
x2 = 2
y2 = -1 / w[2] * (w[0] * 1 + w[1] * x2)
plt.scatter(X[:10, 1], X[:10, 2], color='blue', marker='o', label='Positive')
plt.scatter(X[10:, 1], X[10:, 2], color='red', marker='x', label='Negative')
plt.plot([x1,x2], [y1,y2],'r')
plt.xlabel('Feature 1')
plt.ylabel('Feature 2')
plt.legend(loc = 'upper left')
plt.show()
s = np.dot(X, w)
y_pred = np.ones_like(y)    
loc_n = np.where(s < 0)[0]    
y_pred[loc_n] = -1
t = np.where(y != y_pred)[0][0]
w += y[t] * X[t, :].reshape((3,1))
for i in range(20):
    s = np.dot(X, w)
    y_pred = np.ones_like(y)
    loc_n = np.where(s < 0)[0]
    y_pred[loc_n] = -1
    num_fault = len(np.where(y != y_pred)[0])
    print('第%2d次更新，分类错误的点个数：%2d' % (i, num_fault))
    if num_fault == 0:
        break
    else:
        t = np.where(y != y_pred)[0][0]
        w += y[t] * X[t, :].reshape((3,1))
）
x1 = -2
y1 = -1 / w[2] * (w[0] * 1 + w[1] * x1)
x2 = 2
y2 = -1 / w[2] * (w[0] * 1 + w[1] * x2)
plt.scatter(X[:10, 1], X[:10, 2], color='blue', marker='o', label='Positive')
plt.scatter(X[10:, 1], X[10:, 2], color='red', marker='x', label='Negative')
plt.plot([x1,x2], [y1,y2],'r')
plt.xlabel('Feature 1')
plt.ylabel('Feature 2')
plt.legend(loc = 'upper left')
plt.show()

