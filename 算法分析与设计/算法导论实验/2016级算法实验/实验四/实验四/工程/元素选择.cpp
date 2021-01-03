#include<stdlib.h>
#include<time.h>
#include<stdio.h>
#include<malloc.h>

int partition(int a[],int p,int r)
{
	int z=p,x=r+1;
	int y=a[p];
	int t;
	while(1)
	{
		while(a[++z]<y&&z<r);//空循环，不符合条件时向下执行
		while(a[--x]>y);
		if(z>=x)break;
		t=a[z];
		a[z]=a[x];
		a[x]=t;
	}
	a[p]=a[x];
	a[x]=y;
	return x;
}

void SelectforPosition(int a[],int p,int r)
{
	int q;
	if(p<r)
	{
		q=partition(a,p,r);
		SelectforPosition(a,p,q-1);
		SelectforPosition(a,q+1,r);
	}
}

int main()
{
	int k,*a,*b,n,i,d,s;

	printf("请输入数组个数: \n");
	scanf("%d",&n);
	a=(int *)malloc(sizeof(int)*n);
	b=(int *)malloc(sizeof(int)*n);
	printf("请输入序列: \n");
	for(i=0 ; i<n; i++)
	{
		scanf("%d",&a[i]);
	}
	for(i=0,d=0; d<n; d++)
	{
		b[d]=a[i];
		i++;
	}
	printf("\n");
	printf("请输入第k小元素:");
	scanf("%d",&k);
	for(d=0; d<n; d++)
	{
		if(b[d]==a[k-1])
			s=d+1;
	}
	printf("第%d小元素为:%d\n",k,a[k-1]);
	printf("第%d小元素位置为:%d",k,s);
	printf("\n");
}
