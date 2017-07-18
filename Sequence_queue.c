/*************************************************************************
	> File Name: Sequence_queue.c
	> Author: Linuxer_liu
	> Mail: 
	> Created Time: 2017年07月18日 星期二 20时43分47秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#define TRUE 0
#define FALSE  -1
#define  MAX  10
typedef struct {
    int data[MAX];
    int rear,front;    //rear  尾   front  头 
}Queue ;


int InQueue( Queue *q , int x ) //sure the queue is or not full 
{
    int m;
    m=q->rear - q->front ;
    if(m  ==  MAX ) 
    {
        printf("the queue is full !!\n");
        return FALSE ;
    }
    q->data[++q->rear]= x ;
    return TRUE ;
}


int OutQueue(Queue *q )  //返回出队列的元素,判空队
{
    int m;
    m=q->rear - q->front ;
    if(m ==  0 )
    {
        printf("the queue is empty !!\n");
        return FALSE ;
    }
    return (q->data[++q->front]); 
}

int look_queue(Queue *q )
{
    int m;
    int temp ;
    m=q->rear - q->front ;
    if(m ==  0 )
    {
        printf("the queue is empty !!\n");
        return FALSE ;
    }
    temp = q->front + 1 ;
    return (q->data[temp]);
}

int main(void)
{
    Queue *q ;
    q=(Queue *)malloc(sizeof(Queue));  //init the queue
    q->rear=q->front =   -1;
    InQueue(q,4);
    InQueue(q,5);
    InQueue(q,6);
    InQueue(q,7);
    InQueue(q,8);
    printf("frist out is %d\n",OutQueue(q)); //4
    printf("second out is %d\n",OutQueue(q));//5
    printf("now the frist queue's yuansu is %d \n",look_queue(q)); //6
    printf("thrid  queue's yuansu is %d \n",OutQueue(q)); //6 
    printf("thrid  queue's yuansu is %d \n",OutQueue(q)); //7 
    printf("thrid  queue's yuansu is %d \n",OutQueue(q)); //8 
    printf("thrid  queue's yuansu is %d \n",OutQueue(q)); // 
}
