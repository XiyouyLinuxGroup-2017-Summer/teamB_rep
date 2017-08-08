/*************************************************************************
	> File Name: createthread.c
	> Author:九五二七 
	> Mail: 
	> Created Time: 2017年07月31日 星期一 14时53分55秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

int* thread(void* vrg)
{
    pthread_t newthid;

    newthid = pthread_self();
    printf("this is a new pthread ,thread ID = %lu\n",newthid);
    return NULL;
}

int main ()
{
    pthread_t thid;
    printf("main thread, ID is %lu\n",pthread_self());
    if (pthread_create(&thid, NULL , (void *)thread, NULL ) != 0 ){
        printf("thread  creation failed \n");
        exit(1);
    }
    sleep(1);
    exit(0);
}
