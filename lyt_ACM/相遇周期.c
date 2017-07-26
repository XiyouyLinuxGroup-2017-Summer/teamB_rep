/*************************************************************************
	> File Name: 相遇周期.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月24日 星期一 17时32分32秒
 ************************************************************************/

#include<stdio.h>
long long gdc(long a,long b){
    return b ? gdc(b,a%b):a;
}

int main(void){
    int n;
    scanf("%d",&n);
    int i;
    long x,y,a,b,c,d,f;
    for(i = 0;i<n;i++){
        scanf("%lld/%lld",&a,&b);
        scanf("%lld/%lld",&c,&d);
        f = gdc(a,b);
        a = a/f;
        b = b/f;
        f = gdc(c,d);
        c = c/f;
        d = d/f;
        y = gdc(b,d);
        x = (a*c)/gdc(a,c);
        f = gdc(x,y);
        x = x/f;
        y = y/f;
        if(x%y){
            printf("%lld/%lld\n",x,y);
            
        }else{
            printf("%lld\n",x/y);
        }

    }

}
