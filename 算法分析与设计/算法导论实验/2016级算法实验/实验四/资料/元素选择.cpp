#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int Partition(int *A, int p ,int r)
{
    int x = A[r];
    int i = p-1;
    for(int j  = p;j<=r-1;j++)
    {
        if(A[j] <= x)
        {
            i++;
            swap(A[i],A[j]);
        }
    }
    swap(A[i+1],A[r]);
    return i+1;
}
int Select(int *A, int p, int r, int i)
{
    if(p==r)
        return A[p];
    int q = Partition(A,p,r);
    int k = q-p+1;
    if(i==k)
        return A[q];
    else if(i<k)
        return Select(A,p,q-1,i);
    else
        return Select(A,q+1,r,i-k);
}
int A[30000];
int main()
{
	int n,k;
	cout<<"请输入数组长度:  "<<endl; 
	cin>>n;
	cout<<"要查找第k小的元素，请输入整数k： "<<endl;
	cin>>k;
	cout<<"请输入序列:  "<<endl; 
	for(int i = 1;i<=n;i++)
        cin>>A[i];
    int ans = Select(A,1,n,k);
    cout<<"第"<<k<<"小元素的值为： "<<ans<<endl;
}
