/*************************************************************************
	> File Name: 5.c
	> Author: Linuxer_liu
	> Mail: 
	> Created Time: 2017年08月05日 星期六 09时43分02秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<pthread.h>
#include<math.h>
double fun(double x,double y);
int main(void)
{
    double x,y ;
    printf("Please input the X and Y :");
    scanf("%lf%lf",&x,&y);
    printf("The result is %lf \n",fun(x,y));
    return 0;
}

