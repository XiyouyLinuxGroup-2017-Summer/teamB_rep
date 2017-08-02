/************************************************************************
	> File Name: B.c
	> Author:九五二七 
	> Mail: 
	> Created Time: 2017年07月25日 星期二 16时29分05秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>

void  nizhi(char *st)
{
    int a = strlen (st),i;
    int b=a;
    char  c;
    
    for(i=0;i <(a/2);i++)
    {
        c = st[i];
        st[i] = st[--b];
        st[b] = c;
    }
   // printf("==%d==%d--%s\n",i,b,st);
}

void add(char *s1, char *s2, char *he ,int num)
{
    int jw=0;
    int i,n=0;
    int a=strlen(s1),b=strlen(s2);
    int temp;
    char   *str;
    nizhi(s1);
    nizhi(s2);
      
 //   printf("-----%s\n%s-----------",s1,s2);
    if(a>=b) n=b;
    else     n=a;

    for(i=0;i<n;i++)
    {
        temp = s1[i] -'0' + s2[i] - '0' + jw;
        if(temp >= 10)  
        {
            he[i] = temp%10 + '0';
            jw    = 1;
        }
        else   {   
            he[i] = temp + '0';
            jw    = 0 ;  
        }
    }
    if (n==b){  n=a; str = s1;}
    else if (n==a)  {n=b;str = s2;}
    
    if(jw == 1) 
    {
        for(;i<n;i++)
        {
            temp = jw +str[i] - '0';
            if(temp >= 10)  
            {
                he[i] = temp%10 + '0';
                jw    = 1;
            }
            else   {   
                he[i] = temp + '0';
                jw    = 0 ;  
            }
        }
    //    if(jw==1){
      //      he[n]='1';
        //    he[n+1]='\0';
    //    }
    }
    else{
        for(;i<n;i++)
        {
            he[i] = str[i];    
        }
    }

he[i] = '\0';
nizhi(he);
nizhi(s1);
nizhi(s2);
if(jw==1)
printf("case %d:\n%s + %s = 1%s",num,s1,s2,he);
else 
printf("case %d:\n%s + %s = %s",num,s1,s2,he);

}

int main ()
{
    char s1[1001],s2[1001];
    char he[1001];
    int n,i;
    scanf("%d",&n);
    getchar();
    for(i=1;i<=n;i++){
    scanf("%s%s",s1,s2);
    add(s1,s2,he,i);
    if(i!=n)printf("\n\n");
    }    
}
