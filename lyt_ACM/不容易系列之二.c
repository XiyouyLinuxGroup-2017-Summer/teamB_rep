/*************************************************************************
	> File Name: 不容易系列之二.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月21日 星期五 09时58分56秒
 ************************************************************************/

#include<stdio.h>

int main(void){
    int num[31];
    num[0] = 3;
    int i = 0;
    for(i = 1;i<31;i++){
        num[i] = (num[i-1]-1) * 2;
    }
    int n;
    scanf("%d",&n);
    int x;
    for(i = 0;i<n;i++){
        scanf("%d",&x);
        printf("%d\n",num[x]);
    }
}
