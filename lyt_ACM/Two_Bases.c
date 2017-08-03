/*************************************************************************
	> File Name: Two_Bases.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月27日 星期四 17时34分27秒
 ************************************************************************/

#include<stdio.h>
#include<math.h>

int main(void){
    double n,x;
    scanf("%lf %lf",&n,&x);
    double a = 0,b = 0;
    double i,t;
    for(i = 0;i<n;i++){
        scanf("%lf",&t);
        a += pow(x,n-1-i) * t;
    }
    scanf("%lf %lf",&n,&x);
    for(i = 0;i<n;i++){
        scanf("%lf",&t);
        b += pow(x,n-1-i) * t;
    }
    if(a>b){
        puts(">");
    }else if(a == b){
        puts("=");
    }else{
        puts("<");
    }
}
