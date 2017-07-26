/*************************************************************************
	> File Name: Bulbasau.c
	> Author:hxllhhy
	> Mail:hxllhhy@gmail.com
	> Created Time: 2017年07月24日 星期一 14时53分11秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    char s[110000];
    int i,min,l;
    while(scanf("%s",s)!=EOF)
    {
        l=strlen(s);
        int a[7]={0};
        for(i=0;i<l;i++)
        {
            if(s[i]=='B') a[0]++;
            if(s[i]=='u') a[1]++;
            if(s[i]=='l') a[2]++;
            if(s[i]=='b') a[3]++;
            if(s[i]=='a') a[4]++;
            if(s[i]=='s') a[5]++;
            if(s[i]=='r') a[6]++;
        }
        a[1]/=2;a[4]/=2;
        min=a[0];
        for(i=1;i<=6;i++)
        {
            if(a[i]<min)
                min=a[i];
        }
        printf("%d\n",min);
    }
    return 0;
}
