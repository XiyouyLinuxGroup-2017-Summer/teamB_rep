#include<stdio.h>
#include<string.h>
int main(){
    char word[100];
    int  n ;
    scanf("%d",&n);
    while(n--) {
    scanf("%s",word);//获取字符串 
    int len = strlen(word);//获取字符串长度 
    for(int i=1;i<=len;i++){
            if(len % i==0){//获取整除的最小长度i 
                   int ok = 1;
                   for(int j = i;j<len;j++){
                           if(word[j]!=word[j%i]){//验证之后的单词是否相同 
                             ok = 0;
                             break;                       
                           }
                   }
                   if(ok&&n != 0){
                     printf("%d\n\n",i);
                     break;
                   }
                   if (ok && n==0) {
                        printf("%d\n",i);
                        break;
                  }
            }
    }
   } 
    return 0;
}
