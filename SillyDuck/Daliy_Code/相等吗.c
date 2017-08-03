/*************************************************************************
	> File Name: 相等吗.c
	> Author:hxllhhy
	> Mail:hxllhhy@gmail.com
	> Created Time: 2017年08月03日 星期四 15时03分23秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
char *chuli(char *s)
{
    int i,j,l;
    int t,x,flag,mark;
    t=x=0;
    flag=mark=0;
    l=strlen(s);
    for(i=0;i<l;i++)
    {
        if(s[i]=='.')
        {
            t=i;  //标记小数点的位置为t
            flag=1;
        }
    }
    if(!flag) //没有小数点，只处理前导0
    {
        for(i=0;s[i]!='\0';i++) 
        {
            if(s[i]!='0') 
            {
                x=i; 
                break;
            }
        }//标记第一个不为0的数字
        for(i=0;i<l;i++) 
            s[i]=s[i+x];  //把不为0的数字开始到尾全部前移
    }
    else //有小数点，分别处理小数点前和小数点后
    {
        for(i=0;s[i]!='.';i++)
        {
            if(s[i]!='0')
            {
                mark=1; //小数点前不全为0
                x=i;  //标记第一个不为0的数字位置
                break;
            }
        }
        if(!mark) //小数点前全为0
        {
            for(j=0;j<l;j++)
                s[j]=s[t-1+j]; //只留下小数点前唯一的0，从这个0开始到结尾前移
        }
        else //小数点前有不为0的数字
        {
            for(j=0;j<l;j++)
                s[j]=s[x+j]; //把小数点前不为0的数字开始到尾全部前移
        }
        l=strlen(s); //计算此时字符串的长度
        for(i=0;i<l;i++)
        {
            if(s[i]=='.')  //标记此时字符串里小数点的位置
                t=i;
        }
        for(i=l-1;s[i]!='.';i--) //从尾消0，直到不为0的数字停下
        {
            if(s[i]=='0')
                s[i]='\0';
            else
                break;
        }
        if(s[t+1]=='\0') //若小数点后紧跟着0，则把小数点的0也消掉
            s[t]='\0';
    }
    return s;
}

int main()
{
    char a[1000000],b[1000000];
    char *p,*q;
    while(scanf("%s %s",a,b)!=EOF)
    {
        p=chuli(a);
        q=chuli(b);
        if(strcmp(p,q)==0)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
