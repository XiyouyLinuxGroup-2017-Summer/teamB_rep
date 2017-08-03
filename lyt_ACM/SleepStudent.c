/*************************************************************************
	> File Name: SleepStudent.c
	> Author: 
	> Mail: 
	> Created Time: 2017年08月02日 星期三 11时44分26秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

typedef struct stu{
    int a;  // 清醒时长
    int b;  // 睡觉时长
    int c;  // 第n分钟
    int now;  // 当前状态 0睡，1醒
}STU;


int main(void){
    int n;
    int i;
    int nn = 0;
    while(scanf("%d",&n) && n != 0){
        nn++;
        STU *st = malloc(sizeof(STU) * n);
        for(i = 0;i<n;i++){
            scanf("%d %d %d",&st[i].a,&st[i].b,&st[i].c);
            if(st[i].c <= st[i].a){
                st[i].now = 1;
            }else{
                st[i].now = 0;
            }
        }
        int j;
        int flag = 1;
        int count;  // 上分钟睡着的人数
        for(i = 1;i<1000000;i++){
            //printf("第%d分钟大家的状态：\n",i);
            for(j = 0;j<n;j++){
                //printf("学生%d:%d %d %d %d\n",j,st[j].a,st[j].b,st[j].c,st[j].now);
            }
            count = 0;
            for(j = 0;j<n;j++){
                if(st[j].now == 0){
                    count ++;
                }
            }
            //printf("第%d分钟，%d\n",i,count);
            if(count == 0){
                printf("Case %d: %d\n",nn,i);
                break;
            }else{
                for(j = 0;j<n;j++){
                    st[j].c += 1;
                    if(st[j].c == (st[j].a + 1)){ //即将睡觉
                        //puts("有人想睡觉");
                        if((n-count) >= count){
                            st[j].c = 1; //再等一轮
                        }else{
                            st[j].now = 0; //开始睡觉
                        }
                    }else if(st[j].c == (st[j].a + st[j].b + 1)){ // 一个周期完了
                        st[j].c = 1;
                        st[j].now = 1;
                    }
                }
            }
        }
        if(i == 1000000){
            printf("Case %d: -1\n",nn);
        }
        free(st);
    }

}
