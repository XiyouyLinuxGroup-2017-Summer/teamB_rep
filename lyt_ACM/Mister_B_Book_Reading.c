/*************************************************************************
	> File Name: Mister_B_Book_Reading.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月22日 星期六 14时06分56秒
 ************************************************************************/

#include<stdio.h>

int main(void){
    int c,v0,v1,a,l;
    scanf("%d %d %d %d %d",&c,&v0,&v1,&a,&l);
    int i = 0,to_s;
    int shengyu = c;
    while(1){
        to_s = v0 + i*a;
        if(to_s>v1){
            to_s = v1;
        }
        i++;
        shengyu = shengyu - to_s;
        if(shengyu<=0){
            break;
        }
        shengyu = shengyu + l;
    }
    printf("%d\n",i);
}
