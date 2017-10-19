/*************************************************************************
	> File Name: ne.c
	> Author:九五二七 
	> Mail: 
	> Created Time: 2017年10月10日 星期二 16时37分59秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
int main(){
    int i = 0; // 主串的位置
    int j = 0; // 模式串的位置
    int k =-1;
    int next[100];
    next[0] = -1;
	char str[100];
    char ptr[100];
    fgets(str,100,stdin); //获取主串
    fgets(ptr,100,stdin); //获取模式串

    int len_1= strlen(str);
    int len_2= strlen(ptr);
    
    while (j < (len_2-1)) {
       if (k == -1 || ptr[j] == ptr[k]) {
           next[++j] = ++k;
       } else {  //不相等的时候需要回溯
           k = next[k]; 
       }
    }
 	
    i=0;   j=0;
 
    while (i < len_1 && j < len_2) {

       if (j == -1 || str[i] == ptr[j]) { // 当j为-1时，要移动的是i，当然j也要归0
           i++;
           j++;
       } else {
           j = next[j]; // j回到指定位置
       }
    }
    if (j == len_2) {

       printf("位置为%d" ,i - j);

    } else {

       printf("tan 90`\n");
    }

}
