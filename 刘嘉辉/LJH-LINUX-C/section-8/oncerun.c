/***********************************************************************
> File Name: oncerun.c
> Author:九五二七 
> Mail: 
> Created Time: 2017年08月01日 星期二 09时26分10秒
************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>

pthread_once_t once = PTHREAD_ONCE_INIT; //初始化为0

void run(void)
{
    printf("Fuction run  id running in  thread %lu\n",pthread_self());
}

void * thread1(void *arg)
{
    pthread_t thid= pthread_self();
    printf("Current  t新出现爱你想你的策划过read 's ID is %lu\n",thid );
    
 //   pthread_once(&once, run);//确保线程只创建一次    用过之后立马为2
    printf("thread1i ends\n");
}
//avoid * thread2(void *arg)
void  pp()
{
   
   /* pthread_t thid= pthread_self();
    printf("Current  thread 's ID is %lu\n",thid );
   pthread_once(&once, run);
    printf("thread2 ends\n");*/
    printf("Fuction二函数 run  id running in  thread %lu\n",pthread_self());
}
int main ()
{
printf("once= %d\n",once);
    pthread_t thid1,thid2;

    printf("Fuction run 主线程飞  id running in  thread %lu\n",pthread_self());
    pthread_create(&thid1,NULL,thread1,NULL);
   // pthread_create(&thid2,NULL,thread2,NULL);
   run();
    pp();
    sleep(3);
    printf("main thread exit !\n");
    exit(0);

}
