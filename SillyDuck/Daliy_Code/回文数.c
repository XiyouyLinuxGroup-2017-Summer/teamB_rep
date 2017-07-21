/*************************************************************************
	> File Name: 1.c
	> Author:hxllhhy
	> Mail:hxllhhy@gmail.com
	> Created Time: 2017年07月21日 星期五 09时09分41秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
int main()
{
    int i,l,n,count;
    char s[1000];
    scanf("%d",&n);
    while(n--)
    {
        scanf("%s",s);
        l=strlen(s);
        count=0;
        for(i=0;i<l/2;i++)
        {
            if(s[i]==s[l-i-1])
                count++;
        }
        if(count==l/2)
            printf("yes\n");
        else
            printf("no\n");
    }
    return 0;
}
