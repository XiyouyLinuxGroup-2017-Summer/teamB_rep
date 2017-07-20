/*************************************************************************
	> File Name: aaa.c
	> Author:hxllhhy
	> Mail:hxllhhy@gmail.com
	> Created Time: 2017年07月20日 星期四 19时37分50秒
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
