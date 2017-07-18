/*************************************************************************
	> File Name: p79.c
	> Author:hxllhhy
	> Mail:hxllhhy@gmail.com
	> Created Time: 2017年07月18日 星期二 17时08分40秒
 ************************************************************************/

#include<stdio.h>

int get_big(int i,int j)  //获取较大者
{
    return i>j?i:j;
}

int (*get_function(int a))(int,int)  //返回函数指针的函数
//get_function先与()结合，get_function(int a)是一个含有整型参数的函数。总的来看，int (*)(int,int)是一个函数指针，返回的是一个指向函数的指针，指针指向的函数有两个整型参数。
{
    printf("the number is %d\n",a);

    return get_big;  
    //get_big作函数的返回值，它是函数名，也是函数的入口地址，是一个指针
}

int main()
{
    int i=5,j=10,max;

    int (*p)(int,int);
    p=get_function(100); //函数返回值是指向函数的指针，赋给p

    max=p(i,j); //通过p调用get_big函数，返回值赋给max
    printf("The MAX is %d\n",max);

    return 0;
}
