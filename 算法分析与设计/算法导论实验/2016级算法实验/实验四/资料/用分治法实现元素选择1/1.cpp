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
void quicksort(int a[],int p,int r)
{
 int q;
 if(p<r)
 {
  q=partition(a,p,r);
        quicksort(a,p,q-1);
        quicksort(a,q+1,r);
 }
}   

int main()
{
 for(;;)
 {
 int k,*a,*b,n,i,d,s;
   
    printf("请输入数组个数: \n");
    scanf("%d",&n);
    a=(int *)malloc(sizeof(int)*n);  //给数组a分配空间
    srand((unsigned)time(NULL));
    b=(int *)malloc(sizeof(int)*n); //给数组b分配空间
    srand((unsigned)time(NULL)); 
    printf("请输入序列: \n");
	for(i=0 ;i<n;i++){
		scanf("%d",&a[i]);
    }
	for(i=0,d=0;d<n;d++){   //将数组a赋给b 
		b[d]=a[i];
		i++;
	}
	quicksort(a,0,i-1);            //调用快速排序进行排序
	printf("排序后: \n");
	for(i=0;i<n;i++){
		printf("%d ",a[i]);
    }
    printf("\n");
	printf("请输入第k小元素:");
    scanf("%d",&k);
	for(d=0;d<n;d++){
		if(b[d]==a[k-1])          //从数组b中找出第k小的数在原数组中的位置
        s=d+1;
    }
	printf("第%d小元素为:%d\n",k,a[k-1]);
	printf("第%d小元素位置为:%d",k,s);
	printf("\n"); 
	system("pause");
 }
}
