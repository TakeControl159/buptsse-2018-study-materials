# **************子序列问题***************
# 测试用例1
# target_s = ["买Yahoo股票", "买eBay股票", "买Yahoo股票", "买Oracle股票"]
# sub_s = ["买Yahoo股票", "买Oracle股票"]

# 测试用例2
target_s = ["买Amazon股票", "买Yahoo股票", "买eBay股票", "买Yahoo股票", "买Yahoo股票", "买Oracle股票"]
sub_s = ["买Yahoo股票", "买eBay股票", "买Yahoo股票", "买Oracle股票"]

if __name__ == '__main__':
    j = -1
    count = 0
    for i in range(len(sub_s)):
        while j < len(target_s):
            j += 1
            if sub_s[i] == target_s[j]:
                count += 1
                break
    if count == len(sub_s):
        print("是目标序列的子序列")
    else:
        print("不是目标序列的子序列")
