/*************************************************************************
	> File Name: tsd.c
	> Author:hxllhhy
	> Mail:hxllhhy@gmail.com
	> Created Time: 2017年08月01日 星期二 21时02分56秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

pthread_key_t key;
void *thread2(void *arg)
{
    int tsd=5;
    printf("thread %lu is running\n",pthread_self());
    pthread_setspecific(key,(void *)tsd);
    printf("thread %lu returns %lu\n",pthread_self(),pthread_getspecific(key));
}

void *thread1(void *arg)
{
    int tsd=0;
    pthread_t thid2;

    printf("thread %lu is running\n",pthread_self());
    pthread_setspecific(key,(void *)tsd);
    pthread_create(&thid2,NULL,thread2,NULL);
    sleep(5);
    //sleep(1);
    printf("thread %lu returns %lu\n",pthread_self(),pthread_getspecific(key));
}

int main()
{
    pthread_t thid1;
    printf("main thread begins running\n");
    pthread_key_create(&key,NULL);
    pthread_create(&thid1,NULL,thread1,NULL);
    sleep(3);
    //usleep(10);
    pthread_key_delete(key);
    printf("main thread exit\n");
    return 0;
}
