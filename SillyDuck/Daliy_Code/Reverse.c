/*************************************************************************
	> File Name: Reverse.c
	> Author:hxllhhy
	> Mail:hxllhhy@gmail.com
	> Created Time: 2017年07月20日 星期四 10时03分48秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
int main()
{
    int i,j,k,l,t,n;
    char s[1100];
    scanf("%d",&n);
    getchar();
    while(n--)
    {
        gets(s);
        l=strlen(s);
        for(i=l-1;i>=0;i--)
        {
            s[i+1]=s[i];
        }
        s[l+1]='\0';
        s[0]=' ';
        for(i=1;i<=l+1;i++)
        {
            if(s[i]==' ')
            {
                t=i;
                for(k=t-1;s[k]!=' ';k--)
                {
                    printf("%c",s[k]);
                }
                printf("%c",s[k]);
            }
            if(s[i]=='\0')
            {
                t=i;
                for(k=t-1;s[k]!=' ';k--)
                {
                    printf("%c",s[k]);
                }
            }
        }
        printf("\n");
    }
    return 0;
}
