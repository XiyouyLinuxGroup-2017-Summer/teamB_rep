/*************************************************************************
	> File Name: a.c
	> Author:九五二七 
	> Mail: 
	> Created Time: 2017年07月25日 星期二 18时03分00秒
 ************************************************************************/

#include<stdio.h>    
int gcd(int a,int b)  
{
    return b == 0 ? a : gcd(b,a%b);
}  

int main()  

{  
    int t,a,b,c;  
    scanf("%d",&t);
    
     while(t--)  
        {  
            scanf("%d%d",&a,&b);  
            c=2*b;  
            while(gcd(a,c)!=b)  
              c+=b;  
            printf("%d\n",c);  
        }  
      
    return 0;  
}  
