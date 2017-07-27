/*************************************************************************
	> File Name: fork3.c
	> Author:九五二七 
	> Mail: 
	> Created Time: 2017年07月25日 星期二 09时49分41秒
 ************************************************************************/

#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

int  main(void)
{
    pid_t  pid;   //宏定义 定义在<sys/types.h>之中

            int  i = 4;
    pid = fork();
    
    switch (pid) {
        case 0 :
            while(i--)
            {
                printf("A  background  process ,PID: %d\n, ParentID: %d\n",getpid(),getppid() ) ;   
                sleep(3);
            }
            exit(0);
        case -1:
            perror ("process craetion faild \n");
            exit(-1);
        default:  //返回子进程进程号
            printf("I am parent process ,my pid  is  %d\n",getpid() );
            exit(-1); //会使父进程退出 
    }
return 0;
}
