#include<fstream>
#include<iostream>
using namespace std;

ifstream fin ("input.txt");
ofstream fout("output.txt");

class Exhibit_hall{
	friend void Setrobot(int ,int);
	
private:
	void set(int i,int j,int a[]);//放置机器人
	void recover(int i,int j,int a[]);
	void Backtrack(int i,int j);
	void GreedySearch();	//贪婪搜索
	int search(int i,int j);	//搜索在a[i][j]处设置机器人时它所监督未被监督的陈列室个数
	void set(int i,int j);		
	int m,n;	//陈列馆的行数,列数
	int mn;		//陈列室个数
	int g_num;	//陈列室中已被监视的个数
	int num;	//当前机器人个数
	int num1;	//用于贪心搜索中机器人的个数
	int **x;	//当前解
	int bestn;	//当前最优解的个数
	int **bestx;//当前最优解
};


void Exhibit_hall::set(int i,int j,int a[])//x[][]为1表示此房间已放置了一个机器人，为2表示此房间已被监视
{
	num++;
	a[0]=x[i][j];
	if(a[0]==0) g_num++;//若此陈列室未被监视，则此时已被监视g_num++
	x[i][j]=1;//此位置放置了一个机器人
	if(x[i-1][j]==0) {a[1]=1;x[i-1][j]=2;g_num++;}//若上方未被监视,则此时设置未已被监视
	if(x[i][j+1]==0) {a[2]=1;x[i][j+1]=2;g_num++;}
	if(x[i+1][j]==0) {a[3]=1;x[i+1][j]=2;g_num++;}
	if(x[i][j-1]==0) {a[4]=1;x[i][j-1]=2;g_num++;}
}
	
void Exhibit_hall::recover(int i,int j,int a[])//撤消机器人
{
	num--;
	x[i][j]=a[0];
	if(a[0]==0) g_num--;

	if(a[1]) {x[i-1][j]=0;g_num--;}
	if(a[2]) {x[i][j+1]=0;g_num--;}
	if(a[3]) {x[i+1][j]=0;g_num--;}
	if(a[4]) {x[i][j-1]=0;g_num--;}
	a[0]=0;a[1]=0;a[2]=0;a[3]=0;a[4]=0;
}


void Exhibit_hall::Backtrack(int i,int j)//回溯
{
	if(i>m){
		if(num<bestn)
		{
			for(int k=1;k<m+1;k++)
				for(int l=1;l<n+1;l++)
					bestx[k][l]=x[k][l];
			bestn=num;
		}
		return;
	}

	if(num+(mn-g_num)/5>=bestn) return;

	//当此陈列室已被监视，则没必要在此陈列室放设置警卫机器人
	//因为x[i+1][j+1]放置一机器人优于此处放机器人

	if(x[i][j]!=0)
		Backtrack(i+j/n,j%n+1);

	//在此陈列室被监视
	else
	{
		int a[5]={0};
		if(i<m)		//在此陈列室下面放置机器人监视此陈列室
		{
			set(i+1,j,a);
			Backtrack(i,j);
			recover(i+1,j,a);
		}
		if((j<n) && (x[i][j+1]==0||x[i][j+2]==0))		//在此陈列室右边放置机器人监视此陈列室
		{
			set(i,j+1,a);
			Backtrack(i,j);
			recover(i,j+1,a);
		}
		if(x[i+1][j]==0&&x[i][j+1]==0)		//在此陈列室放置机器人
		{
			set(i,j,a);
			Backtrack(i,j);
			recover(i,j,a);
		}
	}
}
int Exhibit_hall::search(int i,int j)
{
	if(i==m+1||j==n+1) return 0;
	int count=0;
	if(x[i][j]==0)count ++;
	if(x[i-1][j]==0)count ++;
	if(x[i][j+1]==0)count ++;
	if(x[i+1][j]==0)count ++;
	if(x[i][j-1]==0)count ++;
	return count;
}
void Exhibit_hall::set(int i,int j)
{
	num1++;
	x[i][j]=1;

	if(x[i-1][j]==0)x[i-1][j]=2;
	if(x[i][j+1]==0)x[i][j+1]=2;
	if(x[i+1][j]==0)x[i+1][j]=2;
	if(x[i][j-1]==0)x[i][j-1]=2;
}
	
void Exhibit_hall::GreedySearch()
{
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
		{
			if(x[i][j]==0)
			{
				int a1=0,a2=0,a3=0;
				a1=search(i,j);
				a2=search(i+1,j);
				a3=search(i,j+1);
				if(a1>=a2&&a1>=a3)set(i,j);
				else{
					if(a2>=a3)
					{
						if(a2>a3)set(i+1,j);
						else 
							if(x[i+1][j]!=0&&x[i][j+1]==0)set(i,j+1);
							else set(i+1,j);
					}
					else set(i,j+1);
				}
			}
		}
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
		{
			bestx[i][j]=x[i][j];
			x[i][j]=0;
		}
	bestn=num1;
}
				
				

void Setrobot(int m,int n)
{
	Exhibit_hall Ex;
	Ex.m=m;
	Ex.n=n;
	Ex.mn=m*n;
	Ex.num=0;
	Ex.num1=0;
	Ex.bestn=m*n;
	Ex.g_num=0;
	Ex.x=new int*[m+2];
	for(int i=0;i<m+2;i++)
	{
		Ex.x[i]=new int[n+2];
		for(int j=0;j<n+2;j++)Ex.x[i][j]=0;
	}

	Ex.bestx=new int*[m+2];
	for(int i=0;i<m+2;i++)
	{
		Ex.bestx[i]=new int[n+2];
		for(int j=0;j<n+2;j++)Ex.bestx[i][j]=0;
	}
	for(int k=0;k<n+2;k++){Ex.x[0][k]=2;Ex.x[m+1][k]=2;}
	for(int k=1;k<m+1;k++){Ex.x[k][0]=2;Ex.x[k][n+1]=2;}
	
	Ex.GreedySearch();

	cout<<Ex.bestn<<endl;

	Ex.Backtrack(1,1);

	fout<<Ex.bestn<<endl;
	for(int j=1;j<=m;j++){
		for(int k=1;k<=n;k++)
		{
			if(Ex.bestx[j][k]==1)fout<<1<<' ';
			else fout<<0<<' ';
		}
		fout<<endl;
	}	
	delete [] Ex.x;
	delete [] Ex.bestx;
}
int main()
{
	int m,n;
	fin>>m>>n;
	Setrobot(m,n);
}


