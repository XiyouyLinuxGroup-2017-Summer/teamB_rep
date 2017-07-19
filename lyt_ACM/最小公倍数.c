/*************************************************************************
	> File Name: test.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月19日 星期三 10时13分29秒
 ************************************************************************/

#include<stdio.h>
int main()  
{  
    int n,i,j;  
    long long a[1000];  
    long long ji;  
    long long gongyueshu;  
    while(scanf("%d",&n)!=EOF)  
    {  
        for(i=0;i<n;i++)  
            scanf("%lld",&a[i]);  
        for(i=0;i<n-1;i++)  
        {  
            for(j=1;j<=a[i];j++)  
            {  
                if(a[i]%j==0 &&a[i+1]%j==0)  
                    gongyueshu=j;  
            }  
            ji=a[i]*a[i+1];  
            a[i+1]=ji/gongyueshu;  
        }  
        printf("%lld\n",a[i]);  
    }  
    return 0;  
}  
