#include<iostream>
using namespace std;
int a[1000];
void Qsort(int low, int high){
    if(low >= high){
        return;
    }
    int first = low;
    int last = high;
    int key = a[first];
    while(first < last){
        while(first < last && a[last] >= key)
          --last;
        a[first] = a[last];
        while(first < last && a[first] <= key)
          ++first;
        a[last] = a[first];
    }
    a[first] = key;
    Qsort(low, first-1);
    Qsort(first+1, high);
}
int main(){
  int n, k;
  cout << "请分别输入n,k:";
  cin >> n >> k;
  cout << "请输入数组元素:" <<endl;
  for (int i = 0; i < n; i++)
    cin >> a[i];
  Qsort(0, n - 1);
  cout << "结果为：" << a[k - 1] <<endl;
}
