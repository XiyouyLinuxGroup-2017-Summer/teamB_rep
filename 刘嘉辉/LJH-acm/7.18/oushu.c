/*************************************************************************
	> File Name: oushu.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月18日 星期二 14时45分27秒
 ************************************************************************/

#include<stdio.h>
int main () 
{
    int  n=0,m=0;
    int  a=0,b=0,aver;
    while (scanf("%d %d",&n,&m) != EOF) 
    {
        if(n<m) { printf("%d\n",n+1);  continue;}       
        else  
            {
                for (int i=0;i<(n/m);i++) 
                {
                    a=2+m*i*2;
                    b=a+(m-1)*2;
                    aver=(a+b)/2;
                    if(n%m==0 && i == (n/m-1))
                    printf("%d",aver);
                    else printf("%d@",aver);
                }
                if( n%m != 0)  printf("%d",(b+1+n%m));
            }       
        printf("\n");

    }


}
