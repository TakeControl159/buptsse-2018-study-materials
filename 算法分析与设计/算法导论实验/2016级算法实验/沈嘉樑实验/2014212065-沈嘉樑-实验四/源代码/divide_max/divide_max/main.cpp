#include<iostream>
using namespace std;
int MaxSum(int a[], int left, int right){
  int sum = 0;
  if (left == right){ // if the length of sequence is 1
    if (a[left] > 0)
      sum = a[left];
    else sum = 0;
  }
  else{
    int center = (left + right) / 2;
    int leftSum = MaxSum(a, left, center);
    int rightSum = MaxSum(a, center+1, right);
    int maxLeft = 0; //record the maximum of the left part
    int lefts = 0;
    for (int i = center; i >= left; i--){
      lefts += a[i];
      if (lefts > maxLeft) maxLeft = lefts;
    }
    int maxRight = 0;
    int rights = 0;
    for (int j = center + 1; j <= right; j++){
      rights += a[j];
      if (rights > maxRight) maxRight = rights;
    }
    sum = maxLeft + maxRight;
    if (sum < leftSum) sum = leftSum;
    if (sum < rightSum) sum = rightSum;
  }
  return sum;
}
int main(){
  int number;
  int sum;
  int a[1000];
  cout << "Please input the number of integers: ";
  cin >> number;
  cout << "Please input all of the integers:" << endl;
  for (int i = 0; i < number; i++)
    cin >> a[i];
  sum = MaxSum(a, 0, number - 1);
  if (sum < 0) sum = 0;
  cout << "Maximum: " << sum <<endl;
}
