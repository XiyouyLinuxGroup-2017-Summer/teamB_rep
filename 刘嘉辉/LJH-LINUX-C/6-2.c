/*************************************************************************
	> File Name: 6-2.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月18日 星期二 20时34分03秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h> //系统值调用
#include<sys/stat.h> //函数都是获取文件（普通文件，目录，管道，socket，字符，块（）的属性。
#include<fcntl.h>   //给文件枷锁  ，改变权限
#include<errno.h>    //从错误代码获取相应错误，
#include<unistd.h> //系统函数调用
#include<string.h>  //strerrr要用到
int main ( int argc ,char ** argv[] ) {
    int fd;
    if ((fd = open ("example_6_2.c" , O_CREAT | O_EXCL, S_IRUSR | S_IWUSR) | S_IRGRP) == -1) {
     // if ((fd = creat("example_6_2.c",S_IRWXU) ) == -1 )     //S_IRWXU 用户可读写执行
   //     perror("open");
        printf("open : %s   with errno:%d\n",strerror(errno),errno);//a通过标准错误的标号，获得错误的描述字符串 ，将单纯的错误标号转为字符串描述，方便用户查找错误。
        exit(1);
    }
    else printf ("creat file success\n");
    close(fd);
    return  0;
    
}
