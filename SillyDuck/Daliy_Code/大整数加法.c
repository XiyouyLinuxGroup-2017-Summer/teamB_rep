/*************************************************************************
	> File Name: 大整数加法.c
	> Author:hxllhhy
	> Mail:hxllhhy@gmail.com
	> Created Time: 2017年07月25日 星期二 20时34分20秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
    char a[1001],b[1001],c[1001],d[1001];
    int i,j,k,m,n,N,t;
    scanf("%d",&N);
    for(t=0;t<N;t++){
    scanf("%s",a);
    scanf("%s",b);
    strcpy(c,a);strcpy(d,b);
    m=strlen(a);
    k=n=strlen(b);
    if(m>k) k=m;
    a[k+1]=0;
    for(i=0;i<k;i++)
        a[k-i]=a[m-i-1];
    for(i=0;i<=k-m;i++)
        a[i]='0';
    for(i=0;i<k;i++)
        b[k-i]=b[n-i-1];
    for(i=0;i<=k-n;i++)
        b[i]='0';
    j=0;
    for(i=0;i<=k;i++)
    {
        j=(a[k-i]+b[k-i]+j-96);
        a[k-i]=j%10+48;
        j=j/10;
    }
    if(a[0]=='0')
        printf("Case %d:\n%s + %s = %s\n",t+1,c,d,a+1);
    else
        printf("Case %d:\n%s + %s = %s\n",t+1,c,d,a);
    if(t!=N-1)
        printf("\n");
    }
    return 0;
}
