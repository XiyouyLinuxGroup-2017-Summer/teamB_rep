/*************************************************************************
	> File Name: wait.c
	> Author:九五二七 
	> Mail: 
	> Created Time: 2017年07月25日 星期二 15时18分28秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<stdlib.h>

int  main ()
{
    pid_t  pid;
    char  *msg;
    int  k;
    int  exit_code;

    printf("Study how  to get exit  code \n");
    pid = fork();
    switch(pid){
        case 0:
            msg = "Child process is runing\n";
            k = 5;
            exit_code = 37;
            break;
        case -1:
            perror ("process creation failed\n");
            exit(1);
        default:
            exit_code = 0;
            break;

    }

    if(pid != 0) {
        int  stat_val;
        pid_t pid ;
        int child_pid = wait(&stat_val);//返回终止运行的子进程的ｉｄ

        printf("Child  process has exited ,pid = %d\n",child_pid);
        if(WIFEXITED(stat_val))//判断是否正常返回  返回非零值
        {
            printf("Child exited with code %d\n",WEXITSTATUS(stat_val));
        }
        else//abort  异常退出   
            printf("Child exit abnormally\n");
    }
    else {
        while(k--)
        {
            puts(msg);
            sleep(1);
        }
    }
    exit (exit_code);
   // abort(); // 异常退出
}
