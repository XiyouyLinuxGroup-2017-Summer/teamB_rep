/*************************************************************************
	> File Name: studyuid.c
	> Author:九五二七 
	> Mail: 
	> Created Time: 2017年07月25日 星期二 17时05分42秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<stdlib.h>

extern  int errno;

int main ()
{
    int fd;

    printf("uid study :\n");
    printf("Process's uid = %d,euid = %d\n",getuid(),geteuid());

    //strerror 函数获取指定错误码的提示
    if (fd = open("test.c",O_RDWR) == -1){      //可读可写
        printf("open fa_lure,error is %d: %s \n",errno, strerror(errno));
        exit(0);
    }
    else {
        printf("Open successfully!\n");
    }
    close(fd);
    exit(0);
}
