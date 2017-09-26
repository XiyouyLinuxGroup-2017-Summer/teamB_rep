/*************************************************************************
	> File Name: parenthesis-matching.c
	> Author:九五二七 
	> Mail: 
	> Created Time: 2017年09月22日 星期五 16时46分21秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
int main ()
{
    int i,top=0,len;
    char  str[101],ptr[101];
    gets(str);
    len =strlen (str);
    for (i=0;i<len ;i++){
        if (str[i]=='[' || str[i]=='{')
            ptr[++top] = str[i];
        if (str[i]==']' || str[i]=='}')
            if( str[i]==']' && ptr[top]=='[' || str[i]=='}' && ptr[top]=='{')
                top--;
        
    }
    if(top==0)
        printf("YES\n");
    else 
        printf("NO\n");

}
