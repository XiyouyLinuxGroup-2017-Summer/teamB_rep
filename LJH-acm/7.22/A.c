/*************************************************************************
	> File Name: A.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月22日 星期六 15时33分11秒
 ************************************************************************/

#include<stdio.h>
int main () 
{
    int  n,i ;
    char str[20];
    scanf("%d",&n);
    getchar();
    while (n--) 
    {
        i=0;
        gets(str);
        printf("6");
        for (i=6;i<11;i++)
        printf("%c",str[i]);
        printf("\n");

    }
}
