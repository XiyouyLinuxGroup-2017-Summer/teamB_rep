/*************************************************************************
	> File Name: 1.c
	> Author:九五二七 
	> Mail: 
	> Created Time: 2017年08月07日 星期一 22时13分29秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>

int main ()
{
    int  n,i,j,k;
    int count[1000],max,t;

    char str[1002][20];
    while(scanf("%d",&n), n) 
    {
        memset(str,0,20000);
        memset(count,0,1000);
        for (i=0;i<n;i++) 
        {
            scanf("%s",str[i]);
        }
        for (i=0;i<n;i++)
            for (j=i;j<n;j++)
            {
                if (strcmp(str[i],str[j])==0 )
                {
                    count[i]++;                    
                }
            }
        max =count[0];
        t=0;
        for (i=1;i<n;i++){
            if (max < count[i]){
                max = count[i];
                t= i;
            }    
        }                                 
        printf("%s\n",str[t]);
    }

