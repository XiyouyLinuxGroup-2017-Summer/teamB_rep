/*************************************************************************
	> File Name: jtlb.c
	> Author:九五二七 
	> Mail: 
	> Created Time: 2017年09月21日 星期四 14时35分32秒
 ************************************************************************/

#include<stdio.h>
#define   MAXSIZE 1000
typedef  struct 
{
    int  num;
    int  cur;//游标（cursor）
}component,staticlinklist [MAXSIZE];
status  initlist(staticlinklist space)
