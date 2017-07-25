/*************************************************************************
	> File Name: 又见GCD.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月25日 星期二 17时19分06秒
 ************************************************************************/

#include<stdio.h>
long long gcd(long long a,long long b){
    return b?gcd(b,a%b):a;
}

int main(void){
    int n;
    scanf("%d",&n);
    long long a,b,c;
    int i;
    for(i = 0;i<n;i++){
        scanf("%lld %lld",&a,&b);
        long long min = a<b?a:b;
        long long j;
        for(j = min+1;;j++){
            if(j == b){
                continue;
            }
            if(gcd(a,j) == b){
                printf("%lld\n",j);
                break;
            }
        }

    }
}
