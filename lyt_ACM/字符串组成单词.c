/*************************************************************************
	> File Name: 字符串组成单词.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月24日 星期一 16时59分54秒
 ************************************************************************/

#include<stdio.h>

int main(void){
    
    //Bulbasaur
    int a[7] = {0};
    char c;
    while((c = getchar() )!= '\n'){
        switch (c){
            case 'B': a[0]++;
            case 'u': a[1]++; //
            case 'l': a[2]++;
            case 'b': a[3]++;
            case 'a': a[4]++; //
            case 's': a[5]++;
            case 'r': a[6]++;
            default: break;
        }
    }
    a[1] = a[1]/2;
    a[4] = a[4]/2;
    int i,min = a[0];
    for(i = 1;i<7;i++){
        if(a[i]<min){
            min = a[i];
        }
    }
    printf("%d\n",min);

}
