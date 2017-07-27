/*************************************************************************
	> File Name: qipan.c
	> Author:hxllhhy
	> Mail:hxllhhy@gmail.com
	> Created Time: 2017年07月27日 星期四 08时44分24秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define maxn 10

char board[maxn][maxn];
int place[maxn];  //记录一列是否已经放过棋子
int n,k;
int cnt,num;//cnt是放棋子方案数，num是放棋子方案数已放棋子数

void dfs(int i)
{
    if(k==num)
    {
        cnt++;
        return ;
    }

    if(i>=n)
        return ;

    for(int j=0;j<n;j++)
    {
        if(place[j]==0&&board[i][j]=='#')
        {
            place[j]=1;
            num++;
            dfs(i+1);
            place[j]=0;
            num--;
        }
    }
    dfs(i+1); //i行不放棋子
}

int main()
{
    int i,j;
    while(scanf("%d %d",&n,&k)!=EOF)
    {
        getchar();
        if(n==-1&&k==-1)
            break;
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                scanf("%c",&board[i][j]);
            }
            getchar();
        }
        memset(place,0,sizeof(place));
        cnt=0;
        num=0;
        dfs(0);
        printf("%d\n",cnt);
    }
    return 0;
}
