#include <stdio.h> 

int sum(int a[10001],int n) 
  { 
  int s=0,i;
  for(i=0;i<n;i++) 
  if(a[i]>a[n/2]) 
  s+=a[i]-a[n/2]; 
  else s+=a[n/2]-a[i]; 
  return s; 
  }
void sort(int a[10001],int n) 
{ 
  int i,j,tem; 
  for(i=0;i<n;i++) 
     { 
	   for(j=i+1;j<n;j++) 
	       if(a[i]>a[j])
		      {
			   tem=a[i]; 
			   a[i]=a[j]; 
			   a[j]=tem; 
			   } 
	 } 
}
int main() 
{ 
   int i,x,y,n,ax[10001],ay[10001]; 
   printf("请输入居民点个数： \n");
   scanf("%d",&n);
   printf("依次输入坐标，如“2 3”： \n");
   for(i=0;i<n;i++) 
     scanf("%d %d",&ax[i],&ay[i]);
	 sort(ax,n); 
	 sort(ay,n);
     printf("该街区%d个居民点到邮局的距离总和最小为：%d\n",n,sum(ax,n)+sum(ay,n));
     return 0;
 }

