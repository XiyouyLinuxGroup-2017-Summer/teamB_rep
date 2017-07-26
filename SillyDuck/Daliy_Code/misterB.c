/*************************************************************************
	> File Name: misterB.c
	> Author:hxllhhy
	> Mail:hxllhhy@gmail.com
	> Created Time: 2017年07月22日 星期六 10时42分49秒
 ************************************************************************/

#include<stdio.h>
int main()
{
    int c,v0,v1,a,l,day,sum,count;
    while(scanf("%d %d %d %d %d",&c,&v0,&v1,&a,&l)!=EOF)
    {
        day=0;
        if(v0>=c)
            day=1;
        else
        {
            day++;   //第二天开始
            sum=v0;
            while(sum<c)
            {  
                count=v0+day*a;  //每天读的页数
                if(count>v1)     //判断
                    count=v1;    //超过就v1
                sum+=count-l;    //减去重读页数
                day++;           //天数自增
            }
        }
        printf("%d\n",day);
    }
    return 0;
}

//坑点：每天的阅读量与最大阅读量比较的时候，重读页数是不包括在内的。。
//所以先判断，在减去重读页数
