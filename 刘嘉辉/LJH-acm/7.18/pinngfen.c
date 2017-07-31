/*************************************************************************
	> File Name: pinngfen.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月18日 星期二 09时10分10秒
 ************************************************************************/

#include<stdio.h>
int main () {
float m,n,k;
float max= 0,min =100,sum = 0;
float mm;   
    while( scanf("%f",&n) != EOF ){
    m = n-2 ;
    sum = 0;
    min = 100;
    max = 0 ;
    while(n--) {
        scanf("%f",&k);
        if (k >= max) max = k;
        if (k <= min) min = k;
        sum = sum +k;
        mm = max + min ;    
    }
    printf("%.2f\n",(sum - mm)/m);
    }
}
