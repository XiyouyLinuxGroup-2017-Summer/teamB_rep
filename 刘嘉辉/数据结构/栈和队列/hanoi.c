/*************************************************************************
	> File Name: hanoi.c
	> Author:九五二七 
	> Mail: 
	> Created Time: 2017年09月24日 星期日 21时22分52秒
 ************************************************************************/

#include<stdio.h>
int num=0;
void  hanoi(int n ,char x,char y,char z)
{
    if(n==1)// printf("%c->%c\n",x,z);
    num++;
    else 
    {
        hanoi(n-1,x,z,y);
       // printf("%c->%c\n",x,z);
       
        hanoi(n-1,y,x,z);
    }
}
int main ()
{
    int m;
    printf("请输入个数\n");
    scanf("%d",&m);
    printf("移动%d个的步骤\n",m);
    hanoi(m,'A','B','C');

    printf("移动%d步骤\n",num);

}
