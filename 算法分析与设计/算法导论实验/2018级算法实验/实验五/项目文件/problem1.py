# ***************动态规划 01背包问题********************


# 物品类
class Good:
    def __init__(self, weight, value):
        self.weight = weight
        self.value = value
        self.flag = False


# 构造货物列表 已给数据(可修改)
goods = [Good(2, 6), Good(2, 3), Good(6, 5),
         Good(5, 4), Good(4, 6), Good(7, 10)]
good_num = len(goods)
Backpack_capacity = 10  # 背包容量  可修改


# 构造动态规划表
def solution():
    # 初始化动态规划表
    dp = [[0] * (Backpack_capacity + 1) for i in range(good_num + 1)]

    # 根据物品信息和背包容量构造动态规划表
    for i in range(1, good_num + 1):
        for j in range(1, Backpack_capacity + 1):
            # 不装入当前物品
            dp[i][j] = dp[i - 1][j]
            if j >= goods[i - 1].weight:
                # 比较大小,选择最大结果
                dp[i][j] = max(dp[i][j], dp[i - 1][j - goods[i - 1].weight] + goods[i - 1].value)
    return dp


# 展示结果
def show_result(dp):
    print(f"可获得的最大价值总和为: {dp[good_num][Backpack_capacity]}", end="\n\n")
    j = Backpack_capacity

    # 通过动态规划表回溯查找被装入背包的物品
    for i in range(good_num, 0, -1):
        if dp[i][j] > dp[i - 1][j]:
            goods[i - 1].flag = True
            j -= goods[i - 1].weight

    print(f"背包内装存的物品编号及其价值:")
    for i in range(good_num):
        if goods[i].flag:
            print(f"物品编号为:{i}, 物品的重量为:{goods[i].weight}, 物品价值为:{goods[i].value}")

    print("构造的动态规划表如下:")
    for i in range(0, good_num + 1):
        for j in range(0, Backpack_capacity + 1):
            print("%-2d " % (dp[i][j]), end="")
        print()


if __name__ == '__main__':
    dp = solution()
    show_result(dp)


