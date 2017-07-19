/*************************************************************************
	> File Name: mail_check.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月18日 星期二 08时27分59秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>

void check(char str[101]){
    int len = strlen(str);
    int flag = 1;
    if(str[0] == '.' || str[0] == '@' || str[len-1] == '.' || str[len-1] == '@'){
        flag = 0;
        puts("NO");
        return;
    }
    int index;
    int i,count = 0;
    for(i = 0;i<len;i++){
        if(str[i] == '@'){
            count++;
            index = i;
        }
    }
    if(count != 1){
        flag = 0;
        puts("NO");
        return;
    }
    count = 0;
    if(str[index-1] == '.' || str[index+1] == '.'){
       flag = 0;
        puts("NO");
        return;
    }
    for(i = index+2;i<len;i++){
        if(str[i] == '.'){
            count++;
        }
    }
    if(count == 0){
        flag = 0;
        puts("NO");
        return;
    }
    puts("YES");

}

int main(void){
    char mail[101];
    memset(mail,0,sizeof(mail));
    while(scanf("%s",mail) != EOF){
        check(mail);
    }
    return 0;
}
