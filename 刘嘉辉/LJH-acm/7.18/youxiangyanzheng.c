/*************************************************************************
	> File Name: youxiangyanzheng.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月18日 星期二 08时38分49秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main () {
    char str[101];
    int  flag=1,i=0,a,m=0,n=0;
    int l_1=0,l_2=0;
    while (gets(str) != NULL) {
        a = strlen(str);
        l_1=0,l_2=0;
        m=0;n=0;
        flag = 1;
        if (str[0]!= '@' && str[a-1] != '.' && str[0] != '.' && str[a-1]!= '@' ) {
            for (i=1; i < a ;i++ ) {
                if (str[i] == '@' ) {
                    
                    if (str[i-1]=='.' || str[i+1] == '.') { 
                    flag = 0;
                    break;
                    }
                    ++m;
                    
                    l_1=i;
                }
                if (str[i] == '.' ) { ++n; l_2=i; }
            }
        }
        else 
            flag = 0;
        if (flag == 1 && m==1 && m+n >= 2 && l_1 < l_2 && l_1!=l_2) {
            printf("YES\n");
            }
        else 
            printf("NO\n");
            printf("%d %d %d %d %d\n",m,n,l_1,l_2,flag);    
    }
}
