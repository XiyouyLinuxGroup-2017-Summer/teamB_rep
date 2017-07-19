/*************************************************************************
	> File Name: loop_queue.c
	> Author: Linuxer_liu
	> Mail: 
	> Created Time: 2017年07月19日 星期三 10时09分52秒
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#define MAX 10
#define TRUE 0
#define FALSE -1
typedef struct {
    int data[MAX];
    int rear,front ;
    int num ;
}loop_queue ;
int InQueue(loop_queue *sq ,int x)
{
    if(sq->num == MAX )
    {
        printf("the queue if full !!\n");
        return FALSE ;
    }
    sq->rear = (sq->rear + 1)% MAX ;
    sq->data[sq->rear]= x;
    sq->num++ ;
    return TRUE;
}
int  OutQueue(loop_queue *sq)
{
    if(sq->num == 0)
    {
        printf("the queue is empty !!\n");
        return FALSE ;
    }
    sq->front =(sq->front + 1)% MAX ;
    sq->num--;
    return (sq->data[sq->front]);
}
int look_queue(loop_queue *sq)
{
    int temp;
    if(sq->num == 0)
    {
        printf("the queue is empty !!\n");
        return FALSE ;
    }
    temp=(sq->front + 1)% MAX ;
    return (sq->data[temp]);
}
int main(void){
    loop_queue *sq ;
    sq=(loop_queue *)malloc(sizeof(loop_queue));
    sq->rear = sq->front = MAX - 1 ;
    sq->num = 0 ;

    InQueue(sq,44);
    InQueue(sq,55);
    InQueue(sq,66);
    InQueue(sq,77);
    InQueue(sq,88);
    printf("----------------%5d\n",OutQueue(sq));//44
    printf("----------------%5d\n",OutQueue(sq));//55
    printf("now the wueue's front yuansu is %5d\n",look_queue(sq));//66

    printf("----------------%5d\n",OutQueue(sq));//66
    printf("now the wueue's front yuansu is %5d\n",look_queue(sq));//77
    printf("----------------%5d\n",OutQueue(sq));//77
}

