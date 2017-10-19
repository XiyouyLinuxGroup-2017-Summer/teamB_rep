/*************************************************************************
	> File Name: 快速排序.c
	> Author:九五二七 
	> Mail: 
	> Created Time: 2017年09月26日 星期二 20时55分25秒
 ************************************************************************/

#include<stdio.h>
int  a[101],n;
void quicksort(int left,int right)
{
    int  temp,i,j,t;
    
    if ( left > right)
        return ;
    
    i = left;
    j = right;
    temp = a[i];
    
    while(i!=j){
        while( a[j]>=temp && i<j){
            j--;
        }
        while( a[i]<=temp  && i<j){
            i++;    
        }
        
        if( i<j ){
            t = a[i];
            a[i]= a[j];
:x

            a[j] = t;
        }
    }
    a[left] = a[i];
    a[i] = temp;

    quicksort(left,i-1);
    quicksort(i+1,right);
    return ;
}

int   main()
{
    int  i,j;
    printf("请输入个数\n");
    scanf("%d",&n);
    for  (i=1;i<=n;i++){
        scanf("%d",&a[i]);
    }
    
    printf("请输入个数\n");
    
    quicksort(1,n);
    for (j=1;j<=n;j++)
    {
        printf("%d ",a[j]);
    }
    //getchar();

}

