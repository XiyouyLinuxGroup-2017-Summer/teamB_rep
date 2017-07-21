/*************************************************************************
	> File Name: unlink_temp.c
	> Author:hxllhhy
	> Mail:hxllhhy@gmail.com
	> Created Time: 2017年07月20日 星期四 14时54分19秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
void my_err(const char *err_string,int line)
{
    fprintf(stderr,"line:%d ",__LINE__);
    perror("err_string");
    exit(1);
}

int main()
{
    int fd;
    char buf[32];

    if((fd=open("temp",O_RDWR|O_CREAT|O_TRUNC,S_IRWXU))<0)
    {
        my_err("open",__LINE__);
    }
    if(unlink("temp")<0)
    {
        my_err("unlink",__LINE__);
    }
    printf("file unlinked\n");

    if(write(fd,"temp",5)<0)
    {
        my_err("write",__LINE__);
    }
    if((lseek(fd,0,SEEK_SET))==-1)
    {
        my_err("lseek",__LINE__);
    }
    if(read(fd,buf,5)<0)
    {
        my_err("read",__LINE__);
    }
    printf("%s\n",buf);
    return 0;
}

//创建temp文件，调用unlink，之后对文件进行读写操作，程序在unlink之后如果出现崩溃，则在程序结束时，temp也不会留下
