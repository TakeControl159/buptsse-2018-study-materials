# 实验一 蛮力法： 0/1背包问题 and TSP问题


# 货物类
class Good:
    def __init__(self, weight, value):
        self.weight = weight
        self.value = value
        self.flag = 0


cur_value_sum = 0       # 当前物品总价值
cur_weight_sum = 0      # 当前物品总重量
max_value_sum = 0       # 最大物品总价值


cur_good_num = 0        # 当前背包内物品数量
Backpack_capacity = 10  # 背包容量, (可修改)

# 构造货物列表 已给数据(可修改)
goods = [Good(2, 6), Good(2, 3), Good(6, 5),
         Good(5, 4), Good(4, 6), Good(7, 10)]

good_num = len(goods)            # 物品数量
good_id = [0 for i in range(good_num)]  # 当前装入背包的所有货物ID


# 记录背包中物品信息
def record_data():
    global max_value_sum, cur_good_num
    cur_good_num = 0
    max_value_sum = cur_value_sum

    # 通过标志位识别装入背包的物品,记录此物品ID,统计物品数量
    for i in range(0, good_num):
        if goods[i].flag == 1:
            good_id[cur_good_num] = i
            cur_good_num += 1


def get_max_value(x):
    global cur_weight_sum, cur_value_sum, cur_good_num, max_value_sum

    # 物品超重
    if cur_weight_sum > Backpack_capacity:
        return

    # 如果当前背包中的物品总价值比已经记录的总价值高
    if cur_value_sum > max_value_sum:
        record_data()

    # 递归遍历所有物品可能的组合
    for i in range(x, good_num):
        cur_value_sum += goods[i].value
        cur_weight_sum += goods[i].weight
        goods[i].flag = 1

        # 向下一个物品递归遍历
        get_max_value(i + 1)
        cur_value_sum -= goods[i].value
        cur_weight_sum -= goods[i].weight
        goods[i].flag = 0


if __name__ == "__main__":
    # 获取最大值
    get_max_value(0)
    print(end="\n")

    # 输出结果
    print(f"可获得的最大价值总和为:{max_value_sum}", end="\n\n")
    print(f"背包内装存的物品编号及其价值:")

    for i in range(cur_good_num):
        print(f"物品编号为:{good_id[i]}, 物品的重量为:{goods[good_id[i]].weight}, 物品价值为:{goods[good_id[i]].value}")
