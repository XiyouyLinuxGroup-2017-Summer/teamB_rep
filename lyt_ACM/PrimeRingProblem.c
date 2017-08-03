/*************************************************************************
	> File Name: PrimeRingProblem.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月29日 星期六 15时08分59秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
int main(void)
{
    int a[40];
    int i = 1,j;
    for(i = 1;i<40;i++){
        a[i] = 1;
        for(j = i-1;j>1;j--){
            if(i%j == 0){
                a[i] = 0;
                break;
            }
        }
    }

    int n;
    int *c;
    while(scanf("%d",&n) != EOF){
        c = malloc(sizeof(int)*n);
        c[0] = 1;
        dfs(c,n,a);
    }
    
}

void dfs(int *c,int i,int n,int a[40]){
    
}
