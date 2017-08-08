/*************************************************************************
	> File Name: tsd.c
	> Author:九五二七 
	> Mail: 
	> Created Time: 2017年08月01日 星期二 21时32分02秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

pthread_key_t key;
void* thread2()
{
    int tsd = 5;
    printf("thid %d is running\n",pthread_self());
    
    pthread_setspecific (key, (void *) tsd);
    printf("thread %d returns %d \n",pthread_self(), pthread_getspecific(key));
}

void* thread1()
{
    int  tsd = 0;
    pthread_t thid2;

    printf("thid %d is running\n",pthread_self());
    pthread_setspecific (key, (void *) tsd);
    pthread_create (&thid2, NULL,thread2,NULL);
    sleep(5);
    printf("thread %d returns %d \n",pthread_self(), pthread_getspecific(key));
}

int main ()
{
    pthread_t  thid1;
    printf("main  pthread begins running\n");
    pthread_key_create (&key, NULL);
    pthread_create (&thid1, NULL,thread1, NULL);
    sleep (5);
    pthread_key_delete(key);
    printf("main thread exit\n");
    return  0;
}














