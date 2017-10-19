/*************************************************************************
	> File Name: A.c
	> Author:九五二七 
	> Mail: 
	> Created Time: 2017年08月03日 星期四 15时40分25秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
int main (){
    char a[10002];
    char b[10002];
    int  i,j,s1,s2,m,n;
    int flag1 = 0, flag2 = 0; 
    while (scanf("%s%s",a,b) != EOF  )
    {
        s1=0;
        s2=0;
        m = strlen(a);
        n = strlen(b);
            
        for (i=m-1;i>=0; i--)//判断ａ是不是小数
        {
            if(a[i] != '0')  s1=i;
            if (a[i] == '.'){
                flag1 = 1;
            } 
        }        
        //    printf("s1==%d\n",s1);
        for (i=n-1;i>=0; i--)//判断b是不是小数
        {
            if(b[i] != '0' )  s2=i;
            if (b[i] == '.'){
                flag2 = 1;
             //   break;
            }
        }
        //    printf("s2==%d\n",s2);
        if(flag1) {
            for ( i = m-1 ;i>=0 ;i-- ) {
                if (a[i] != '0'){
                    m=i;
                    if(a[i] == '.')
                        a[i] = '\0';
                    a[i+1] = '\0';
                break;
                }
            }   
        }
        if(flag2) {
            for ( i = n-1 ;i>=0 ;i-- ) {
                if (b[i] != '0'){
                    n=i;
                    if(b[i] == '.')
                        b[i] = '\0';
                    b[i+1] = '\0';
                break;
                }    
            }
        } 

        if( strcmp(&a[s1],&b[s2]) == 0 )  
            printf("YES\n");
        else  
            printf("NO\n");
    }
}
