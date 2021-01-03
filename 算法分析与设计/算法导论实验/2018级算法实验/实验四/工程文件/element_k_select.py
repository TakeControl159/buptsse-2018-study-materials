# **********************第k小元素问题*********************
# 测试数据（可修改）
# array = [3, 15, 30, 18, 20, 7, 62, 45]
array = [23, 45, 17, 11, 13, 89, 72, 26, 3, 17, 11, 13]
# 查找第k个小的元素
k = 6


def arr_partition(left_, right_):
    left, right = left_, right_
    # 选择数组第一个元素为划分依据
    p = array[left]
    # 将数组中大于p的数放到p前面，小于p的数放到p后面
    while left < right:
        while left < right and array[right] >= p:
            right -= 1
        array[left] = array[right]
        while left < right and array[left] <= p:
            left += 1
        array[right] = array[left]
    array[left] = p
    
    # 返回p在数组中的位置
    return left


def element_k_select(left_, right_, k):
    # 数组划分，返回划分后，划分依据元素的下标
    index = arr_partition(left_, right_)
    if k == index:
        return array[k]
    elif k < index:
        return element_k_select(left_, index - 1, k)
    elif k > index:
        return element_k_select(index + 1, right_, k)


if __name__ == "__main__":
    value = element_k_select(0, len(array) - 1, k)
    print(f"数组中第{k}小的元素数值为:{value}")
    print(f"数组单独的排序结果为:\n{sorted(array)}\n用于对比算法结果是否正确")




