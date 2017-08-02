/*************************************************************************
	> File Name: A.c
	> Author:九五二七 Bulbbasaur
	> Mail: 
	> Created Time: 2017年07月24日 星期一 16时19分32秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main ()
{
    char str[100001];
    char a[8]="Bulbsar";
    int   i,j,l;
    int  su[7]={0};
    gets(str);
    l = strlen (str);
    for(i=0; i<l ;i++)
    {
        for(j=0; j<7; j++)
        {
            if(a[j] == str[i])
            {
                su[j]++;
            }
        }
    }
    su[1] /= 2;

    su[5] /= 2;
    int min = su[0]; 
    for (i=1; i<7;i++)
    {
        if (su[i] < min )  min = su[i];
    }
    
    printf("%d\n",min);

}
