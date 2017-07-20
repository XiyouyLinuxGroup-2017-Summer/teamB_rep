/*************************************************************************
	> File Name: TextReverse.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月20日 星期四 10时35分03秒
 ************************************************************************/

#include<stdio.h>
int main(void){
    char ch[1000];
    int a;
    scanf("%d",&a);
    getchar();
    int i,cont;
    for(i = 0;i<a;i++){
        char c;
        cont = 0;
        int j;
        while(c = getchar()){
            if(c == '\n'){
                for(j = cont-1;j>=0;j--){
                    putchar(ch[j]);
                }
                puts("");
                break;
            }
            else if(c == ' '){
                for(j = cont-1;j>=0;j--){
                    putchar(ch[j]);
                }
                putchar(' ');
                cont = 0;
            }
            else{
                ch[cont] = c;
                cont ++;
            }
        }
    }
}
