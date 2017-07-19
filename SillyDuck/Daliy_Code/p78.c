/*************************************************************************
	> File Name: p78.c
	> Author:hxllhhy
	> Mail:hxllhhy@gmail.com
	> Created Time: 2017年07月18日 星期二 16时56分12秒
 ************************************************************************/

#include<stdio.h>

int get_big(int i,int j) //获得较大者
{
    return i>j?i:j;
}

int get_max(int i,int j,int k,int (*p)(int,int)) //获取三个数中的最大者
{
    int ret;

    ret=p(i,j);
    ret=p(ret,k);

    return ret;
}

int main()
{
    int i=5,j=10,k=15,ret;

    ret=get_max(i,j,k,get_big); //函数名作参数
    printf("The MAX is %d\n",ret);

    return 0;
}


