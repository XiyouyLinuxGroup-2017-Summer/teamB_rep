/*************************************************************************
	> File Name: B.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月20日 星期四 14时27分06秒
 ************************************************************************/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void   fun (char str[]) {
    int  s,i=0,j=0;
    char a[1001];
    s=strlen(str);  
    for(i=0;i<=s;i++) 
    {
        if( str[i]!= '\0' && str[i]!= ' ') 
        {
            a[j++]=str[i];
        }
        else
        { 
            j--;
            for(;j>=0;j--) 
                printf("%c",a[j]);
            if(i!=s) putchar('@');
            j=0;
        }        
    }
  /*  i=s-1;
    while(str[i]!=' '){
        printf("%c",str[i]);
        i--;
    }*/ 
    printf("\n");
}
int main () {
    int i,n;
    char str[1001];
    scanf("%d",&n);
    getchar();
    while(n--) {
       gets(str);
       fun (str);
    }
}
