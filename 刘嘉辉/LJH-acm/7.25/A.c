/************************************************/

#include<stdio.h>
int main()
{
    int n;
    int c,b,a;
    scanf("%d",&n);
    while(n--)
    {
        scanf("%d %d",&a,&b);
        c = b+1;
        while(1)
        {
            if(a==b)  { c=2*b;  break;}     
            else if(c%b==0 && a%c!=0 && c%a!=0) break;
            c++;
        }
        printf("%d\n",c);
    }
    return 0; 
}
