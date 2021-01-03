# *******************邮局选址问题***********************
from numpy import *
import matplotlib.pyplot as plt
import copy
# 居民坐标
location = {"X": [3, 15, 30, 18, 20, 7, 40, 11, 2],
            "Y": [10, 11, 9, 21, 30, 22, 6, 22, 17]}


# 分治函数
def divide(left_, right_, arr):
    left, right = left_, right_
    temp = arr[left]
    while left < right:
        while left < right and arr[right] >= temp:
            right -= 1
        arr[left] = arr[right]
        while left < right and arr[left] <= temp:
            left += 1
        arr[right] = arr[left]
    arr[left] = temp
    return left


# 快速排序算法
def quick_sort(left, right, arr):
    if left < right:
        # 分治
        index = divide(left, right, arr)
        quick_sort(left, index - 1, arr)
        quick_sort(index + 1, right, arr)


if __name__ == "__main__":
    location_ = copy.deepcopy(location)
    array_len = len(location["X"])
    # 居民坐标快速排序
    quick_sort(0, array_len - 1, location_["X"])
    quick_sort(0, array_len - 1, location_["Y"])

    # 用排序坐标后的中位数计算距离之和：
    distance_x = 0
    distance_y = 0
    distance = 0
    for x, y in zip(location_["X"], location_["Y"]):
        distance_x = math.pow(x - location_["X"][math.floor(array_len / 2)], 2)
        distance_y = math.pow(y - location_["Y"][math.floor(array_len / 2)], 2)
        distance += math.sqrt(distance_x + distance_y)
    print(f"最小距离之和为:{distance}")

    # 绘制散点图展示结果：
    plt.figure()
    # 居民坐标，用蓝色点显示
    plt.scatter(location["X"], location["Y"], c='blue')
    # 邮局坐标，用红色点显示
    plt.scatter(location_["X"][math.floor(array_len / 2)], location_["Y"][math.floor(array_len / 2)], c='red')
    plt.show()
