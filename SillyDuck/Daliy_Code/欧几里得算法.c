/*************************************************************************
	> File Name: 欧几里得算法.c
	> Author:hxllhhy
	> Mail:hxllhhy@gmail.com
	> Created Time: 2017年07月21日 星期五 01时34分10秒
 ************************************************************************/

#include<stdio.h>

long long gcd(long long m,long long n)
{
        return n==0?m:gcd(n,m%n);

}

int main()
{
        int a,b;
        scanf("%d %d",&a,&b);
        printf("%lld\n",gcd(a,b));
        return 0;

}
