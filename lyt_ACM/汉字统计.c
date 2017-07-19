/*************************************************************************
	> File Name: 汉字统计.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月19日 星期三 09时27分10秒
 ************************************************************************/

#include<stdio.h>

int main(void){
    int n;
    scanf("%d",&n);
    char cc = getchar();
    int i = 0;
    for(i = 0;i<n;i++){
        int count = 0;
        char c;
        while((c = getchar()) != '\n'){
            if(c<0){
                count = count + 1;
            }
        }
        printf("%d\n",count/3);
    }
}
