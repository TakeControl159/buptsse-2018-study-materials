#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

int Partition(int *A, int p ,int r)
{
	int x = A[r];
	int i = p-1;
	for(int j  = p; j<=r-1; j++)
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
	printf("请输入数组个数: \n");
	cin>>n;
	for(int i = 1; i<=n; i++)
		cin>>A[i];
	printf("请输入查询的位置: \n");
	cin>>k;
	int ans = Select(A,1,n,k);
	for(int j=0;j<n;j++)
	{
		if(A[j]==ans)
			printf("位置为%d",j);
	}
	printf("\n");
	printf("%d",ans);	
}
