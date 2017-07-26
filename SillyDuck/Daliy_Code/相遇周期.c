/*************************************************************************
	> File Name: 相遇周期.c
	> Author:hxllhhy
	> Mail:hxllhhy@gmail.com
	> Created Time: 2017年07月24日 星期一 15时44分12秒
 ************************************************************************/

#include<stdio.h>
long long int gcd(long long int m,long long int n)
{
    return n==0?m:gcd(n,m%n);
}
long long int lcm(long long int m,long long int n)
{
    return m*n/gcd(m,n);
}
int main()
{
    long long int a,b,c,d,i,j,t;
    int n;
    scanf("%d",&n);
    while(n--)
    {
        scanf("%lld/%lld %lld/%lld",&a,&b,&c,&d);
        t=gcd(a,b);
        a/=t;
        b/=t;
        t=gcd(c,d);
        c/=t;
        d/=t;
        i=lcm(a,c);
        j=gcd(b,d);
        t=gcd(i,j);
        i/=t;
        j/=t;
        if(j==1)
            printf("%lld\n",i);
        else
            printf("%lld/%lld\n",i,j);
    }
    return 0;
}
