# ***********************汽车加油行驶问题******************
from math import inf

# 网格地图  （可修改） 其中5代表map[0][i] map[i][0] 属于边界,不会被访问
map = [[5, 5, 5, 5, 5, 5, 5, 5, 5, 5],
       [5, 0, 0, 0, 0, 1, 0, 0, 0, 0],
       [5, 0, 0, 0, 1, 0, 1, 1, 0, 0],
       [5, 1, 0, 1, 0, 0, 0, 0, 1, 0],
       [5, 0, 0, 0, 0, 0, 1, 0, 0, 1],
       [5, 1, 0, 0, 1, 0, 0, 1, 0, 0],
       [5, 0, 1, 0, 0, 0, 0, 0, 1, 0],
       [5, 0, 0, 0, 0, 1, 0, 0, 0, 1],
       [5, 1, 0, 0, 1, 0, 0, 0, 1, 0],
       [5, 0, 1, 0, 0, 0, 0, 0, 0, 0]]


N = len(map) - 1  # 网格大小
K = 3             # 装满油后,能行驶k条边(走K步)
A = 2             # 油库加油费用
B = 3             # x y坐标减小应付的费用
C = 6             # 增设油库费用

# 方向表
direction = [[-1, 0, 0],  # 向左移动 花费B元
             [0, -1, 0],  # 向上移动 花费B元
             [1, 0, B],   # 向右移动 花费0元
             [0, 1, B]]   # 向下移动

# 动态规划表
dp = [[0] * (N + 1) for i in range(N + 1)]


def data_init():
    global dp
    for i in range(1, N + 1):
        for j in range(1, N + 1):
            dp[i][j] = [inf, K]
    for i in range(N + 1):
        dp[0][i] = [0, 0]
        dp[i][0] = [0, 0]

    # 起点初始化,
    # dp[i][j][0]表示汽车从网格点(1,1)行驶至网格点(i,j)所需的最少费用
    # dp[i][j][1]表示汽车行驶至网格点(i,j)后还能行驶的网格边数(剩余油量)
    dp[1][1][0] = 0
    dp[1][1][1] = K


def solution():
    global dp, direction, map

    for x in range(1, N + 1):
        for y in range(1, N + 1):
            if x == 1 and y == 1:
                continue
            min_cost, remain_steps = inf, inf
            data = {"当前花销": 0, "当前剩余油量": 0}

            # 遍历四个方向
            for i in range(4):
                next_x = x + direction[i][0]
                next_y = y + direction[i][1]
                # 如果越界
                if next_x < 1 or next_y < 1 or next_x > N or next_y > N:
                    continue

                data["当前花销"] = dp[next_x][next_y][0] + direction[i][2]
                data["当前剩余油量"] = dp[next_x][next_y][1] - 1
                # 如果遇到油库
                if map[x][y] == 1:
                    data["当前花销"] += A
                    data["当前剩余油量"] = K
                # 如果遇到剩余步数为0, 建立油库,并加油
                if data["当前剩余油量"] == 0 and (x != N or y != N):
                    data["当前花销"] += A + C
                    data["当前剩余油量"] = K
                if data["当前花销"] < min_cost:
                    min_cost = data["当前花销"]
                    remain_steps = data["当前剩余油量"]
            # 更新最小花销,以及剩余油量
            if dp[x][y][0] > min_cost:
                dp[x][y][0] = min_cost
                dp[x][y][1] = remain_steps


if __name__ == '__main__':
    data_init()
    solution()

    print("构造的动态规划表为:")

    for x in range(1, N + 1):
        for y in range(1, N + 1):
            print("%-2d " % (dp[x][y][0]), end="")
        print()

    print(f"到达终点所需要的最少花销为:{dp[N][N][0]}")

