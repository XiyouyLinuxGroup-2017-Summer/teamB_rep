/*************************************************************************
	> File Name: 字母dfs.c
	> Author:hxllhhy
	> Mail:hxllhhy@gmail.com
	> Created Time: 2017年08月02日 星期三 11时44分49秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int r,c,step,max;
int book[20][20],num[26];
char a[20][20];

void dfs(int x,int y,int step)
{
    int tx,ty,k;
    int next[4][2]={{0,1},{1,0},{0,-1},{-1,0}};

    //更新最大步数
    if(step>max)
        max=step;

    //枚举4种走法
    for(k=0;k<=3;k++)
    {
        //计算下一个点的坐标
        tx=x+next[k][0];
        ty=y+next[k][1];

        //判断是否越界
        if(tx<0||tx>=r||ty<0||ty>=c)
            continue;
        //判断该点是否走过并且是与以前不同的字母
        if(book[tx][ty]==0&&num[a[tx][ty]-'A']==0)
        {
            book[tx][ty]=1;  //标记该点走过
            num[a[tx][ty]-'A']=1;  //标记该点的字母走过
            dfs(tx,ty,step+1);  //开始尝试下一个点
            book[tx][ty]=0;  //尝试结束，取消这个点
            num[a[tx][ty]-'A']=0;
        }
    }
    return ;
}

int main()
{
    int i;

    memset(a,0,sizeof(a));
    memset(a,0,sizeof(book));
    memset(a,0,sizeof(num));
    
    //读入r行 c列
    while(scanf("%d %d",&r,&c)!=EOF)
    {
        //读入字母
        for(i=0;i<r;i++)
            scanf("%s",a[i]);

        //给定起点
        book[0][0]=1;
        num[a[0][0]-'A']=1;
        max=step=1;
        dfs(0,0,1);

        //输出最长步数，即经过最多不同字母的个数
        printf("%d\n",max);
    }
    return 0;
}
