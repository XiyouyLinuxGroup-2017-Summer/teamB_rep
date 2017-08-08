/*************************************************************************
	> File Name: condition.c
	> Author:九五二七 
	> Mail: 
	> Created Time: 2017年08月02日 星期三 07时59分08秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
 
pthread_mutex_t mutex;    //静态
pthread_cond_t  cond;

void *thread1(void  *arg)
{
    pthread_cleanup_push ((void *) pthread_mutex_unlock, &mutex);   //pthread mutex  unlock 为指定函数 

    while (1){
        printf ("thread1 is running \n");
        pthread_mutex_unlock (&mutex);// 这个mutex主要是用来保证pthread_cond_wait的并发性   
        pthread_cond_wait (&cond , &mutex);// pthread_cond_wait会先解除之前的pthread_mutex_lock锁定的mtx，然后阻塞在等待对列里休眠，直到再次被唤醒（大多数情况下是等待的条件成立而被唤醒，唤醒后，该进程会先锁定先pthread_mutex_lock(&mtx);，再读取资源， 用这个流程是比较清楚的/*block-->unlock-->wait() return-->lock*/
        printf ("thread1 applied the condition\n ");
        pthread_mutex_unlock  (&mutex);
        sleep(4);
    }

    pthread_cleanup_pop(0);   //当执行到这一步时返回 push  释放指定资源
}

void *thread2(void  *arg)
{   
    while (1){
        printf ("thread2 is running \n");
        pthread_mutex_unlock (&mutex);
        pthread_cond_wait (&cond , &mutex);
        printf ("thread2 applied the condition\n ");
        pthread_mutex_unlock  (&mutex);
        sleep(1);
    }
}
int main(){
    
    pthread_t  tid1,tid2;
    printf("condition variable study !\n");
    pthread_mutex_init (&mutex, NULL);//锁的初始化
    pthread_cond_init (&cond , NULL); //条件变量的初始化 
    
    pthread_create (&tid1, NULL, (void *)thread1, NULL);//实践证明线程1与线程2无特定先后顺序 
    pthread_create (&tid2, NULL, (void *)thread2, NULL);

    do{
        pthread_cond_signal(&cond);  //  用于激活条件变量  并发出信号   由wait所指定的变量来接收
    } while (1);
   
    sleep(50);
    pthread_exit(0);

}

