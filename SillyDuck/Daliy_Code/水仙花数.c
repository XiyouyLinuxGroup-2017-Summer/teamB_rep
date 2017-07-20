/*************************************************************************
	> File Name: 水仙花数.c
	> Author:hxllhhy
	> Mail:hxllhhy@gmail.com
	> Created Time: 2017年07月20日 星期四 09时36分02秒
 ************************************************************************/

#include<stdio.h>
int main()
{
    int i,i1,i2,i3,m,n,j,k,a[1000];
    while(scanf("%d %d",&m,&n)!=EOF)
    {
        j=0;
        for(i=m;i<=n;i++)
        {
            i1=i%10;
            i2=i/10%10;
            i3=i/100;
            if(i==i1*i1*i1+i2*i2*i2+i3*i3*i3)
            {
                a[j++]=i;
            }
        }
        if(j>0)
        {
            for(k=0;k<j-1;k++)
                printf("%d ",a[k]);
            printf("%d",a[j-1]);
        }
        else
            printf("no");
        printf("\n");
    }
    return 0;
}
