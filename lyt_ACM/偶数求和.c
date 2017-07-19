/*************************************************************************
	> File Name: 偶数求和.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月18日 星期二 08时59分59秒
 ************************************************************************/

#include<stdio.h>

void out(int n,int m){
    int star = 2;
    int i;
    int sum = 0;
    int cont = 0;
    for(i = 0;i<n;i++){
        cont ++;
        sum += star;
        star+=2;
        if(cont == m){
            printf("%d",sum/cont);
            cont = 0;
            sum = 0;
            if(i != n-1){
                printf(" ");
            }
        }
    }
    if(cont != 0){
        printf("%d",sum/cont);
    }
    printf("\n");
}

int main(void){
    int n,m;
    while(scanf("%d %d",&n,&m)!=EOF){
        out(n,m);
    }
    return 0;
}
