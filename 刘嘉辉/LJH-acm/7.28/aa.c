/*************************************************************************
	> File Name: aa.c
	> Author:九五二七 
	> Mail: 
	> Created Time: 2017年07月29日 星期六 17时28分22秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
int main ()
{
    int val=1;
    pid_t pid ;

    if (pid = vfork() < 0 )
    {
        printf("error\n");
    }
    
    if ( pid ==0 )
    {
        val++;
        
        return 0;
    }
    
    printf("%d %d\n",getpid(),val);
    return 0;
}
