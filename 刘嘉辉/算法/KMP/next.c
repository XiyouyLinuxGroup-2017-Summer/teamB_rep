/*************************************************************************
	> File Name: next.c
	> Author:九五二七 
	> Mail: 
	> Created Time: 2017年10月09日 星期一 22时21分57秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
int  main ()
{
    int  j = 0;
    int  k = -1; 
    int  next[5];
    next[0] = -1;
    
    char str[6]="abab";
    char ptr[10];
    
    gets(ptr);

    int  len_1 = strlen(ptr);
    int  len =  strlen(str)-1;
    
    while(  j< len ){
        if( k==-1 || str[j] == str[k] ){
            next[++j] = ++k;
        }
        else{
            k = next[k];
        }
    }
    for (int i=0;i<4;i++)
    printf("%d ",next[i]);
    printf("\n");
    int i=0;
    j=0;

    while (i<len && j<len_1 ){    
        if  (i==-1 || str[i] == ptr[j]){
            i++;
            j++;
        }
        else {
            i = next[i];
        }    
    }
    if  (i < len )
        printf("无匹配\n");
    if  (i==len)
        printf("i = %d j=%d 位置为 %d",i,j,j-i);



}
