/*************************************************************************9
	> File Name: a.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月21日 星期五 14时16分20秒
 ************************************************************************/

#include<stdio.h>
int main ()
{
    int i=0;
    double a,sum=0;

    while(scanf ("%lf",&a) != EOF) 
    {
        sum = sum + a;
        if(++i, i==12) {
        printf("$%.2f\n",sum/12 );
        sum = 0;
        i=0;
        }    
    }   

}
