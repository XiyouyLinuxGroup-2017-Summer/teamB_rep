/*************************************************************************
	> File Name: 汉字.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月19日 星期三 08时54分37秒
 ************************************************************************/

#include<stdio.h>
int  main ()
{
    
    int  n,sum=0;
    char  letter;
    scanf ("%d",&n);
    getchar();
    while (n--)  {
        sum = 0;
        while ((letter = getchar() ) != '\n') {
            if (letter < 0) 
            sum++;
        }
        if (n==0)  printf("%d",sum/2);
        else   printf("%d\n",sum/2);

    }
}
