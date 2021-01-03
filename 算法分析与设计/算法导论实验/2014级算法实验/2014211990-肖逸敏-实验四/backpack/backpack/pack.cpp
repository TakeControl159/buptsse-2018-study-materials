#include <iostream>
using namespace std;
typedef struct 
{ 
	int v; 
	int w;
	float pv;
}pvu; 

void sortByPv(pvu[], int);
int   zeroneBags(pvu[], int, int, int *); 
void print(pvu a[], int n) 
{ 
	for (int i = 0; i<n; i++) 
	{ 
		cout << a[i].w << " " << a[i].v << " " << a[i].pv << endl;
	} 
	cout << endl;
}

int main() {

	int remained=0;
	int i, maxw;  
	int w[] = { 1, 2, 3, 2 }; 
	int v[] = { 9, 10, 15, 6 }; 
	int n = sizeof(w) / sizeof(int);  
	int N = n;
	pvu arr[30]; 
	for (i = 0; i<n; i++) 
	{ 
		arr[i].v = v[i]; 
		arr[i].w = w[i];
		arr[i].pv = v[i] * 1.0 / w[i];
	} 
	cout << "已知物品的重量分别为1，2，3，2" << endl;
	cout << "物品的价值分别为9，10，15，6" << endl;
	cout << "输入背包的最大承重量:\n"; 
	cin >> maxw; 
	cout << "最大价值为:" << zeroneBags(arr, n, maxw, &remained) << "\n还剩" << remained << "空间未使用" << endl;
	return 0;
}
void sortByPv(pvu arr[], int n)
{ 
	pvu t;  
	int i, j; 
	for (i = 0; i<n - 1; i++)
		for (j = 0; j<n - 1 - i; j++)     
			if (arr[j].pv<arr[j + 1].pv)  
			{
		t = arr[j];  
		arr[j] = arr[j + 1];   
		arr[j + 1] = t;
			} 
}
int   zeroneBags(pvu arr[], int n, int maxw, int *e)
{
	int i = 0, j, minw, totalv = 0;
	int avail = maxw; 
	sortByPv(arr, n); //按最大单位重量价值PV从大到小的排序 
	while (avail&&i<n) 
	{ 
		minw=i; 
		for (j=0;j<n;j++) 
			if (arr[i].pv==arr[j].pv) 
			{ 
			if (arr[i].w>arr[j].w&&j>i)  
			{  
				minw=j;  
			} 
			}  
		if (arr[minw].w<=avail) 
		{   
			avail-=arr[minw].w;  
			totalv+=arr[minw].v; 
			i++;  
		} 
		else  
			i++; 
	} 
	*e = avail; 
	return totalv;
}