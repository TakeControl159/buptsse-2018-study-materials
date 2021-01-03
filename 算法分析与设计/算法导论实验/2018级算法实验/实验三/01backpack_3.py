# *************分枝界限法解决01背包问题**************


# 物品类
class Good:
    def __init__(self, weight, value):
        self.weight = weight
        self.value = value
        self.unit_value = value / weight
        # 背包是否被拿标志位
        self.is_take = False


# 物品节点
class Node:
    def __init__(self, cur_weight_sum, cur_value_sum, ub):
        self.cur_weight_sum = cur_weight_sum
        self.cur_value_sum = cur_value_sum
        # 物品拿取结果
        self.goods_take_result = []
        self.ub = ub

    def set_goods_take_result(self, good_id):
        # 记录已经遍历物品的标志位值
        for i in range(good_id + 1):
            self.goods_take_result.append(goods[i].is_take)


# 构造货物列表 已给数据(可修改)
# Goods = [Good(2, 6), Good(2, 3), Good(6, 5),
#          Good(5, 4), Good(4, 6), Good(7, 10)]
# Goods = [Good(20, 20), Good(15, 30), Good(10, 25)]
goods = [Good(4, 40), Good(7, 42), Good(5, 25), Good(3, 12)]

# 物品节点数组
good_nodes = []
backpack_capacity = 10  # 背包容量, (可修改)
ub_bound = [0, 0]  # 界限


# 计算ub
def get_ub(good_id, cur_weight_sum, cur_value_sum):
    ub = 0
    if good_id < len(goods) - 1:
        ub = cur_value_sum + (backpack_capacity - cur_weight_sum) * goods[good_id + 1].unit_value
    else:
        ub = cur_value_sum + 0

    # 判断是否越界, 添加节点
    if ub_bound[0] <= ub <= ub_bound[1]:
        node = Node(cur_weight_sum, cur_value_sum, ub)
        node.set_goods_take_result(good_id)
        good_nodes.append(node)
    return ub


def get_optimal_good_take_result():
    # 初始化上下界
    ub_bound[0], ub_bound[1] = backpack_capacity * goods[-1].unit_value, backpack_capacity * goods[0].unit_value
    # 当前物品重量和、价值和
    cur_weight_sum = 0
    cur_value_sum = 0

    # 物品数量
    good_num = len(goods)

    good_id = 0
    while good_id < good_num:
        true_ub, false_ub = 100, 100

        # 将当前物品放入背包
        goods[good_id].is_take = True
        cur_weight_sum += goods[good_id].weight
        cur_value_sum += goods[good_id].value
        # 判断是否超重
        if cur_weight_sum <= backpack_capacity:
            true_ub = get_ub(good_id, cur_weight_sum, cur_value_sum)

        # 将当前物品不装入背包
        goods[good_id].is_take = False
        cur_weight_sum -= goods[good_id].weight
        cur_value_sum -= goods[good_id].value
        false_ub = get_ub(good_id, cur_weight_sum, cur_value_sum)

        # 判断是否遍历到最后一个节点
        if good_id >= len(goods) - 1:
            # 更新下界
            ub_bound[0] = true_ub if true_ub < false_ub else false_ub

        # 从物品节点数组中,获取ub值最大的节点和对应下标
        index = 0
        max_ub = ub_bound[0]
        for i in range(len(good_nodes)):
            if good_nodes[i].ub >= max_ub:
                max_ub = good_nodes[i].ub
                index = i

        # 重新给货物的标志位赋值
        for i in range(len(good_nodes[index].goods_take_result)):
            goods[i].is_take = good_nodes[index].goods_take_result[i]
        cur_weight_sum = good_nodes[index].cur_weight_sum
        cur_value_sum = good_nodes[index].cur_value_sum

        # 更新遍历的物品编号, 回溯
        good_id = len(good_nodes[index].goods_take_result)
        # 删除节点
        del good_nodes[index]


if __name__ == "__main__":
    # 物品单位价值排序
    goods.sort(key=lambda good: good.unit_value, reverse=True)

    total_weight = 0
    total_value = 0

    # 获取最佳的物品拿取结果(总价值最大)
    get_optimal_good_take_result()

    print("最佳的物品拿取结果为:\n物品ID:", end="")
    for i in range(len(goods)):
        if goods[i].is_take:
            total_value += goods[i].value
            total_weight += goods[i].weight
            print(f"{i}, ", end="")

    print(f"\n背包内物品总重量为: {total_weight}, 背包内物品总价值为: {total_value}")
