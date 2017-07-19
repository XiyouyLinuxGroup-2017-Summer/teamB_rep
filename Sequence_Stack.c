/*************************************************************************
	> File Name: Sequence_Stack.c
	> Author: Linuxer_liu
	> Mail: 
	> Created Time: 2017年07月17日 星期一 17时13分53秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

#define MAXNUM  30
#define FALSE -1
#define TRUE  0

typedef  struct    //data structure of stack
{
    int stack[MAXNUM];
    int lefttop ;
    int righttop ;
}share_stack;

int init_stack(share_stack **s)    //init  the  stack 
{
    *s=(share_stack *)malloc(sizeof(share_stack));
    if( *s ==  NULL)
        return FALSE ;
    (*s)->lefttop=  -1;
    (*s)->righttop=MAXNUM ;
    return TRUE ;
}

int push_stack(share_stack *s,char status ,int x )   //push x
{ 
    if(s->lefttop+ 1== s->righttop)      //sure the stack is or not empty
    {
        printf("the stack is full !!\n");
        return FALSE;
    }
    if(status == 'L')        s->stack[++s->lefttop]= x ;        //frist ++
    else if(status == 'R')   s->stack[--s->righttop]= x ;    //frist --
    else  //the parameter wrong 
    {
        printf("parameter is wrong !! \n");
        return FALSE ;
    }
    return TRUE;
}

int pop_stack(share_stack *s ,char status)  //pop a element 
{
    if(status == 'L')
    {
        if(s->lefttop == -1)
        {
            printf("the left strack is empty !!\n");
            return FALSE;
        }
        else return (s->stack[s->lefttop--]);
    }
    else if(status == 'R')
    {
        if(s->righttop == MAXNUM)
        {
            printf("the right strack is empty !!\n");
            return FALSE;
        }
        else return (s->stack[s->righttop++]);
    }
    else return TRUE ;
}

int main(void)
{
    share_stack *s ;
    init_stack(&s);
    push_stack(s,'L',10);
    push_stack(s,'L',9);
    push_stack(s,'L',8);
    push_stack(s,'L',7);
    push_stack(s,'L',6);

    printf("1======%d\n",pop_stack(s,'L')); //6 
    printf("2======%d\n",pop_stack(s,'L'));//7
    printf("1======%d\n",pop_stack(s,'L')); //8 

    push_stack(s,'R',1);
    push_stack(s,'R',2);
    push_stack(s,'R',3);
    push_stack(s,'R',4);
    push_stack(s,'R',5);

    printf("3======%d\n",pop_stack(s,'R')); //5
    printf("4======%d\n",pop_stack(s,'R')); //4 
}
