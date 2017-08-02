/*************************************************************************
	> File Name: createthread.c
	> Author:hxllhhy
	> Mail:hxllhhy@gmail.com
	> Created Time: 2017年08月01日 星期二 16时45分17秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

int *thread(void *arg)  //线程函数
{
    pthread_t newthid; //新线程

    newthid=pthread_self();  //获取新线程id
    printf("this is a new thread,thread ID = %lu\n",newthid);
    return NULL;
}

int main(void)
{
    pthread_t thid;  //主线程

    printf("main thread ID is %lu\n",pthread_self());  //打印主线程ID
    if(pthread_create(&thid,NULL,(void *)thread,NULL)!=0)  //创建新线程
    {
        printf("thread creation failed\n");  //创建线程失败
        exit(1); 
    }
    sleep(1);
    exit(0);
}

//pthread_create函数的第三个参数是函数指针，指向创建后要调用的函数
//线程创建成功后，新创建的线程开始运行第三个参数所指向的函数，原来的线程继续运行
