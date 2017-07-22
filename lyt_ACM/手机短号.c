/*************************************************************************
	> File Name: 手机短号.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月22日 星期六 13时55分08秒
 ************************************************************************/

#include<stdio.h>
int main(void){
    int n;
    scanf("%d",&n);
    int i,j;
    char ch[20];
    for(i = 0;i<n;i++){
        scanf("%s",ch);
        printf("6");
        for(j = 6;j<11;j++){
            printf("%c",ch[j]);
        }
        puts("");
    }
}
