/*************************************************************************
	> File Name: daemon.c
	> Author:九五二七 
	> Mail: 
	> Created Time: 2017年07月24日 星期一 22时32分14秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<signal.h>
#include<sys/param.h>
#include<time.h>
#include<syslog.h>
#include<stdlib.h>
#include<sys/stat.h>

int init_daemon(void)
{
    int pid;
    int i;

    /*忽略终端　I/O信号，STOP信号*/
    signal(SIGTTOU,SIG_IGN);
    signal(SIGTTIN,SIG_IGN);
    signal(SIGTSTP,SIG_IGN);
    signal(SIGHUP,SIG_IGN);
    
    pid = fork();
    if(pid > 0)
    {
        exit(0);    /*结束父进程，使得子进程成为后台进程*/   
    }
    else if(pid < 0)
    {
        return -1;
    }
    /*建立一个新的进程组，在这个新的进程组中，子进程成为这个进程组的首进程，以使该进程脱离所有进程*/
    pid = fork();
    if( pid  > 0 ) {
        exit(0);
    }
    else if  (pid <0)
    {
        return -1;
    }
    /**/
    for (i=0; i <NOFILE ; close(i++));

    chdir("/");

    umask(0);

    signal(SIGCHLD,SIG_IGN);

    return  0;


}

int  main ()
{
    time_t now;
    init_daemon();
    syslog(LOG_USER|LOG_INFO,"测试守护进程");
    while(1){
        sleep(0);
        time(&now);
        syslog(LOG_USER|LOG_INFO,"\t%s\t\t\n",ctime(&now));
    }
    

}
