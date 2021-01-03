#include <stdio.h>
#include<iostream>
int maxSubValues(int nums[], int minIndex, int maxIndex) {
	int sum = 0;
	int allMax = 0;
	int leftMax = 0;
	int rightMax = 0;
	int middleIndex = (minIndex + maxIndex) / 2;
	int i;
	if (minIndex == maxIndex) { // 数组就一个元素了
		if (nums[minIndex] < 0) { // 如果数据都是负数，最大子段值为0
			return 0;
		}
		else {
			return nums[minIndex];
		}
	}
	leftMax = maxSubValues(nums, minIndex, middleIndex);
	rightMax = maxSubValues(nums, middleIndex + 1, maxIndex);
	for (i = middleIndex; i >= 0; i--) { // 从中点往左累加最大值
		sum += nums[i];
		if (allMax < sum) {
			allMax = sum;
		}
	}
	sum = allMax; // 保留最大值
	for (i = middleIndex + 1; i <= maxIndex; i++) {
		sum += nums[i]; // 往左累加最大值继续累加，找到左右累加最大值
		if (allMax < sum) {
			allMax = sum;
		}
	}
	// 比较左侧最大子段和右侧最大子段还有中间往两边累加的最大值看看谁更大
	if (allMax < leftMax) {
		allMax = leftMax;
	}
	else if (allMax < rightMax) {
		allMax = rightMax;
	}
	return allMax;
}

int main(int argc, char **argv) {
	int nums[] = { -8, 11, -4, 13, -9, -10,11,12,13 };
	printf("max sub:%d\n", maxSubValues(nums, 0, sizeof nums / sizeof(int) - 1));
	system("pause");
	return 0;
}
