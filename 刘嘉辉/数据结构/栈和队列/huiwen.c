/*************************************************************************
	> File Name: huiwen.c
	> Author:九五二七 
	> Mail: 
	> Created Time: 2017年09月22日 星期五 11时21分18秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
int  main ()
{
    int   i,middle,len,top,next;
    char  str[101],ptr[101];
    gets (str);
    len = strlen (str);

    if (len % 2){
        middle = len/2-1;
        next = middle+2 ;
    }
    else{  
        middle = len/2-1;
        next = middle+1;
        
    }
    printf("middle=%d,next=%d\n",middle,next);
    top=0;
    
    for(i=0;i<=middle ;i++){
        ptr[++top] = str[i];
    }
    
    for(i=next;i<len;i++){
        if (str[i]!= ptr[top])
            break;
    top--;
    }   
    if(top==0)
        printf("YES\n");
    else 
        printf("NO\n");

}
