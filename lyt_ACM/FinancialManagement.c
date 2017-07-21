/*************************************************************************
	> File Name: FinancialManagement.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月21日 星期五 10时25分36秒
 ************************************************************************/

#include<stdio.h>

int main(void){
    int i;
    double sum = 0,each;
    for(i = 0;i<12;i++){
        scanf("%lf",&each);
        sum += each;
    }
    printf("$%.2lf\n",sum/12);
    return 0;
}
