/*************************************************************************
	> File Name: linklist_queue.c
	> Author: Linuxer_liu
	> Mail: 
	> Created Time: 2017年07月19日 星期三 15时31分58秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

#define TRUE 0
#define FALSE -1

typedef struct node  {
    int  data;
    char str[21];
    struct node *next ;
}Queue  ;//the type of node 

typedef struct {
    Queue *front ;
    Queue *rear ;
}Link_queue ; //linklist queue  

int InQueue(Link_queue *p_link )
{
    Queue *p;
    p=(Queue *)malloc(sizeof(Queue));
    printf("please input the data : ");
    scanf("%d",&p->data);
    printf("please inout the string : ");
    scanf("%s",p->str);
    p->next =NULL;
    p_link->rear->next = p ;
    p_link->rear = p ;
    return TRUE ;
}
Queue * OutQueue(Link_queue *p_link) //返回出队列的节点
{
    Queue *p;
    if(p_link->front == p_link->rear) // front 始终指在最前面 
    {
        printf("the queue is empty !!!\n");
        return (Queue *)FALSE ;
    }
    else 
    {
        p=p_link->front->next ;
        p_link->front->next=p->next ;
    }
    if(p_link->front->next == NULL ) //一个元素时，需要修改尾指针 
        p_link->front = p_link->rear ;
    return p;   
}
int main(void)
{
    Link_queue *p_link;
    Queue *p_queue ;
    Queue *temp ;
    p_link=(Link_queue *)malloc(sizeof(Link_queue));
    p_queue=(Queue *)malloc(sizeof(Queue));
    p_queue->next = NULL;
    p_link->rear =p_link->front =p_queue ;
    InQueue(p_link);
    InQueue(p_link);
    InQueue(p_link);
    InQueue(p_link);
    temp=OutQueue(p_link);
    printf("--------------num== %d \n",temp->data);
    printf("--------------str== %s \n",temp->str);
}

