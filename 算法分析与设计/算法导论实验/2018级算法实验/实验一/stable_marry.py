import collections

# # 匹配测试用例一
# # 男士偏向列表
# men_perference = {
#     "Xavier": ["Amy", "Bertha", "Clare"],
#     "Yancey": ["Bertha", "Amy", "Clare"],
#     "Zeus": ["Amy", "Bertha", "Clare"]}
#
# # 女士偏向列表
# women_perference = {"Amy": ["Yancey", "Xavier", "Zeus"],
#                     "Bertha": ["Xavier", "Yancey", "Zeus"],
#                     "Clare": ["Xavier", "Yancey", "Zeus"]}

# 匹配测试用例二
# 男士偏向列表
men_perference = {
    "Victor": ["Amy", "Bertha", "Clare", "Diane", "Erika"],
    "Wyatt": ["Bertha", "Clare", "Diane", "Amy", "Erika"],
    "Xavier": ["Clare", "Diane", "Amy", "Bertha", "Erika"],
    "Yancey": ["Diane", "Amy", "Bertha", "Clare", "Erika"],
    "Zeus": ["Amy", "Bertha", "Clare", "Diane", "Erika"]}

# 女士偏向列表
women_perference = {"Amy": ["Wyatt", "Xavier", "Yancey", "Zeus", "Victor"],
                    "Bertha": ["Xavier", "Yancey", "Zeus", "Victor", "Wyatt"],
                    "Clare": ["Yancey", "Zeus", "Victor", "Wyatt", "Xavier"],
                    "Diane": ["Zeus", "Victor", "Wyatt", "Xavier", "Yancey"],
                    "Erika": ["Victor", "Wyatt", "Xavier", "Yancey", "Zeus"]}

match_result = {}


# 初始化匹配结果字典
def init_match_result():
    for woman, man in women_perference.items():
        # 设女士与各自最不满意的男士匹配
        match_result[woman] = women_perference[woman][len(women_perference) - 1]


def start_match():
    # 男士队列，存放没有匹配成功的男士
    men_queue = collections.deque()

    # 初始化队列, 设所有男士都没有匹配上女士
    for men, women in men_perference.items():
        men_queue.append(men)

    while len(men_queue) != 0:
        # 取出第一个要匹配的男士
        cur_men = men_queue.popleft()
        # 当前男人按照偏好顺序依次与女士去匹配
        for cur_women in men_perference[cur_men]:
            # 如果当前男士优先级比匹配结果中的男士高, (下标越小,优先级越高)
            if women_perference[cur_women].index(cur_men) < women_perference[cur_women].index(match_result[cur_women]):
                # 当前女士重新匹配男士
                if match_result[cur_women] not in men_queue:
                    men_queue.append(match_result[cur_women])
                    match_result[cur_women] = cur_men
                    # print(f"中间匹配结果为{match_result}")
                    break
                else:
                    match_result[cur_women] = cur_men
                    # print(f"中间匹配结果为{match_result}")
                    break


if __name__ == "__main__":
    # 初始化匹配结果
    init_match_result()
    print(f"初始化匹配结果为{match_result}", end="\n\n")

    # 开始匹配
    start_match()
    print(f"最终匹配结果为{match_result}")
