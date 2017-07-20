/*************************************************************************
	> File Name: g.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月17日 星期一 11时43分12秒
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
int main () {
    int a,sum=0,k,n=0;
    scanf("%d",&n);
    while(n--) {
        scanf("%d",&a);
        sum = 0;
        while (a--) {
                    
        scanf("%d",&k);
        sum = sum + k;
            
        }
        if(a==1){ printf("%d",sum);break;} 
        printf("%d\n\n",sum);
        
    }
return 0 ;
}

