# *****************逆序对问题******************
import copy
# 测试数组，（可修改）
# array = [3, 15, 30, 18, 20, 7, 45]
array = [49, 38, 65, 97, 76, 13, 27]

# 临时数组 用于归并时临时存储归并排序结果
temp_array = [0] * len(array)
# 存储逆序对数组
interval = []


# 归并
def merge(left_, mid_, right_):
    i = left_
    j = mid_ + 1
    k = left_

    # 查找逆序对，i < j   array[i] > array[j]
    while i <= mid_ and j <= right_:
        if array[i] >= array[j]:
            # 加入逆序对
            # 如果arr[i] >= arr[j] 那么arr[i ~ mid+1]也必定大于arr[j]
            # 因为归并排序后的小数组都是有序的。
            # 例如，【7，9，10，11】【5，6，8，12】要进行归并
            # 7大于5，那么7后面的数也肯定大于5，它们都为逆序对
            for z in range(i, mid_ + 1):
                interval.append([array[z], array[j]])
            temp_array[k] = array[j]
            j += 1
        else:
            temp_array[k] = array[i]
            i += 1
        k += 1

    # 将剩余未比较的元素加入到temp_array中
    while i <= mid_:
        temp_array[k] = array[i]
        i += 1
        k += 1
    while j <= right_:
        temp_array[k] = array[j]
        j += 1
        k += 1

    # 数值重新拷贝
    for z in range(left_, right_ + 1):
        array[z] = temp_array[z]


# 归并排序
def merge_sort(left, right):
    if left < right:
        mid = (left + right) // 2
        # 分治
        merge_sort(left, mid)
        merge_sort(mid + 1, right)
        # 获取逆序对，放入interval数组中
        merge(left, mid, right)



if __name__ == "__main__":
    array_copy = copy.deepcopy(array)
    merge_sort(0, len(array) - 1)

    # 输出结果
    print(f"查找逆序对的数组为：{array_copy}")
    for i in range(len(array_copy)):
        print(f"数组第{i}个数\"{array_copy[i]}\"的逆序对为：")
        count = 0
        for j in range(len(interval)):
            if interval[j][0] == array_copy[i]:
                print(interval[j], end=" ")
                count += 1
        print("_无逆序对_") if 0 == count else print()




