/*************************************************************************
	> File Name: 发工资.c
	> Author:hxllhhy
	> Mail:hxllhhy@gmail.com
	> Created Time: 2017年08月03日 星期四 14时52分59秒
 ************************************************************************/

#include<stdio.h>
int main()
{
    int n,x,i,m,sum;
    int a[6]={100,50,10,5,2,1};
    while(scanf("%d",&n)!=EOF)
    {
        if(n==0)
            break;
        sum=0;
        while(n--)
        {
            scanf("%d",&m);
            x=0;
            for(i=0;i<6;i++)
            {
                if(m%a[i]==0)
                {
                    x+=m/a[i];
                    break;
                }
                else
                {
                    x+=m/a[i];
                    m%=a[i];
                }
            }
            sum+=x; 
        }
        printf("%d\n",sum);
    }
    return 0;
}
