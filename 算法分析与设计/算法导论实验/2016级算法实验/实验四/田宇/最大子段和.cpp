#include <stdio.h>

int MaxSum(int a[],int left,int right);

int main()
{
    int n,a[100];
    printf("请输入序列长度： \n"); 
    scanf("%d",&n);
    printf("请输入序列： \n");
    for(int i=0;i<n;i++)
        scanf("%d",&a[i]);
    int sum = MaxSum(a,0,n-1);
    printf("最大子段和为： \n");
    printf("%d",sum);
    return 0;
}

int MaxSum(int a[],int left,int right)
{
    int sum=0,midsum=0,leftsum=0,rightsum=0;
    int center,s1,s2,lefts,rights;
    if(left == right)
        sum = a[left];
    else
    {
        center = (left+right)/2;
        leftsum = MaxSum(a,left,center);
        rightsum = MaxSum(a,center+1,right);
        s1 = -9999,lefts = 0;
        for(int j=center;j>=left;j--)
        {
            lefts+=a[j];
            if(lefts>s1)
                s1=lefts;
        }
        s2=-9999,rights=0;
        for(int i=center+1;i<=right;i++)
        {
            rights+=a[i];
            if(rights>s2)
                s2=rights;
        }
        midsum=s1+s2;
        if(midsum<leftsum)
            sum=leftsum;
        else
            sum=midsum;
        if(sum<rightsum)
            sum=rightsum;
    }
    return sum;
}
