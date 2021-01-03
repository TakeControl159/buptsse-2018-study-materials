from numpy import *

# 这个算法忘记了这是一个环路。
# 构造路由表
Routing_table = mat([[0, 3, 6, 7],
                     [12, 0, 2, 8],
                     [8, 6, 0, 2],
                     [3, 7, 6, 0]])


# 优化路由表,修改为最短距离
def optimization_Routing_table():
    row, column = shape(Routing_table)
    for i in range(row):
        for j in range(i, column):
            if Routing_table[i, j] < Routing_table[j, i]:
                Routing_table[j, i] = Routing_table[i, j]
            else:
                Routing_table[i, j] = Routing_table[j, i]


# 通过深度优先遍历的思想实现TSP, 算法复杂度为(n!)
def get_routes():
    routes = []  # 存储所有通路
    visited_list = []  # 保存所有已经遍历的节点
    rt_len = len(Routing_table)

    visited_list.append(0)  # 从第0个节点开始遍历寻找环路
    stack = [[0, 0]]  # 第一个数代表当前节点、第二个数代表要跳转到的节点 从0节点跳转到0节点

    while len(stack) != 0:
        # 取出栈顶元素, 获取节点
        cur_node, next_node = stack[-1]

        # 若要下一节点超出最大值
        if next_node >= rt_len:
            # 如果所有节点都被遍历, 且最后一个节点和第一个节点不同, 则将遍历的节点序列存到Route中
            if len(visited_list) == rt_len and (Routing_table[cur_node, visited_list[0]] != 0):
                route = [i for i in visited_list]
                routes.append(route)

            # 节点弹栈
            visited_list.pop()
            stack.pop()

            # 此时下层节点全部遍历完，上层节点横向拓展
            if stack:
                stack[-1][1] += 1

        # 如果当前节点和下一节点相同 or 下一个节点已经被遍历
        elif (Routing_table[cur_node, next_node] == 0) or (next_node in visited_list):
            stack[-1][1] += 1

        # 如果当前节点和下一节点不同 and 下一节点没有被遍历
        elif (Routing_table[cur_node, next_node] != 0) and (next_node not in visited_list):
            # 遍历此节点
            visited_list.append(next_node)
            # 将下一节点放到栈顶
            stack.append([next_node, 0])
    return routes


if __name__ == "__main__":
    min_len = inf
    min_route = []

    # 优化路由表
    optimization_Routing_table()

    # 获取所有通路
    routes = get_routes()

    # 遍历所有通路找出最短路径
    print(f"一共有{len(routes)}个通路, 通路结果分别为：")
    for route, i in zip(routes, range(len(routes))):
        print(route, end="")
        if (i + 1) % 5 == 0: print()

        cur_len = 0
        for j in range(len(route)):
            cur_len += Routing_table[route[j], route[(j + 1) % len(Routing_table)]]

        # 如果当前长度小于 最小长度
        if cur_len < min_len:
            min_len = cur_len
            min_route = route

    print()
    print(f"最短通(环)路为{min_route}, 其长度为{min_len}")




