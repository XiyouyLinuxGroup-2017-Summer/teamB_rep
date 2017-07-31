/**:x
 ***********************************************************************
	> File Name: B.c
	> Author:九五二七 
	> Mail: 
	> Created Time: 2017年07月24日 星期一 17时49分08秒
 ************************************************************************/

#include<stdio.h>   
long long gcd(long long g,long long h)  
{  
    long long t;  
    while(g%h)  
        {  
                    t=g%h;  
                    g=h;  
                    h=t;  
                }  
        return h;  
}//辗转相除法求最小公倍数   
int main()  
{  
    int n,i,j;  
    long long a,b,c,d,e,f,t,m,k;  
    scanf("%d",&n);  
    while(n--)  
    {  
            scanf("%lld/%lld%lld/%lld",&a,&b,&c,&d);  
            e=b*c;  
            f=a*d;  
            m=b*d;//通分   
            if(e>f)  
            {  
                        t=e;  
                        e=f;  
                        f=t;  
                    }  
            t=gcd(f,e);  
            t=f/t*e;  
            if(t%m==0)//能除整   
            printf("%lld\n",t/m);  
            else//不能整除,要化简后，输出分数   
            {  
                        if(m<t)  
                        k=gcd(t,m);  
                        k=gcd(m,t);//求分子分母最大公约数   
                        printf("%lld/%lld\n",t/k,m/k);    
                    }  
         }   
    return 0;  
}  
