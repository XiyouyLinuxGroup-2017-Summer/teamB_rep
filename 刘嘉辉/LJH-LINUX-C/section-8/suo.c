
/*下面给个测试小程序进一步了解互斥，mutex互斥信号量锁住的不是一个变量，而是阻塞住一段程序。
 * 如果对一个mutex变量testlock, 执行了第一次pthread_mutex_lock(testlock)之后，在unlock(testlock)之前的这段时间内
如果有其他线程也执行到了pthread_mutex_lock(testlock)，这个线程就会阻塞住，直到之前的线程unlock之后才能执行
，由此，实现同步，也就达到保护临界区资源的目的。
* */


#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

static pthread_mutex_t testlock;
pthread_t test_thread;

void *test()
{
pthread_mutex_lock(&testlock);  //会发生阻塞
printf("thread Test() \n");
pthread_mutex_unlock(&testlock);
}

int main()
{
pthread_mutex_init(&testlock, NULL);
pthread_mutex_lock(&testlock); //这个先执行

printf("Main lock \n");

pthread_create(&test_thread, NULL, test, NULL);
sleep(1); //更加明显的观察到是否执行了创建线程的互斥锁
printf("Main unlock \n");
pthread_mutex_unlock(&testlock); //解锁之后 ， void × test才能执行

sleep(1);
pthread_join(test_thread,NULL);   //等待线称结束 
pthread_mutex_destroy(&testlock); 	//释放锁所占用的资源
return 0;
}
