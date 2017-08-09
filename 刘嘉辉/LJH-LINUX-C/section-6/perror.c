/*************************************************************************
	> File Name: perror.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月18日 星期二 21时16分36秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
int main (int argc,char ** argv[]) {
        FILE *fp;
        fp = fopen ("123","r");
        if (fp == NULL ) {
            perro("");
        }

    
 //   fclose(fp);
}
