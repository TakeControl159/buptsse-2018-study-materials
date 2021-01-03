#include <iostream>
#include <fstream>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

const int MAX = 50;
int board[MAX][MAX];  //记录方格被监视情况
int root[MAX][MAX];      //记录机器人位置
int m, n;             //矩阵为 m * n
int k = 0;                //机器人个数
int bestk;

void compute()
{
    memset(root, 0, sizeof(root));
    bool ok = false;
    int i, k;
    if(m == 1)  //矩阵只有一行的情况
    {
        k = n / 3;
        if(n%3 == 1)
        {
            for(i=0; i<=k; i++)
                root[1][3*i+1] = 1;
        }
        else
        {
            if(n%3 == 0)
                k--;
            for(i=0; i<=k; i++)
                root[1][3*i+2] = 1;
        }
        bestk = k + 1;
        ok = true;
    }
    if(n == 1) //矩阵只有一列的情况
    {
        k = m / 3;
        if(m%3 == 1)
        {
            for(i=0; i<=k; i++)
                root[1][3*i+1] = 1;
        }
        else
        {
            if(m%3 == 0)
                k--;
            for(i=0; i<=k; i++)
                root[1][3*i+2] = 1;
        }
        bestk = k + 1;
        ok = true;
    }
    if(m==2 && n%2 == 1) //矩阵有2行，且列数为奇数
    {
        int k = n / 4;
        if(m%4 == 0)
            k--;
        for(i=0; i<=k; i++)
        {
            root[1][4*i+3] = 1;
            root[2][4*i+1] = 1;
        }
        bestk = 2 * k + 2;
        ok = true;
    }
    if(n==2 && m%2 == 1) //矩阵有2列，且行数为奇数
    {
        int k = m / 4;
        if(n%4 == 0)
            k--;
        for(i=0; i<=k; i++)
        {
            root[1][4*i+3] = 1;
            root[2][4*i+1] = 1;
        }
        bestk = 2 * k + 2;
        ok = true;
    }
    if(n==4 && m==4)  //4行4列
    {
        root[1][1] = 1;
        root[1][4] = 1;
        root[4][1] = 1;
        root[4][4] = 1;
        bestk = 4;
        ok = true;
    }
    if(ok)
    {
        //cout << "最少的机器人个数为：" << bestk << endl;
        //cout << "机器人位置为：\n";
        for(int i=1; i<=m; i++)
        {
            for(int j=1; j<=n; j++)
                cout << root[i][j] << " ";
            cout << endl;
        }
    }
    else
        cout << "-1\n";
}

int main()
{
    while(cin >> m>>n){
    compute();
    cout << endl;
    }
    return 0;
}
