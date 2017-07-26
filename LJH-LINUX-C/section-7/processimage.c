/*************************************************************************
	> File Name: processimage.c
	> Author:九五二七 
	> Mail: 
	> Created Time: 2017年07月25日 星期二 11时22分45秒
 ************************************************************************/

#include<stdio.h>
#include<sys/stat.h>
#include<unistd.h>

int main(int argc,char **argv,char ** environ)  //main的完整形式　环境变量：包括主目录　终端类型　当前目录
{
    int i;

    printf("I am a process image!\n");
    printf("My pid = %d, parentpid = %d \n",getpid(),getppid());
    printf("uid = %d,gid = %d \n",getuid(),getgid());   

    for (i=0 ; i<argc; i++)
    {
        printf("argv[%d]: %s\n ",i, argv[i]);
    }
}
