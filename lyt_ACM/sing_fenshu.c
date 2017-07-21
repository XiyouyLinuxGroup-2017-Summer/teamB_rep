/*************************************************************************
	> File Name: sing_fenshu.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月18日 星期二 08时50分59秒
 ************************************************************************/

#include<stdio.h>

int main(void){
    int n,sum,c,i;
    int max,min;
    float out;
    while(scanf("%d",&n) != EOF){
        sum = 0;
        min = 101;
        max = -1;
        for(i = 0;i < n;i++){
            scanf("%d",&c);
            if(c>max){
                max = c;
            }
            if(c<min){
                min = c;
            }
            sum += c;
        }
        sum = sum - max - min;
        out = sum *1.0 / (n - 2);
        printf("%.2f\n",out);
    }
    return 0;
}
