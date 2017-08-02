/*************************************************************************
	> File Name: exec.c
	> Author:九五二七 
	> Mail: 
	> Created Time: 2017年07月25日 星期二 14时28分38秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc , char ** argv , char **environ)
{
    pid_t pid;
    int  stat_val;   //有什么用？？？
    printf("Exec example\n");
    pid = fork();
    switch (pid) {
        case -1 :
            perror("Process  Creation Failed\n");
            exit(1);
        case 0:
            printf("Child process is  running\n");
            printf("My pid = %d, parentpid = %d \n",getpid(),getppid());
            printf("uid = %d,gid = %d \n ",getuid(),getgid());
            execve("processimage", argv, environ);  //第一个参数为另一个可执行文件　作用为调用函数　传进环境变量　　执行这个程序
            printf("Process never is runing here\n");
        default:
            printf("parent process is running %d \n",pid);
            break;
    }
    wait(&stat_val);
    exit(0);
}
