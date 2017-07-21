/*************************************************************************
	> File Name: my_create.c
	> Author:hxllhhy
	> Mail:hxllhhy@gmail.com
	> Created Time: 2017年07月18日 星期二 22时08分55秒
 ************************************************************************/

#include<stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main()
{
    int fd;
    
    if((fd=open("example_1.c",O_CREAT|O_EXCL,S_IRUSR|S_IWUSR))==-1)
    //if(creat("example_1.c",S_IRWXU)==-1)
    {
        perror("open");
        //printf("open:%s with errno:%d\n",strerror(errno),errno);
        exit(1);    
    }
    else
    {
        printf("create file success\n");        
    }
    close(fd);
        
    return 0;
}
