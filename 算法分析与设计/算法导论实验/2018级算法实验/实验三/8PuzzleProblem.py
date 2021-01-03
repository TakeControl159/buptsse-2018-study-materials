import difflib
import copy

# 这个算法有bug。。。。。。。。。。。。。。。
class Eight_puzzle_node:
    def __init__(self):

        self.puzzle = [[0] * 3 for row in range(3)]            # 数码矩阵
        self.zero_coordinate_list = []                         # 存储数字0坐标的列表
        self.puzzle_str = ""
        self.is_effective = False                              # 标志位
        self.puzzle_similarity = 0                             # 数码矩阵相似度

    # 数码矩阵字符串化
    def set_puzzle_str(self):
        for row in range(len(self.puzzle)):
            for column in range(len(self.puzzle[0])):
                self.puzzle_str += str(self.puzzle[row][column])
        self.set_puzzle_similarity()

    # 计算与目标数码字符串相似度
    def set_puzzle_similarity(self):
        goal_puzzle_str = "123456780"
        for i in range(len(self.puzzle_str)):
            if self.puzzle_str[i] == goal_puzzle_str[i]:
                self.puzzle_similarity += 1


# 节点列表，用于选择下一个节点
node_list = []
# 数码字符串列表，用于记录已经遍历过的八数码字符串
puzzle_str_list = []
# 数字0的坐标移动方向（向上移，向下移，向左移，向右移）
move = [[-1, 0], [1, 0], [0, -1], [0, 1]]


# 初始化开始节点
def init_start_node():
    # 用于测试（可修改）
    start_node.puzzle = [[1, 0, 3],
                         [4, 2, 6],
                         [7, 5, 8]]
    start_node.set_puzzle_str()
    start_node.is_effective = True
    for row in range(len(start_node.puzzle)):
        for column in range(len(start_node.puzzle[0])):
            if 0 == start_node.puzzle[row][column]:
                start_node.zero_coordinate_list.append([row, column])


# 从节点列表中获取相似度最大的节点
def get_max_puzzle_similarity_node():
    max_puzzle_similarity_node = Eight_puzzle_node()
    index = 0
    for i in range(len(node_list)):
        # 判断相似度是否更大
        if node_list[i].puzzle_similarity > max_puzzle_similarity_node.puzzle_similarity:
            max_puzzle_similarity_node = node_list[i]
            index = i
        # 判断相似度是否相等
        elif node_list[i].puzzle_similarity == max_puzzle_similarity_node.puzzle_similarity:
            # 判断遍历深度是否更大
            if len(node_list[i].zero_coordinate_list) > len(max_puzzle_similarity_node.zero_coordinate_list):
                max_puzzle_similarity_node = node_list[i]
    # 返回节点与对应坐标
    return max_puzzle_similarity_node, index


# 使用广度优先遍历，解决八数码问题
def start_bfs():
    node_list.append(copy.deepcopy(start_node))
    while 0 != len(node_list):
        # 获取相似度最高的节点及坐标
        cur_node, index = get_max_puzzle_similarity_node()
        # 从四个方向移动数字0的位置
        # print(f"{cur_node.puzzle_str}, --{cur_node.puzzle_similarity}")
        for i in range(4):
            next_node = move_zero(cur_node, i)
            if next_node.is_effective:
                if next_node.puzzle_str == "123456780":
                    return next_node
                else:
                    node_list.append(next_node)
        # 删除已经遍历过的节点
        del node_list[index]
    return -1


def move_zero(cur_node, index):
    next_node = Eight_puzzle_node()
    next_node.puzzle = copy.deepcopy(cur_node.puzzle)
    next_node.zero_coordinate_list = copy.deepcopy(cur_node.zero_coordinate_list)

    # 计算移动数字0后的新坐标
    new_zero_row = cur_node.zero_coordinate_list[-1][0] + move[index][0]
    new_zero_col = cur_node.zero_coordinate_list[-1][1] + move[index][1]

    # 判断是否越界
    if 0 <= new_zero_row < 3 and 0 <= new_zero_col < 3:
        # 八数码矩阵数字交换
        temp = next_node.puzzle[new_zero_row][new_zero_col]
        next_node.puzzle[new_zero_row][new_zero_col] = next_node.puzzle[cur_node.zero_coordinate_list[-1][0]][cur_node.zero_coordinate_list[-1][1]]
        next_node.puzzle[cur_node.zero_coordinate_list[-1][0]][cur_node.zero_coordinate_list[-1][1]] = temp
        # 添加新的数字0坐标
        next_node.zero_coordinate_list.append([new_zero_row, new_zero_col])
        next_node.set_puzzle_str()

        # 判断此结果是否已经遍历过
        if next_node.puzzle_str not in puzzle_str_list:
            # 添加未遍历的节点
            puzzle_str_list.append(next_node.puzzle_str)
            next_node.is_effective = True
    return next_node


if __name__ == "__main__":
    start_node = Eight_puzzle_node()
    init_start_node()
    end_node = start_bfs()
    print("数字0移动方向：")
    coordinate = start_node.zero_coordinate_list[0]
    for zero_coordinate in end_node.zero_coordinate_list:
        x = zero_coordinate[0] - coordinate[0]
        y = zero_coordinate[1] - coordinate[1]
        if [x, y] == move[0]:
            print("向上移动", end=" ")
        elif [x, y] == move[1]:
            print("向下移动", end=" ")
        elif [x, y] == move[2]:
            print("向左移动", end=" ")
        elif [x, y] == move[3]:
            print("向右移动", end=" ")
        coordinate = zero_coordinate
    print(f"\n数字0移动坐标：")
    for zero_coordinate in end_node.zero_coordinate_list:
        print(zero_coordinate, end=" ")
    print(f"\n经历的步数为:{len(end_node.zero_coordinate_list) - 1}")
