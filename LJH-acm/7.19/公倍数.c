/*************************************************************************
	 File Name: 公倍数.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月19日 星期三 10时48分20秒
 ************************************************************************/

#include<stdio.h>
int main ()
{
    int a[100];
    int n,i=0,l;
    long long gbs=0;
    while(scanf("%d",&n) != EOF){
        i=0;
        
        while(n--){
            
           scanf("%d",&a[i++]);

        }
        gbs = a[0];
        for (int j=1;j<i;j++) {
         
            int k=gbs;
         
            if(gbs%a[j] == 0) continue;
            if(a[j]%gbs == 0) {gbs= a[j];continue;}
        
            while (1) {
                if(gbs%a[j] == 0 && gbs%k == 0)  break;
                gbs++;
            }

        }
    printf("%lld\n",gbs); 
    }
    
}
