/*************************************************************************
	> File Name: dual_pipe.c
	> Author:九五二七 
	> Mail:    全双工　双管道进程通信
	> Created Time: 2017年08月04日 星期五 11时02分44秒
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>


//子进程读写管道的函数
void child_pipe(int  readfd , int writefd)
{
    char *str = "from  child   666666\n";
    write (writefd, str, strlen (str) +1);

    char ptt[100];
    read (readfd , ptt, 100);
    printf("child_pipe  read from pipe : %s" , ptt);
    
}

//父进程读写管道的函数
void  parent_pipe(int  readfd , int  writefd )
{
    char *str = "from parent_999999 \n";
    write (writefd,str, strlen (str)+1);

    char btt[100] ;
    rad (readfd, btt, 100);
    printf("parent_ read from pipe : %s", btt);
}

int main ()
{
    int  pipe1[2],pipe2[2];
    pid_t  pid;
    int  stat_val;

   printf("  全双工　双管道进程通信\n\n");
    if (pipe(pipe1))
    {
        printf(",,,\n");
    }
    printf(" pip1  %d%d",pipe1[0],pipe1[1]);
    if (pipe(pipe2))
    {
        printf("...\n");
    }
    
    printf(" pip2  %d%d",pipe2[0],pipe2[1]);
    pid = fork ();

    switch (pid)
    {
        case -1:
            printf("fork error \n");
            exit(0);
        case 0 : 
            //子进程关闭pipe1的读端， 关闭pipe2的写端    
            close (pipe1[1]);
            close (pipe2[0]);
            child_pipe(pipe1[0],pipe2[1]);
            exit(0);
        default :
            //父进程关闭pipe1的写端， 关闭pipe2的读端    
            close (pipe1[0]);
            close (pipe2[1]);
            parent_pipe(pipe2[0],pipe1[1]);
            wait (&stat_val);
            exit(0);  
    
    }

}














