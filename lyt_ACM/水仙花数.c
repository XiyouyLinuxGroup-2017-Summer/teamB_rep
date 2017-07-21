/*************************************************************************
	> File Name: 水仙花数.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月20日 星期四 10时10分58秒
 ************************************************************************/

#include<stdio.h>

int main(void)
{
    int set[1000];
    int i,j;
    int x,y,z;
    int n = 0;
    for(i = 100;i<1000;i++){
        x = i/100;
        y = (i - 100*x)/10;
        z = i-100*x-10*y;
        if(x*x*x+y*y*y+z*z*z == i){
            set[n] = i;
            n++;
        }
    }
    int left,right;
    int start,cont;
    while(scanf("%d %d",&left,&right)!=EOF){
        start = -1;
        cont = 0;
        for(i = 0;i<n;i++){
            if(set[i] >= left && set[i] <= right){
                if(start == -1){
                    start = i;
                }
                cont = cont + 1;
            }
        }
        if(cont == 0){
            puts("no");
            continue;
        }
        for(i = start;i<start + cont -1;i++){
            printf("%d ",set[i]);
        }
        printf("%d\n",set[i++]);
    }
}
