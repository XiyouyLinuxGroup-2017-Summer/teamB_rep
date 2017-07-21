/*************************************************************************
	> File Name: 7.c
	> Author:hxllhhy
	> Mail:hxllhhy@gmail.com
	> Created Time: 2017年07月19日 星期三 10时25分48秒
 ************************************************************************/

#include<stdio.h>
int cow(int n)
{
    if(n==1)
        return 1;
    if(n==2)
        return 2;
    if(n==3)
        return 3;
    if(n>3)
        return cow(n-1)+cow(n-3);
}
int main()
{
    int n;
    while(scanf("%d",&n)!=EOF)
    {
        if(n==0)
            break;
        printf("%d\n",cow(n));
    }
    return 0;
}
