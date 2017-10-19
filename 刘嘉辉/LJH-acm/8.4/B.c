/*************************************************************************
	> File Name: B.c
	> Author:九五二七 
	> Mail: 
	> Created Time: 2017年08月07日 星期一 14时25分24秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
int main ()
{
    int i,n,len ;
    float sum,temp;
    char str [100];
    scanf("%d",&n);
    while(n--)
    {
        sum = 0;
        scanf("%s",str);
        len = strlen (str) ;
        for (i=0; i<len ;i++)
        {
            if(str[i] <= '0' || str[i] >= '9' )
            {
                switch (str[i])
                {
                    case 'C' : temp = 12.01 ;break;
                    case 'H' : temp = 1.008 ;break;
                    case 'O' : temp = 16.00 ;break; 
                    case 'N' : temp = 14.01 ;break;
                }    
                if (str [i+1]>='0' && str [i+1]<='9' ){
                    if (str [i+2]>='0' && str [i+2]<='9')
                        sum += temp*(( str[i+1]-'0')*10 +str[i+2]-'0');
                    else 
                        sum += temp*(str[i+1]-'0');
                }
                else 
                    sum += temp;
            }
            
        }
        printf("%.3f\n",sum);
    }



}
