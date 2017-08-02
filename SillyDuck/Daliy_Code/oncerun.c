/*************************************************************************
	> File Name: oncerun.c
	> Author:hxllhhy
	> Mail:hxllhhy@gmail.com
	> Created Time: 2017年08月01日 星期二 17时01分13秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

pthread_once_t once=PTHREAD_ONCE_INIT;

void run(void)
{
    printf("Function run is running in thread %lu\n",pthread_self());
}

void *thread1(void *arg)  //线程1
{
    pthread_t thid=pthread_self();
    printf("Current thread's ID is %lu\n",thid);
    pthread_once(&once,run);  //run运行
    printf("thread1 ends\n");
}

void *thread2(void *arg)  //线程2
{
    pthread_t thid=pthread_self();
    printf("Current thread's ID is %lu\n",thid);
    pthread_once(&once,run);  //run没有运行
    printf("thread2 ends\n");
}

int main()
{
    pthread_t thid1,thid2;

    pthread_create(&thid1,NULL,thread1,NULL);
    pthread_create(&thid2,NULL,thread2,NULL);
    sleep(3);
    printf("main thread exit !\n");
    exit(0);
}

//在某些情况下，函数执行次数要被限制为一次，就使用pthread_once函数
//从这个测式的运行结果可看出两个线程都运行了，但是其中的有一个线程调用了run，而另一个线程没有调用
