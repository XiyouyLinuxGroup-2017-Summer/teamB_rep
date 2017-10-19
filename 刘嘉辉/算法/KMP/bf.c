/*************************************************************************
	> File Name: bf.c
	> Author:九五二七 
	> Mail: 
	> Created Time: 2017年10月10日 星期二 14时43分47秒
 ************************************************************************/

#include<stdio.h>
#include <string.h>
int main(){
        
        int j = 0; // 模式串的位置
        int i = 0; // 主串的位置
        int len_1;
        int len_2;
        char str[100];
        char ptr[100];
        
        fgets(str,100,stdin); //获取主串
        fgets(ptr,100,stdin); //获取模式串
        
        len_1 = strlen(str);
        len_2 = strlen(ptr);
        
    while (i < len_1 && j < len_2){
        
               if (str[i] == ptr[j]) { // 当两个字符相同，就比较下一个
                    i++;
                    j++;
                } else {
                    i = i - j + 1; // 一旦不匹配，i后退
                    j = 0; // j归为0
                }
    }
    if (j == len_2) {
               printf("位置为%d\n",i-j);    //找到就输出第一个符号的序号
            
    } else {
               printf("tan 90`\n");   //不存在
            }
    }

