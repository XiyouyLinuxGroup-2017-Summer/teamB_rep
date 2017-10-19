/*************************************************************************
	> File Name: 括号配对.c
	> Author:九五二七 
	> Mail: 
	> Created Time: 2017年08月10日 星期四 16时54分12秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main ()
{
    int  n;
    int i,j,len;
    char  str[100];
    scanf("%d",&n);
    while(n--) {
        memset(str,0,sizeof(str));
        scanf("%s",str);
        len = strlen(str);
        if (len % 2 == 0){
            for  (i = 0; i<len ; i++)
            {
                    printf("%d",len);
                if (str[i] == '[' && str[i+1] == ']' )
                {
                    for(j=i;j<len ;j++)
                    {
                        str[j] = str[j+2];
                    }
                    len = len -2;
                    str[len] = '\0';
                    str[len+1] = '\0';
                    printf("%s",str);
    printf("===%d",strlen (str));
                    i=0;
                }
                if (str[i] == '(' && str[i+1] == ')' )
                {
                    for(j=i;j<len-2 ;j++)
                    {
                        str[j] = str[j+2];
                    }
                    len = len -2;
                    str[len] = '\0';
                    i=0;
                }
            }
        }    
        printf("%s",str);
    }



} 
