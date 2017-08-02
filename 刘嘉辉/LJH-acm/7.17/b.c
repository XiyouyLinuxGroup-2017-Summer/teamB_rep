/*************************************************************************
	> File Name: b.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月17日 星期一 10时51分29秒
 ************************************************************************/
#include<stdio.h>
#include <stdlib.h>

int main () {
        int a,sum=0,k;
    while(scanf("%d",&a) && a!=0) {
        sum = 0;
        while (a--) {
                   
                scanf("%d",&k);
                    sum = sum + k;
                    
        }
                printf("%d\n",sum);
            
    }
        return 0 ;


}
