/*************************************************************************
	> File Name: 字符串的周期.c
	> Author:hxllhhy
	> Mail:hxllhhy@gmail.com
	> Created Time: 2017年08月04日 星期五 10时37分51秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
int main()
{
    int i,j,l,n;
    int flag=0;
    char s[100];
    while(scanf("%d",&n)!=EOF)
    {
        while(n--)
        {
            scanf("%s",s);
            l=strlen(s);
            for(i=1;i<=l;i++)
            {
                if(l%i==0)
                {
                    flag=1;
                    for(j=i;j<l;j++)
                    {
                        if(s[j]!=s[j%i])
                        {
                            flag=0;
                            break;
                        }
                    }
                }
                if(flag)
                    break;
            }
            if(n>=1)
                printf("%d\n\n",i);
            else
                printf("%d\n",i);
        }
    }
    return 0;
}
