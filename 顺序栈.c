#include<stdio.h>
#include<stdlib.h>
#define MAX  30
#define FALSE -1
#define TRUE  0
typedef  struct    //data structure of stack
{
    int data[MAX];
    int top ;
}stack;
int init_stack(stack **s)    //init  the  stack 
{
    *s=(stack *)malloc(sizeof(stack));
    if( *s ==  NULL)
        return FALSE ;
    (*s)->top=  -1;
    return TRUE ;
}
int push_stack(stack *s ,int x )   //push x
{ 
    if(s->top == MAX - 1 )      //sure the stack is or not full 
    {
        printf("the stack is full !!\n");
        return FALSE;
    }
    s->data[++s->top]= x ;    //frist --
    return TRUE;
}
int pop_stack(stack *s )  //pop a element ,return the element's itself 
{
        if(s->top == -1)
        {
            printf("the strack is empty !!\n");
            return FALSE;
        }
        else return (s->data[s->top--]);
}
int main(void)
{
    stack *s ;
    init_stack(&s);
    push_stack(s,8);
    push_stack(s,7);
    push_stack(s,6);
    printf("======%5d\n",pop_stack(s)); //6 
    printf("======%5d\n",pop_stack(s));//7
    printf("======%5d\n",pop_stack(s)); //8 
    push_stack(s,1);
    push_stack(s,2);
    push_stack(s,3);
    printf("======%5d\n",pop_stack(s)); //3
    printf("======%5d\n",pop_stack(s)); //2 
    printf("======%5d\n",pop_stack(s)); //1
    printf("======%5d\n",pop_stack(s)); //error ,the stack is empty !! 
}
