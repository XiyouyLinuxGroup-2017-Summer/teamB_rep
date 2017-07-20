/*************************************************************************
	> File Name: my_mv.c
	> Author:hxllhhy
	> Mail:hxllhhy@gmail.com
	> Created Time: 2017年07月20日 星期四 14时34分44秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
int main(int argc,char **argv)
{
    if(argc<3)
    {
        printf("my_mv <old file> <new file>\n");
        exit(0);
    }
    if(rename(argv[1],argv[2])<0)
    {
        perror("rename");
        exit(1);
    }
    return 0;
}
