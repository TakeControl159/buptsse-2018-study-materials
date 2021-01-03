# ****************股票买卖问题****************

# 股票价格 （可修改）
# stock_price = [100, 90, 85, 50, 30, 20, 10]
stock_price = [59, 68, 66, 61, 71, 75, 70]


# 最大收益字典，"左半边"：【买入价格， 卖出价格】
max_profit = {"左半边": [0, 0],
              "右半边": [0, 0],
              "整个": [0, 0]}


def get_max_profit(price):
    if len(price) <= 1:
        return [price[0], price[0]]

    # 分治，将价格分为两部分
    mid = len(price) // 2
    price_left = price[:mid]
    price_right = price[mid:]
    # 获取左右半边，收益最大的买入和卖出价格
    max_profit["左半边"] = get_max_profit(price_left)
    max_profit["右半边"] = get_max_profit(price_right)

    # 获取整个数组，收益最大和买入和卖出价格
    min_price_left = min(price_left)
    max_price_right = max(price_right)
    max_profit["整个"] = [min_price_left, max_price_right]

    # 从最大收益字典中获取，三个键值
    three_max_profit = [value for key, value in max_profit.items()]
    # 返回三个部分中，收益最大和买入和卖出价格
    return max(three_max_profit, key=lambda x: x[1] - x[0])


if __name__ == "__main__":
    # 获取最好的买入价格， 卖出价格
    best_price = get_max_profit(stock_price)

    # 获取股票购买日期， 用数组下标代替
    buy_date = stock_price.index(best_price[0])
    sell_date = 0
    for i in range(len(stock_price)):
        if stock_price[i] == best_price[1]:
            sell_date = i

    # 输出结果
    print(f"股票价格为：{stock_price}")
    print(f"建议在第{buy_date}天买入股票，在第{sell_date}天出售股票，这样能获取最大利润")
    print(f"这两天对应的价格分别为：{best_price[0]}元，{best_price[1]}元，差价为：{best_price[1] - best_price[0]}元")
    print(f"如果买1000股，赚取的利润为：{(best_price[1] - best_price[0]) * 1000}元")

