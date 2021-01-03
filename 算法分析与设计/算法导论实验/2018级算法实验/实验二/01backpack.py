# *************回溯法实现01背包问题**************

Max_value_sum = 0       # 最大物品总价值
Max_weight_sum = 0      # 最大物品重量
Backpack_capacity = 25  # 背包容量, (可修改)


# 货物类
class Good:
    def __init__(self, weight, value):
        self.weight = weight
        self.value = value
        self.flag = 0


# 构造货物列表 已给数据(可修改)
Goods = [Good(2, 6), Good(2, 3), Good(6, 5),
         Good(5, 4), Good(4, 6), Good(7, 10)]
# Goods = [Good(20, 20), Good(15, 30), Good(10, 25)]
Result = [0 for i in range(len(Goods))]


# 记录背包中的物品数据
def record_data(cur_value_sum, cur_weight_sum):
    global Max_value_sum, Max_weight_sum, Backpack_capacity

    # 如果当前物品价值 > 记录的最大价值
    if cur_value_sum > Max_value_sum:
        for i, good in zip(range(len(Goods)), Goods):
            Result[i] = good.flag
        Max_value_sum = cur_value_sum
        Max_weight_sum = cur_weight_sum


def get_max_value(goodId, cur_weight_sum, cur_value_sum):
    # 如果物品编号大于物品数量则回退
    if goodId > len(Goods) - 1:
        return

    # 将当前物品装入背包
    cur_weight_sum += Goods[goodId].weight
    cur_value_sum += Goods[goodId].value
    Goods[goodId].flag = 1

    # 如果当前物品重量和<=背包容量,
    if cur_weight_sum <= Backpack_capacity:
        # 如果当前取得是最后一个物品
        if len(Goods) - 1 == goodId:
            record_data(cur_value_sum, cur_weight_sum)
            return  # 回溯
        else:
            get_max_value(goodId + 1, cur_weight_sum, cur_value_sum)  # 递归

    # 将当前物品不装入背包
    cur_weight_sum -= Goods[goodId].weight
    cur_value_sum -= Goods[goodId].value
    Goods[goodId].flag = 0

    # 如果当前取得是最后一个物品
    if len(Goods) - 1 == goodId:
        record_data(cur_value_sum, cur_weight_sum)
    else:
        get_max_value(goodId + 1, cur_weight_sum, cur_value_sum)  # 递归


if __name__ == "__main__":
    # 只能从第0个物品取东西
    get_max_value(0, 0, 0)

    print(f"可以取得物品的最大价值为:{Max_value_sum}")
    print("背包内包含的物品ID为:", end="")
    for i in range(len(Goods)):
        if Result[i] == 1:
            print(f"{i}, ", end="")
    print(f"\n背包内物品总重量为:{Max_weight_sum}")






