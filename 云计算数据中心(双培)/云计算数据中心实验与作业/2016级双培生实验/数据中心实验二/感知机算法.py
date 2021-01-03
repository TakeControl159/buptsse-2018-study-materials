import numpy as np
import random as random
import matplotlib as mpl
import matplotlib.pyplot as plt
datas = [[(1,2),-1],[(2,1),-1],[(2,2),-1],[(1,4),1],[(3,3),1],[(5,4),1],[(3, 3), 1], [(4, 3), 1], [(1, 1), -1],[(2, 3), -1], [(4, 2), 1]]
random.shuffle(datas)
fig = plt.figure('Input Figure')
mpl.rcParams['xtick.labelsize'] = 16
mpl.rcParams['ytick.labelsize'] = 16
plt.rcParams['font.sans-serif']=['SimHei'] #用来正常显示中文标签
#plt.rcParams['axes.unicode_minus']=False #用来正常显示负号
xArr = np.array([x[0] for x in datas])
yArr = np.array([x[1] for x in datas])
xPlotx,xPlotx_,xPloty,xPloty_ = [],[],[],[]
for i in range(len(datas)):
    y = yArr[i]
    if y>0:
        xPlotx.append(xArr[i][0])
        xPloty.append(xArr[i][1])
    else:
        xPlotx_.append(xArr[i][0])
        xPloty_.append(xArr[i][1])
plt.title('Perception 输入数据')
plt.grid(True)
pPlot1,pPlot2 = plt.plot(xPlotx,xPloty,'b+',xPlotx_,xPloty_,'rx')
plt.legend(handles = [pPlot1,pPlot2],labels=['Positive Sample','Negtive Sample'],loc='upper center')
plt.show()

