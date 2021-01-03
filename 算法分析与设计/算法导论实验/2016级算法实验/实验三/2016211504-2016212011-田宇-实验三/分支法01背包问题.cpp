/*
*
*分支限界法求解01背包问题 
*
*BY Tian Yu 2018 11 22
*
*
*
*/

#include<iostream>
#include<cstdio>
#include<conio.h>
#include<iomanip>
using namespace std;
int *x;
struct node
{
	//结点表的结点数据结构
	node  *parent,//父结点指针
	      *next; //后继结点指针
	int    level,//结点的层
	       bag,//节点的解
	       cw,//当前背包装载量
	       cp;//当前背包价值
	float  ub; //结点的上界值
};
class Knap
{
	private:
		struct    node      *front, //队列队首
				*bestp,*first; //解结点、根结点
		int       *p,*w,n,c,*M;//背包价值、重量、物品数、背包容量、记录大小顺序关系
		long      lbestp;//背包容量最优解
	public:
		void Sort();
		Knap(int *pp,int *ww,int cc,int nn);
		~Knap();
		float Bound(int i,int cw,int cp);//计算上界限
		node *nnoder(node *pa,int ba,float uub);//生成一个结点 ba=1生成左节点 ba=0生成右节点
		void addnode(node *nod);//将结点添加到队列中
		void deletenode(node *nod);//将结点队列中删除
	struct node *nextnode(); //取下一个
		void display(); //输出结果
		void solvebag(); //背包问题求解
};

Knap::Knap(int *pp,int *ww,int cc,int nn)
{
	int i;
	n=nn;
	c=cc;
	p=new int[n];
	w=new int[n];
	M=new int[n];
	for(i=0; i<n; i++)
	{
		p[i]=pp[i];
		w[i]=ww[i];
		M[i]=i;
	}
	front=new node[1];
	front->next=NULL;
	lbestp=0;
	bestp=new node[1];
	bestp=NULL;
	Sort();
}
Knap::~Knap()
{
	delete []first;
	delete []front;
	delete []bestp;
	delete []p;
	delete []w;
}
float Knap::Bound(int i,int cw,int cp)
{
	// 计算上界
	int cleft=c-cw;
	float b=(float)cp;
	while (i<n&&w[i]<=cleft)
	{
		cleft-=w[i];
		b+=p[i];
		i++;
	}
	if (i<n) b+=1.0*p[i]/w[i]*cleft;
	return b;
}
node * Knap::nnoder(struct node *pa,int ba,float uub)
{
	//生成一个新结点
	node * nodell=new(node);
	nodell->parent=pa;
	nodell->next=NULL;
	nodell->level=(pa->level)+1;
	nodell->bag=ba;
	nodell->ub=uub;
	if(ba==1)
	{
		nodell->cw=pa->cw+w[pa->level];
		nodell->cp=pa->cp+p[pa->level] ;
	}
	else
	{
		nodell->cw=pa->cw;
		nodell->cp=pa->cp;
	}
	return(nodell);
}

void Knap::addnode(node *no)
{
	//将结点加入优先队列
	node *p=front->next,*next1=front;
	float ub=no->ub;
	while(p!=NULL)
	{
		if(p->ub<ub)
		{
			no->next=p;
			next1->next=no;
			break;
		}
		next1=p;
		p=p->next;
	}
	if(p==NULL)
	{
		next1->next=no;
	}
}

node *Knap::nextnode()
{
	//取上限最大结点
	node *p=front->next;
	front->next=p->next;
	return(p);
}

void Knap::Sort()
{
	int i,j,k,kkl;
	float minl;
	for(i=1; i<n; i++)
	{
		minl=1.0*p[i]/w[i];
		k=0;
		for(j=1; j<=n-i; j++)
		{
			if(minl<1.0*p[j]/w[j])
			{
				minl=1.0*p[j]/w[j];
				swap(p[k],p[j]);
				swap(w[k],w[j]);
				swap(M[k],M[j]);
				k=j;
			}
		}
	}
}

void Knap::display()
{
	int i;
	for(i=n; i>=1; i--)
	{
		x[M[i-1]]=bestp->bag;
		bestp=bestp->parent;
	}
	cout<<"当你选择这几个物品，获得最有价值的子集: "<<endl;
	for(i=1; i<=n; i++)
	{
		if(x[i-1])
			cout<<i<<"th"<<endl;
	}

	cout<<"总价值为:"<<lbestp<<endl;
}

void Knap::solvebag()
{
	//背包问题求解
	int i;
	float ubb;
	node *aa;
	first=new node[1]; //根结点
	first->parent=NULL;
	first->next=NULL;
	first->level=0;
	first->cw=0;
	first->cp=0;
	first->bag=0;
	ubb=Bound(0,0,0);
	first->ub=ubb;
	front->next=first;
	while(front->next!=NULL)
	{
		aa=nextnode();
		i=aa->level;
		if(i==n-1)
		{
			if(aa->cw+w[i]<=c&&(long)(aa->cp+p[i])>lbestp)
			{
				lbestp=aa->cp+p[i];
				bestp=nnoder(aa,1,(float)lbestp);
			}
			if((long)(aa->cp)>lbestp)
			{
				lbestp=aa->cp;
				bestp=nnoder(aa,0,(float)lbestp);
			}
		}
		if(i<n-1)
		{
			if(aa->cw+w[i]<=c&&Bound(i+1,
			                         aa->cw+w[i],aa->cp+p[i])>(float)lbestp)
			{
				ubb=Bound(i,aa->cw+w[i],aa->cp+p[i]);
				addnode(nnoder(aa,1,ubb));
			}
			ubb=ubb=Bound(i,aa->cw,aa->cp);
			if(ubb>lbestp)
				addnode(nnoder(aa,0,ubb));
		}
	}
	display();
}

int main()
{
	int c,n;
	int i=0;
	int *p;
	int *w;
	cout<<"请输入背包容量:"<<endl;
	cin>>c;
	cout<<"请输入物品数:"<<endl;
	cin>>n;
	x=new int[n];
	p=new int[n];
	w=new int[n];
	cout<<"请输入"<<n<<"个物品的重量:"<<endl;
	for(i=0; i<n; i++)
		cin>>w[i];
	cout<<"请输入"<<n<<"个物品价值:"<<endl;
	for(i=0; i<n; i++)
		cin>>p[i];
	x=new int[n];
	Knap knbag(p,w,c,n);
	knbag.solvebag();
	getch();
	return 0;
}

