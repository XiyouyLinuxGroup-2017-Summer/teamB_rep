/*************************************************************************
	> File Name: jointhread.c
	> Author:hxllhhy
	> Mail:hxllhhy@gmail.com
	> Created Time: 2017年08月01日 星期二 17时21分46秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

void assisthread(void *arg)
{
    printf("I am helping to do some job\n");
    sleep(3);
    pthread_exit(0);
}

int main()
{
    pthread_t assistthid;
    int status;

    pthread_create(&assistthid,NULL,(void *)assisthread,NULL);
    pthread_join(assistthid,(void *)&status);
    printf("assisthread's exit is caused %d\n",status);

    return 0;
}
