/*************************************************************************
	> File Name: B.c
	> Author:九五二七 
	> Mail: 
	> Created Time: 2017年08月02日 星期三 11时29分53秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
int  R,C;
int  was[4][2]={-1,0,1,0,0,-1,0,1}; //控制四个方向
int  max = 0;  //个数
char  str[22][22];   //图
char  vist[30]; // 记录访问过的

void  dfs(int x,int y,int count)
{

    int xx,yy,i,j;
    if (max<count )
    max = count;    // 
    for (i = 0; i< 4 ;i++)
    {
        xx = x + was[i][0];
        yy = y + was[i][1];
        if(xx < 0 || xx >= R || yy >= C || yy < 0)    continue;   // 判断范围是否合法
        for (j=1;j<=count; j++){         
            if (vist[j] == str[xx][yy])
                break;
        }    
        if (j <= count  )  continue;   //以上五行判断是否有重复 
        else { 
            vist[count+1] = str[xx][yy];
            dfs(xx,yy,count+1);
            vist[count+1] = '\0';
        }    
    }
}
int main ()
{
    int i =0; 
    
    while(scanf("%d %d",&R,&C) != EOF  ){
        max = 0;
        for (i=0 ; i<R;i++ )
            scanf("%s",str[i]);
        vist[1]=str[0][0];
        dfs(0,0,1);
    printf("%d\n",max);
   // memeset(vist,0,sizeof(char) * 30);
    }
}
