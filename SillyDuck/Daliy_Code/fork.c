/*************************************************************************
	> File Name: fork.c
	> Author:hxllhhy
	> Mail:hxllhhy@gmail.com
	> Created Time: 2017年07月24日 星期一 10时36分58秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

int main(void)
{
    pid_t pid;

    printf("Process Creation Study\n");
    pid=fork();
    switch(pid)
    {
        case 0:
            printf("Child process is running,CurPid is %d,ParenPid is %d\n",pid,getppid());
            break;
        case -1:
            perror("Process creation failed\n");
            break;
        default:
            printf("Parent process is running,ChildPid is %d,ParenPid is %d\n",pid,getppid());
            break;
    }
    exit(0);
}
