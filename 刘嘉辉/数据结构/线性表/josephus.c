/*************************************************************************
	> File Name: josephus.c
	> Author:九五二七 
	> Mail: 
	> Created Time: 2017年09月21日 星期四 15时30分28秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
typedef struct NODE
{
    int  id;
    int  passwd;
    struct NODE *next;
}NODE;
//循环链表的创建
void creat(NODE *head,int n);
//打印循环链表
void print(NODE *head);
//判断链表否为空
int  isempty(NODE  *head);
//运行约瑟夫环问题
void josephusoperate(NODE *head,int m);
int main ()
{
    int  m=0,n=0;
    NODE *head;
    head = (NODE *)malloc (sizeof(NODE ));
    printf("请输入初始密码\n");
    scanf("%d",&m);
    
    printf("请输入人数:");
    scanf("%d",&n);

    printf("请输入密码");
    scanf("%d",&head->passwd);
    head->id = 1;
    creat (head,n);
    print(head);
    josephusoperate(head,m);
}
void creat(NODE *head,int n)
{
    int  i;
    NODE  *pnew,*pend;
    pend = head;
    for  (i=2;i<=n;i++){
        pnew  = (NODE *)malloc (sizeof(NODE));
        pend->next = pnew;    //这个坑已经踩了几次了不敢再犯了  试想pnew->next后是什么都毛有的 
        printf("请输入密码");
        scanf("%d",& pnew->passwd);    
        pnew ->id = i;           
        pend = pnew ;
    }
    pend->next = head;
}


void print(NODE *head)
{
    NODE *pnew;
    pnew = head;
    while (pnew != head ){
        printf("id---%d,passwd---%d\n",pnew->id,pnew->passwd); 
        pnew = pnew->next;      
    }
}

void josephusoperate(NODE *head,int m)
{
    int flag=1,i=1;
    NODE *pcur=NULL,*pdel=NULL,*ptr=NULL;
    pcur = head;
    while (flag){
        if(ptr == pcur) break;
        for (i=1;i< m;i++)
        {
            ptr = pcur;
            pcur = pcur->next;
        }
        pdel = pcur;
        printf("第%d个人出列(密码:%d)\n ",pdel->id,pdel->passwd);
        m = pdel->passwd;
        pcur = pcur->next;
        ptr->next = pcur;
        free(pdel);
    }
    
    printf("第%d个人出列(密码:%d)\n ",ptr->id,ptr->passwd);
}









