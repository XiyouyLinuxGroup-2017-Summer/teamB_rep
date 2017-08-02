/*************************************************************************
	> File Name: env.c
	> Author:九五二七 
	> Mail: 
	> Created Time: 2017年07月25日 星期二 11时13分18秒
 ************************************************************************/

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

extern  char **environ;

int main (int argc,char **argv)
{
    int i;
    
    printf("Argument :\n");
    for (i=0;i<argc;i++)
    {
        printf("argv[%d] is  %s \n",i,argv[i]);
    }
    printf("Enviroment: \n");

    for (i=0; environ[i] != NULL;i++)
    {
        printf("%s\n",environ[i]);
    }
    return 0;
}
