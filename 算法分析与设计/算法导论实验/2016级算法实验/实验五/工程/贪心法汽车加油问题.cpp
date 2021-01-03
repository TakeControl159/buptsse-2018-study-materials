#include<stdio.h>

int greedy(int A[],int d,int n){
	int num=0;
	for(int i=0;i<=n;i++){
		if(A[i]>d){
			printf("无解。\n");
			return 0;
		}
	}
	for(int i=0,s=0;i<=n;i++){
		s+=A[i];
		if(s>d){
			num++;
			s=A[i];
		}
	}
	printf("最少加油次数为%d.\n",num);
}
int main(){
	int i,d,n;
	int A[100];
	printf("请输入每次加油可行驶路程： \n"); 
	scanf("%d",&d);
	printf("请输入加油站个数： \n"); 
	scanf("%d",&n); 
	printf("请输入%d个加油站之间距离： \n",n); 
	for(i=0;i<n;i++){
	scanf("%d",&A[i]);  
    }
    greedy(A,d,n);
} 


