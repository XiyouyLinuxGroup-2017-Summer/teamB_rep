/*************************************************************************
	> File Name: B.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月22日 星期六 15时14分47秒
 ************************************************************************/

#include<stdio.h>
int main ()
{
    int n;
    int a,b;
    scanf("%d",&n);
    while (n--) {
        scanf("%d %d",&a,&b);
        if(a>=100)   a = a%100;
        if(b>=100)   b = b%100;
        if(a+b >= 100)  
        printf("%d\n",a+b-100);
        else  printf("%d\n",a+b);
    }

}
