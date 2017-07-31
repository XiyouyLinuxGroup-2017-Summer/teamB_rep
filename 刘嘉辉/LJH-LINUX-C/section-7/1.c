/*************************************************************************
	> File Name: 1.c
	> Author:九五二七 
	> Mail: 
	> Created Time: 2017年07月27日 星期四 09时24分21秒
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include<unistd.h>
int main(int argc ,char **argv )
{
    pid_t  pid;
  //  char *song[3] = {NULL,"/home/holy666/音乐/CloudMusic/The Verve - Bitter Sweet Symphony.mp3"};
    printf("hello 网易云\n");
    pid = fork();
    
    switch(pid){
        case -1 :
            exit;
            break;
        case 0:
            system("/usr/bin/netease-cloud-music /home/holy666/音乐/CloudMusic/The Verve - Bitter Sweet Symphony.mp3");
           // execvp("/usr/bin/netease-cloud-music",song);
            sleep(10);
        default :
            printf("!!!!");
    }





    // exit(0);
}
