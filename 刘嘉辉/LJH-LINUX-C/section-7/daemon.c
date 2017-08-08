/*************************************************************************
	> File Name: daemon.c
	> Author:九五二七 
	> Mail: 
	> Created Time: 2017年07月24日 星期一 22时32分14秒
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<syslog.h>
#include<sys/param.h>
#include<signal.h>

int init_daemon(void)
{
    int  pid;
    int  i;

    //忽略终端 信号，，
    signal(SIGTTOU,SIG_IGN);
    signal(SIGTTIN,SIG_IGN);
    signal(SIGTSTP,SIG_IGN);
    signal(SIGHUP,SIG_IGN);

    pid = fork();
    if(pid > 0) {
        exit(0); //结束父进程 使得子进程成为后台进程
    }
    else  if (pid  < 0) {
        return -1;
    }
    //建立一个新的进程组，在这个进程组中，子进程成为这个进程组的首进程，以使该进程脱离所有终端
    setsid();
    pid = fork();
    if (pid  >  0)
    {
        exit(0);
    }

    else if ( pid < 0 ){
        return 0;
    }

    //关闭所有从父进程继承来的不再需要的文件描述符
    for (i=0; i< NOFILE;close(i++) ) ; //NOFILE  为嘴杂打开文数　即２５６
    //改变工作目录　是的进程不与任何文件系统联系
    chdir ("/");
    //将文件屏蔽字设置为0;
    umask(0);
    //忽略SIGCHLD
    signal (SIGCHLD, SIG_IGN);

    return 0;
    
}


int main ()
{
    time_t  now;
    init_daemon();
    syslog(LOG_USER| LOG_INFO, "测试守护进程！\n");
    while(1) {
        sleep(8);
        time(&now);
        syslog(LOG_USER| LOG_INFO,"系统时间：\t%s\t\t\n",ctime(&now));
    }
}









