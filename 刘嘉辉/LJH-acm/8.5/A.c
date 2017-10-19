#include<stdio.h>
#include<string.h>

int main()
{
    int i,j,n,max,t;
    char s[1005][20];
    char count[1005];
    while(scanf("%d",&n)!=EOF)
    {
        if(n==0)
            break;
        memset(count,0,1005);
        for(i=0;i<n;i++)
            scanf("%s",s[i]);
        for(i=0;i<n-1;i++)
            for(j=i+1;j<n;j++)
            {
                if(strcmp(s[i],s[j])==0)
                {
                    count[i]++;
                }
            }
        max=count[0];
        t=0;
        for(i=0;i<n;i++)
        {
            if(count[i]>max)
            {
                max=count[i];
                t=i;
            }
        }
        printf("%s\n",s[t]);
    }
    return 0;
}

