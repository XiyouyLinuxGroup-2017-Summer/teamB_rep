/*************************************************************************
	> File Name: 母牛.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月19日 星期三 09时45分54秒
 ************************************************************************/
 #include <stdio.h>
 long   f(int  n) {
    if (n<=4)  return  n;
    if (n>4)   return f(n-1) +f(n-3);
 }
 int main () {
    int  n ;
     while (scanf("%d",&n) != EOF&& n!=0 ) {
            printf("%ld",f(n));

     }

}
 
