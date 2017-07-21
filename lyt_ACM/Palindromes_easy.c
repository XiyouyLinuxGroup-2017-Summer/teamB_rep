/*************************************************************************
	> File Name: Palindromes_easy.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月21日 星期五 10时06分06秒
 ************************************************************************/

#include<stdio.h>

int main(void){
    int n;
    scanf("%d%*c",&n);
    int i;
    char ch[1000];
    int len;
    int j,flag;
    for(i = 0;i<n;i++){
        scanf("%[^\n]%n%*c",ch,&len);
        flag = 1;
        for(j = 0;j<len/2;j++){
            if(ch[j] != ch[len - j - 1]){
                flag = 0;
                break;
            }
        }
        if(flag == 0){
            puts("no");
        }
        else{
            puts("yes");
        }
    }
}
