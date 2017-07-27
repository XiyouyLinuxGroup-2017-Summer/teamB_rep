/*************************************************************************
	> File Name: env.c
	> Author:hxllhhy
	> Mail:hxllhhy@gmail.com
	> Created Time: 2017年07月26日 星期三 02时10分02秒
 ************************************************************************/

#include<stdio.h>
#include<malloc.h>

extern char **environ;

int main(int argc,char *argv[])
{
    int i;

    printf("Argument:\n");
    for(i=0;i<argc;i++)
    {
        printf("argv[%d] is %s\n",i,argv[i]);
    }

    printf("Environment:\n");

    for(i=0;environ[i]!=NULL;i++)
    {
        printf("%s\n",environ[i]);
    }

    return 0;
}

