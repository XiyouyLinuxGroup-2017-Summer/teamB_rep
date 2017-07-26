/*************************************************************************
	> File Name: 手机短号.c
	> Author:hxllhhy
	> Mail:hxllhhy@gmail.com
	> Created Time: 2017年07月22日 星期六 10时03分51秒
 ************************************************************************/

#include<stdio.h>
int main()
{
    int i,n;
    char s[12];
    scanf("%d",&n);
    while(n--)
    {
        scanf("%s",s);
        printf("6");
        for(i=6;i<11;i++)
            printf("%c",s[i]);
        printf("\n");
    }
    return 0;
}
