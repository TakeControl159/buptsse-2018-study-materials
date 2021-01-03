# ****************带权区间调度问题*********************
class Request:
    def __init__(self, requrest_id, begin_time, end_time, weight):
        self.request_id = requrest_id     # 需求编号
        self.begin_time = begin_time      # 开始时间
        self.end_time = end_time          # 结束时间
        self.weight = weight              # 权重
        self.p = -1                       # 不冲突的最大下标的任务


# 测试数据，(可修改）
requests = [Request(1, 1, 4, 12), Request(2, 3, 5, 20), Request(3, 0, 6, 23),
            Request(4, 4, 7, 13), Request(5, 3, 8, 26), Request(6, 8, 11, 16),
            Request(7, 5, 9, 20), Request(8, 6, 10, 11), Request(9, 1, 11, 1)]
# 需求数量
request_num = len(requests)


def requests_init():
    global requests, request_num
    # 对每个需求按照结束时间升序排序
    requests = sorted(requests, key=lambda request: request.end_time)

    # 寻找与第i个需求相容的最大下标的需求
    for i in range(request_num):
        for j in range((i - 1), -1, -1):
            if requests[i].begin_time >= requests[j].end_time:
                # 记录最大下标
                requests[i].p = j
                break


def solution():
    global requests, request_num
    # 初始化动态规划表
    dp = [0 for i in range(request_num + 1)]
    # 构造动态规划表
    for i in range(1, request_num + 1):
        # 寻找前i-1个任务的最优解
        if -1 == requests[i - 1].p:
            dp[i] = max(dp[i - 1], requests[i - 1].weight)
        else:
            dp[i] = max(requests[i - 1].weight + dp[requests[i - 1].p + 1], dp[i - 1])
    return dp


def show_result(dp):
    print("动态规划表中的值为：")
    for result in dp:
        print(result, end=",")
    print()

    # 回溯寻找被满足的需求
    max_weight = dp[-1]
    i = request_num
    while i > 0:
        if max_weight == dp[i - 1]:
            i -= 1
        else:
            print(f"调度的需求编号为：{requests[i - 1].request_id}，"
                  f"开始、结束时间为{requests[i - 1].begin_time}，{requests[i - 1].end_time},"
                  f"权值为{requests[i - 1].weight} ")
            # 回溯
            i = requests[i - 1].p + 1


if __name__ == '__main__':
    requests_init()
    dp = solution()
    show_result(dp)


