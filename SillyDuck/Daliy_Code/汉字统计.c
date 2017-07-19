/*************************************************************************
	> File Name: 5.c
	> Author:hxllhhy
	> Mail:hxllhhy@gmail.com
	> Created Time: 2017年07月19日 星期三 09时32分31秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
int main()
{
    int n,i,count;
    char s[1000];
    scanf("%d",&n);
    getchar();
    while(n--)
    {
        gets(s);
        count=0;
        for(i=0;i<strlen(s);i++)
        {
            if(s[i]<0||s[i]>255)
                count++;
        }
        printf("%d\n",count/2);

    }
    return 0;
}
