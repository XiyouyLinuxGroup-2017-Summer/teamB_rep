/*************************************************************************
	> File Name: B.c
	> Author:九五二七 
	> Mail: 
	> Created Time: 2017年08月03日 星期四 14时51分09秒
 ************************************************************************/

#include<stdio.h>
int main ()
{
    int a[8] ={100,50,10,5,2,1};
    int i,m,sum,n;
    while (scanf("%d",&n),n){
    sum  =0 ;    
        while(n--){
            scanf("%d",&m);
            for (i=0;i<6;i++){
            sum = sum + m/a[i];
            m  = m % a[i];
    
            }        
        }
    printf("%d\n",sum);    
    }
}
