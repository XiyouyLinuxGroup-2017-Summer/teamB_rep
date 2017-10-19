/*************************************************************************
	> File Name: B.c
	> Author:九五二七 
	> Mail: 
	> Created Time: 2017年07月31日 星期一 15时32分26秒
 ************************************************************************/

#include<stdio.h>
int  flag;
void  dfs (long long y  ,int  k , int  num  )
{
    if (flag == 1 || num >= 19)
    {
        return ;
    }
    if (y % k == 0) 
    {
        flag = 1;
        printf("%lld\n",y);
        return ;
    }
    dfs(y*10, k ,num+1);
    dfs(y*10 + 1 , k, num+1);
    return ;
}
int main ()
{
    int  n;
    while (scanf("%d",&n) && n ){
        flag = 0;
        dfs (1,n,0);
    }
return 0;
}
