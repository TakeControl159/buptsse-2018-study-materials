//1.h程序
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


