/*************************************************************************
	> File Name: pipe.c
	> Author:九五二七 
	> Mail: 
	> Created Time: 2017年08月04日 星期五 10时22分30秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>

//读管道　
void readpipe(int fd )
{
    char str[100];
    read (fd ,str, 100);
    printf("read from pipe: %s\n",str);
}
//写管道
void writepipe(int fd )
{
    char *str = "HELLO  高糕糕!\n";
    write(fd, str, strlen(str)+1);

}
int main (){
    int fd[2] ;
    pid_t pid;
    int  stat_val;

    if(pipe (fd)){
        printf("create  pipe  failed\n");
        exit(0);
    }
    
    pid = fork ();
    switch (pid )
    {
        case  -1:
            printf(" fork  failed\n ");
            exit(1);
/*管道通信是原子操作，为保证读或写的原子性　（操作过程中不能被打断　，必须一次性操作完全　）　 */
        //所以每步操作前　需关闭行对应的端口
        case  0 :
            //子进程关闭写端
            close (fd[1]);//
            readpipe(fd[0]);
                   
            exit(0);
        default:
            //    
            close (fd[0]);
            writepipe(fd[1]);
            wait (&stat_val);
            exit(0);
    }
    return 0; 

}
