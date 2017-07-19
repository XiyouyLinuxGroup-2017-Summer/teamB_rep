/*************************************************************************
	> File Name: p81.c
	> Author:hxllhhy
	> Mail:hxllhhy@gmail.com
	> Created Time: 2017年07月18日 星期二 17时38分15秒
 ************************************************************************/

#include<stdio.h>

void copy_string1(char src[],char dst[]) //接收两个数组作参数
{
    int i;

    for(i=0;src[i]!='\0';i++)
        dst[i]=src[i];
    dst[i]='\0';
}

void copy_string2(char *psrc,char *pdst)  //接收两个指向字符串的指针作参数
{
    for(;*psrc!='\0';psrc++,pdst++)
        *pdst=*psrc;
    *pdst='\0';
}

int main()
{
    char a[]="Linux C Program",b[20],c[20];

    copy_string1(a,b);
    copy_string2(a,c);

    printf("%s\n%s\n%s\n",a,b,c);

    return 0;
}
