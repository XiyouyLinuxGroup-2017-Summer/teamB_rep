/*************************************************************************
	> File Name: 水仙花.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月20日 星期四 14时10分38秒
 ************************************************************************/

#include<stdio.h>
int fun (int m,int n){
    int a,b,c;
    int flag=0;
    for(m;m<=n;m++) {
        a=m/100;
        b=(m-a*100)/10;
        c=m%10;
    
        if(( a*a*a+b*b*b+c*c*c ) == m)  
        {
            if(flag!=0)printf(" ");
            flag=1;
            printf("%d",m);
            continue;
        }
        
        
    }
    if(! flag)  printf("no");
    printf("\n");
}
int  main ()
{
    int m,n;
    while(scanf("%d %d",&m,&n) != EOF)
    fun (m,n);

return 0;
}
