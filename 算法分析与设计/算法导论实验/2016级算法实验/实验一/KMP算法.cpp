#include<cstdio>
#include<cstring>#include<iostream>
#include<algorithm>
using namespace std;
char a[1000100],b[1000100];
int p[1000100];
int main()
{
	scanf("%s%s",a+1,b+1);
	int la=strlen(a+1),lb=strlen(b+1);
	int j=0;
	p[1]=0;
	//先处理出p数组，无非是b和自己匹配，与b和a匹配一样，故代码差不多
	for(int i=2; i<=lb; i++)
	{
		while(j>0 && b[i]!=b[j+1]) j=p[j];//往前翻记录了有相同前缀的j
		if(b[i]==b[j+1]) j++;//i匹配成功了，i继续往后
		p[i]=j;
	}
	j=0;
	for(int i=1; i<=la; i++)
	{
		while(j>0 && a[i]!=b[j+1]) j=p[j];
		if(a[i]==b[j+1]) j++;
		if(j==lb) printf("%d\n",i-lb+1),j=p[j];
	}
	for(int i=1; i<lb-1; i++)
		printf("%d ",p[i]);
	//printf("%d",p[lb]);
	return 0;
}
