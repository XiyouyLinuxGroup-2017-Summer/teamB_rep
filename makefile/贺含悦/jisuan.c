/*************************************************************************
	> File Name: jisuan.c
	> Author:hxllhhy
	> Mail:hxllhhy@gmail.com
	> Created Time: 2017年08月05日 星期六 09时50分01秒
 ************************************************************************/

#include<math.h>
#include"jisuan.h"

void lifangsum()
{
    int i;
    int sum=0;
    for(i=1;i<=10;i++)
        sum+=pow(i,3);
    printf("从1到10的立方之和为%d\n",sum);
}

