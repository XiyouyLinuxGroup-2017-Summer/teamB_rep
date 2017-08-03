/*************************************************************************
	> File Name: 发工资.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月03日 星期四 08时50分31秒
 ************************************************************************/

#include<stdio.h>
int main(void){
    int n,l,a,i,j;
    int mony[6] = {100,50,10,5,2,1};
    while(scanf("%d",&n) && n != 0){
        l = 0;
        for(i = 0;i<n;i++){
            scanf("%d",&a);
            for(j = 0;j<6;j++){
                l += a/mony[j];
                a = a%mony[j];
            }
        }
        printf("%d\n",l);
    }
}
