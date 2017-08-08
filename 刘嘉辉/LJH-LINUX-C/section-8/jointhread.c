/*************************************************************************
	> File Name: jointhread.c
	> Author:九五二七 
	> Mail: 
	> Created Time: 2017年08月01日 星期二 15时55分29秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

void  assisthraed(void *arg)
{
    printf("I am ``````\n");
    //sleep (3);
    pthread_exit (10);

}

int main ()
{
    pthread_t  assisthid;
    int  status;
    pthread_create (&assisthid, NULL, (void * ) assisthraed, NULL);
    pthread_join (assisthid,(void *) &status);
    printf(" assisthraed's  exit is  caused %d\n ",status);

    return 0;
}
