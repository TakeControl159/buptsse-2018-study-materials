#include <stdio.h>
#include <stdlib.h>
#include <memory.h> 

int nCount = 0;
int Matrix[100][100];

void chessBoard(int tr, int tc, int dr, int dc, int size);

int main()
{
    int size,r,c,row,col;
    memset(Matrix,0,sizeof(Matrix));
    printf("请输入棋盘大小（必须为2的k次方）：\n");
    scanf("%d",&size);
    printf("请输入特殊方格位置： \n"); 
    scanf("%d%d",&row,&col);
    chessBoard(0,0,row,col,size);
    printf("棋盘： \n"); 

    for (r = 0; r < size; r++)
    {
        for (c = 0; c < size; c++)
        {
            printf("%2d ",Matrix[r][c]);
        }
        printf("\n");
    }

    return 0;
}

void chessBoard(int tr, int tc, int dr, int dc, int size)
{
    int s,t;
    if (1 == size) return;
    s = size/2; 
    t = ++ nCount;
    if (dr < tr + s && dc < tc +s)
    {
        chessBoard(tr,tc,dr,dc,s);
    }
    else
    {
        Matrix[tr+s-1][tc+s-1] = t;
        chessBoard(tr,tc,tr+s-1,tc+s-1,s);
    }
    if (dr < tr + s && dc >= tc + s )
    {
        chessBoard(tr,tc+s,dr,dc,s);
    }
    else
    {
        Matrix[tr+s-1][tc+s] = t;
        chessBoard(tr,tc+s,tr+s-1,tc+s,s);
    }
    if (dr >= tr + s && dc < tc + s)
    {
        chessBoard(tr+s,tc,dr,dc,s);
    } 
    else
    {
        Matrix[tr+s][tc+s-1] = t;
        chessBoard(tr+s,tc,tr+s,tc+s-1,s);
    }
    if (dr >= tr + s && dc >= tc + s)
    {
        chessBoard(tr+s,tc+s,dr,dc,s);
    } 
    else
    {
        Matrix[tr+s][tc+s] = t;
        chessBoard(tr+s,tc+s,tr+s,tc+s,s);
    }

}
