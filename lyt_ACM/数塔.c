/*************************************************************************
	> File Name: 数塔.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月12日 星期六 14时31分53秒
 ************************************************************************/

#include<stdio.h>
int MAX_VALUE;
int MAX_LENGTH;
int num[102][102];
void dfs(int floot,int start,int value){
    if(start >floot){
        return;
    }
    if(floot == MAX_LENGTH-1){
        value += num[floot][start];
        if(value > MAX_VALUE){
            MAX_VALUE = value;
        }
        return;
    }
    dfs(floot+1,start,value+num[floot][start]);
    dfs(floot+1,start+1,value+num[floot][start]);
    return;
}

int main(void){
    int n,i,j,k,l;
    scanf("%d",&n);
    for(i = 0;i<n;i++){
        scanf("%d",&l);
        MAX_LENGTH = l;
        for(j = 0;j<l;j++){
            for(k = 0;k<=j;k++){
                scanf("%d",&num[j][k]);
            }
        }
        MAX_VALUE = 0;
        dfs(0,0,0);
        printf("%d\n",MAX_VALUE);
    }
}
