/*************************************************************************
	> File Name: ceshi.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月13日 星期四 13时56分30秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
char getch()
{
    char c;
    system("stty -echo");  //不回显
    system("stty -icanon");//设置一次性读完操作，如使用getchar()读操作，不需要按enter
    c=getchar();
    system("stty icanon");//取消上面的设置
    system("stty echo");//回显
    return c;

}

char getche()
{
    char c;
    system("stty -icanon");
    c=getchar();
    system("stty icanon");
    return c; 

}
int main () {
    char a;

    a=getch();
    if(a== '#')  printf("666");
    else printf("111");

    return 0;
}
