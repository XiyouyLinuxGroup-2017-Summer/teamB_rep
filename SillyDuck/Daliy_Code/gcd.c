/*************************************************************************
	> File Name: gcd.c
	> Author:hxllhhy
	> Mail:hxllhhy@gmail.com
	> Created Time: 2017年07月25日 星期二 14时08分57秒
 ************************************************************************/

#include<stdio.h>
int gcd(int m,int n)
{
    return n==0?m:gcd(n,m%n);
}
int main()
{
    int n,a,b,c,t;
    scanf("%d",&n);
    while(n--)
    {
        scanf("%d %d",&a,&b);
        if(b>a)
        {
            c=2*a;
            while(gcd(a,c)!=b)
            {
                c+=a;
            }
        }
        c=2*b;
        while(gcd(a,c)!=b)
        {
            c+=b;
        }
        printf("%d\n",c);
    }
    return 0;
}
