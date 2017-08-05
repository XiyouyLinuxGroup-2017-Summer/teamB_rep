/*************************************************************************
	> File Name: 6.c
	> Author: Linuxer_liu
	> Mail: 
	> Created Time: 2017年08月05日 星期六 09时45分35秒
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
double fun(double x ,double y)
{
    return pow(x,y);
}
