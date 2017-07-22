/*************************************************************************
	> File Name: 小明A+B.c
	> Author:hxllhhy
	> Mail:hxllhhy@gmail.com
	> Created Time: 2017年07月22日 星期六 10时09分01秒
 ************************************************************************/

#include<stdio.h>
int xiaoming(int num)
{
    if(num>=100)
        return num%10+num/10%10*10;
    else
        return num;
}
int main()
{
    int n,a,b;
    scanf("%d",&n);
    while(n--)
    {
        scanf("%d %d",&a,&b);
        printf("%d\n",xiaoming(xiaoming(a)+xiaoming(b)));
    }
    return 0;
}
