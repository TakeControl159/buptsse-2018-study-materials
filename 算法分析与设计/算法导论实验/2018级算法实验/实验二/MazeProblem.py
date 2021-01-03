# ****************求解迷宫问题*****************
# 路径栈
path_stack = []
# 迷宫矩阵
Maze = [[1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
        [1, 0, 0, 1, 0, 0, 0, 1, 0, 1],
        [1, 0, 0, 1, 0, 0, 0, 1, 0, 1],
        [1, 0, 0, 0, 0, 1, 1, 0, 0, 1],
        [1, 0, 1, 1, 1, 0, 0, 0, 0, 1],
        [1, 0, 0, 0, 1, 0, 0, 0, 0, 1],
        [1, 0, 1, 0, 0, 0, 1, 0, 0, 1],
        [1, 0, 1, 1, 1, 0, 1, 1, 0, 1],
        [1, 1, 0, 0, 0, 0, 0, 0, 0, 1],
        [1, 1, 1, 1, 1, 1, 1, 1, 1, 1]]


def get_path():
    # 设置起点位置:第一行-第一列
    row, column = 1, 1
    path_stack.append(["开", "始"])
    path_stack.append([row, column])

    while path_stack:
        # 判断是否到达终点
        if row == column == len(Maze) - 2:
            return True
        # 判断是否可以向右移动
        if not Maze[row][column + 1]:
            column += 1
            path_stack.append([row, column])
        # 判断是否可以向下移动
        elif not Maze[row + 1][column]:
            row += 1
            path_stack.append([row, column])
        # 判断是否可以向上移动
        elif not Maze[row - 1][column]:
            row += 1
            path_stack.append([row, column])
        # 判断是否可以向左移动
        elif not Maze[row][column - 1]:
            row += 1
            path_stack.append([row, column])
        else:
            # 标记此节点不可走, 回溯
            Maze[row][column] = 2
            row, column = path_stack.pop()

    return False


if __name__ == "__main__":
    if get_path():
        print("已找到一条迷宫通路:", end="\n")
        for i in range(1, len(path_stack)):
            if path_stack[i] == [len(Maze) - 2, len(Maze) - 2]:
                print(f"{path_stack[i]}", end="\n\n")
                Maze[path_stack[i][0]][path_stack[i][1]] = 8
            else:
                print(f"{path_stack[i]}->", end="")
                Maze[path_stack[i][0]][path_stack[i][1]] = 8
            if i == 6: print()
    else:
        print("此迷宫起点与终点之间没有通路")

    print("在迷宫中行走的路径为：")
    for m in Maze:
        print(m)


