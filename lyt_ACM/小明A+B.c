/*************************************************************************
	> File Name: 小明A+B.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月22日 星期六 13时51分36秒
 ************************************************************************/

#include<stdio.h>
int main(void){
    int n;
    scanf("%d",&n);
    int i;
    int x,y,sum;
    for(i = 0;i<n;i++){
        scanf("%d %d",&x,&y);
        sum = (x%100 + y % 100)%100;
        printf("%d\n",sum);
    }
}
