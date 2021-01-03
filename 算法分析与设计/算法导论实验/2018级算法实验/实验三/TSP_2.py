from numpy import *
import math
import heapq
import copy


# 城市节点
class Node:
    def __init__(self, pass_cities, lb):
        self.pass_cities = copy.deepcopy(pass_cities)  
        self.pass_cities_num = len(pass_cities)
        self.lb = lb


# 路径长度边界
lb_bound = [0, 0]
# 构造城市距离表 inf——正无穷大
city_distance_table = [[inf, 3, 1, 5, 8],
                       [3, inf, 6, 7, 9],
                       [1, 6, inf, 4, 2],
                       [5, 7, 4, inf, 3],
                       [8, 9, 2, 3, inf]]


def get_lb(pass_cities):
    lb = 0
    city_distance_form = copy.deepcopy(city_distance_table)
    # 1.计算已经走过的城市距离*2
    for i in range(len(pass_cities) - 1):
        lb += city_distance_form[pass_cities[i]][pass_cities[(i + 1)]] * 2
        city_distance_form[pass_cities[i]][pass_cities[(i + 1)]] = inf
        city_distance_form[pass_cities[(i + 1)]][pass_cities[i]] = inf

    # 2.累加起点城市、当前城市到其他最近城市的距离
    for i in range(len(city_distance_form)): 
        if i in [pass_cities[0], pass_cities[-1]]:
            lb += min(city_distance_form[i])

        # 3.累加未经过城市的两条最短路径距离
        elif i not in pass_cities:
            lb += sum(heapq.nsmallest(2, city_distance_form[i]))
    return math.ceil(lb / 2) 


def init_lb_bound():
    city_list = []

    # 贪心算法计算上界
    for i in range(len(city_distance_table)):
        min_distance = inf
        index = 0
        for j in range(len(city_distance_table)):
            if j not in city_list and city_distance_table[i][j] < min_distance:
                min_distance = city_distance_table[i][j]
                index = j
        city_list.append(index)
        lb_bound[1] += min_distance

    # 计算下界
    for distance in city_distance_table:
        # 累加每一个城市到达其他最近两个城市的距离
        lb_bound[0] += sum(heapq.nsmallest(2, distance))
    # 除2 向上取整
    lb_bound[0] = math.ceil(lb_bound[0] / 2)


def get_min_route():
    # 初始化上下界
    init_lb_bound()
    # 当前经过的城市, 默认第0号城市已经经过
    pass_cities = [0]
    # 城市节点列表
    city_nodes = []
    # 城市数量
    city_num = len(city_distance_table)

    while len(pass_cities) < city_num:
        # 遍历每一个能够到达的城市节点
        for city_id in range(city_num):
            # 判断城市是否被经过
            if city_id not in pass_cities:
                pass_cities.append(city_id)
                node = Node(pass_cities, get_lb(pass_cities))

                # 判断lb是否越界
                if lb_bound[0] <= node.lb <= lb_bound[1]:
                    city_nodes.append(node)
                pass_cities.pop()

        # 从路径节点数组中,获取lb值最小的且经过城市数量最多节点的对应下标
        index = 0
        min_lb = lb_bound[1]
        pass_city_num = 0
        for node_id in range(len(city_nodes)):
            # 寻找lb值最小的节点
            if city_nodes[node_id].lb < min_lb:
                min_lb = city_nodes[node_id].lb
                pass_city_num = city_nodes[node_id].pass_cities_num
                index = node_id

            # 寻找经过城市数量最多的节点
            elif city_nodes[node_id].lb == min_lb:
                if pass_city_num < city_nodes[node_id].pass_cities_num:
                    pass_city_num = city_nodes[node_id].pass_cities_num
                    index = node_id

        # 刷新经历过的城市
        pass_cities = city_nodes[index].pass_cities

        # 删除节点
        del city_nodes[index]
    return pass_cities


if __name__ == "__main__":
    min_distance_route = get_min_route()
    print(f"最短通(环)路为{min_distance_route}, 其路程长度为{get_lb(min_distance_route)}")
