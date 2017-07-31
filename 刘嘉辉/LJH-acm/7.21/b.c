/*************************************************************************
	> File Name: b.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月21日 星期五 14时36分46秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>

int main ()
{
    int  n,l;
    char str[1000];
    scanf("%d",&n);
    getchar();
    while (n--) {
        int i=0;
        int  flag=0;
        gets(str);
        l = strlen (str)-1;
        while (1) {
            for (i=0 ;i< l/2;i++) {
                if(str[i] != str[l--]) {
                    flag=1;   
                    break;
                }    
            }    
        break;
        }
        if (n&&flag==1)   printf("no\n");
        if (n&&flag==0)   printf("yes\n");
        
        if (n==0&&flag==1) printf("no");
        if (n==0&&flag==0) printf("yes");
    }
}
