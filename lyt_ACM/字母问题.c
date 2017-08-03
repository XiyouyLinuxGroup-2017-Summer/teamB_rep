/*************************************************************************
	> File Name: 字母问题.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月02日 星期三 15时01分02秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int max;
int vist[255];
int R,C;
char a[21][21];

int check(int x,int y){
    if(x < 0 || x >= R || y < 0 || y >= C){
        return 0;
    }
    if(vist[a[x][y]] == 1){
        return 0;
    }

    return 1;
}

int dfs(int deep,int x,int y){
    if(check(x,y)){
        vist[a[x][y]] = 1;
        if(deep > max){
            max = deep;
        }
        dfs(deep+1,x-1,y); 
        dfs(deep+1,x,y+1); 
        dfs(deep+1,x+1,y); 
        dfs(deep+1,x,y-1); 
        vist[a[x][y]] = 0;
        return 0;
    } 
    return 0;
}


int main(void){
    int r,c;
    int i,j;
    while(scanf("%d %d",&r,&c) != EOF){
        max = 0;
        memset(vist,0,255);
        R = r;
        C = c;
        for(i = 0;i<r;i++){
            scanf("%s",a[i]);
        }

        dfs(1,0,0);

        printf("%d\n",max);
    }
}
