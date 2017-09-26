/*************************************************************************
	> File Name: lian-stack.c
	> Author:九五二七 
	> Mail: 
	> Created Time: 2017年09月25日 星期一 12时10分39秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
typedef  struct  NODE {
    int  num;
    struct NODE *next;
}NODE;
//入栈操作
//栈空判断
int  isempty(NODE *top);
int  pushLstack(NODE *top)
{
    
    NODE *pnew;
    pnew = (NODE *)malloc (sizeof(NODE));
    printf("请输入数据\n");
    scanf("%d",&pnew->num);
    pnew->next= top->next;
    top->next = pnew;
   
}
//出栈操作
int  popLstack(NODE *top)
{
    int  b;
    NODE *pdel;
    b = isempty(top);
    if (b) {
        pdel =top->next;
        top->next = pdel->next;
        printf("出栈元素为%d\n",pdel->num);
        free(pdel);
       
    }
    else  
        printf("栈空不能操作\n");
}
//栈空判断
int  isempty(NODE *top)
{
    if(top->next == NULL) return 0;
    else  return  1;
}
void  printstack(NODE *top)
{
    NODE *pnew;
    pnew = top->next;
    while(pnew!=NULL){
        printf("数据为%d\n",pnew->num);
        pnew= pnew ->next;

    }

}
int  main ()
{
    NODE *top;
    int a=0;
    top = (NODE*) malloc (sizeof(NODE));
    top->num = 0;
    top->next = NULL;

    while(1){
        printf("请选择你要的操作\n");
        printf("1: 入栈数据\n");
        printf("2: 出栈数据\n");
        printf("3: 打印数据\n");
        scanf("%d",&a);
        switch(a){
            case 1:
                pushLstack(top);
                break;
            case 2:
                popLstack(top);
                break;
            case 3:
                printstack(top);
                break;
        }
    }
}
