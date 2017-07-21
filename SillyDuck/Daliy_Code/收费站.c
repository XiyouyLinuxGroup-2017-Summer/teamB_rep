/*************************************************************************
	> File Name: 2.c
	> Author:hxllhhy
	> Mail:hxllhhy@gmail.com
	> Created Time: 2017年07月21日 星期五 09时36分12秒
 ************************************************************************/

#include<stdio.h>
int main()
{
    int n,m,sum;
    scanf("%d",&n);
    while(n--)
    {
        scanf("%d",&m);
        sum=3;
        while(m--)
        {
            sum=2*(sum-1);
        }
        printf("%d\n",sum);
    }
    return 0;
}
