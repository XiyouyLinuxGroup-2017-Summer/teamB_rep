/*************************************************************************
	> File Name: 相对分子质量.c
	> Author:hxllhhy
	> Mail:hxllhhy@gmail.com
	> Created Time: 2017年08月04日 星期五 09时29分46秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
int main()
{
    int i,n;
    double letter,sum;
    char s[100];
    while(scanf("%d",&n)!=EOF)
    {
        while(n--)
        {
            scanf("%s",s);
            sum=0;
            for(i=0;i<strlen(s);i++)
            {
                if(s[i]=='C'||s[i]=='H'||s[i]=='O'||s[i]=='N')
                {
                    switch(s[i])
                    {
                        case 'C':letter=12.01;break;
                        case 'H':letter=1.008;break;
                        case 'O':letter=16.00;break;
                        case 'N':letter=14.01;break;
                    }

                    if(s[i+1]>='1'&&s[i+1]<='9') //字母后跟数字
                    {
                        if(s[i+2]>='1'&&s[i+2]<='9') //字母后两位是数字
                            sum+=letter*((s[i+1]-'0')*10+s[i+2]-'0');
                        else                        //字母后一位是数字
                            sum+=letter*(s[i+1]-'0');
                    }
                    else //字母后跟字母
                        sum+=letter*1.0;
                }
            }
            printf("%.3lf\n",sum);
        }
    }
    return 0;
}
