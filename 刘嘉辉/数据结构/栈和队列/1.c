/*************************************************************************
	> File Name: 马踏棋盘.c
	> Author:九五二七 
	> Mail: 
	> Created Time: 2017年09月25日 星期一 19时35分59秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
int  qipan[6][6]=
{
    {0,0,0,0,0,0},
    {0,0,0,0,0,0},
    {0,0,0,0,0,0},
    {0,0,0,0,0,0},
    {0,0,0,0,0,0},
    {0,0,0,0,0,0}
};
int  step=0;

typedef struct data{
    int  i;//行
    int  j;//列
    int  position;
    struct data*next;
    
}NODE;

void pushLstack (NODE *Top,int i,int j){    
    
    step++;
    NODE  *pnew;
    pnew = (NODE *) malloc(sizeof(NODE));
    pnew->i = i;
    pnew->j = j;
    pnew->position = 0;
    pnew->next = Top->next;
    Top->next = pnew;
    qipan[i][j]=step;

}
void popLstack(NODE *Top){

    NODE *pdel;
    pdel = Top->next;
    Top->next = pdel->next;
    qipan[pdel->i][pdel->j]=0;
    free (pdel);
    step--;
}
void isEmpty(NODE *Top){
    NODE *pnew ;
    if (Top->next ==NULL)
        printf("无解");
}
void Outputmath(NODE *Top){
    NODE *pnew;
    pnew = Top->next;
    while (pnew !=NULL) {
        printf("(%d,%d,%d)\n",pnew->i,pnew->j,pnew->position);
        pnew = pnew->next;
    }
}
void Horsepath(int s_x,int s_y)
{
    NODE  *Top;
    int position = 0,i,j,flag;
    Top = (NODE *) malloc(sizeof(NODE));
    Top ->next = NULL;
    pushLstack(Top, s_x,s_y);
    position = 0;
    while (Top->next != NULL){
        i = Top->next->i;
        j = Top->next->j;

        position = Top->next->position;
        
        printf("到底咋回事%d,%d,%d\n",step,i,j);
        flag=0;


        if(step == 36){
            Outputmath(Top);
            return;
        }
        while(position < 9  && flag ==0 ){
            
            position++;
           // printf("position=%d\n",position);
            switch(position){
                case 1:
                    i=Top->next->i-2;
                    j=Top->next->j+1;
                    break;
                case 2:
                    i=Top->next->i-1;
                    j=Top->next->j+2;
                    break;
              case 3:
                    i=Top->next->i+1;
                    j=Top->next->j+2;
                    break;
                case 4:
                    i=Top->next->i+2;
                    j=Top->next->j+1;
                    break;
                case 5:
                    i=Top->next->i+2;
                    j=Top->next->j-1;
                    break;
                case 6:
                    i=Top->next->i+1;
                    j=Top->next->j-2;
                    break;
                case 7:
                    i=Top->next->i-1;
                    j=Top->next->j-2;
                    break;
                case 8:
                    i=Top->next->i-2;
                    j=Top->next->j-1;
                    break;
            }
        
            
            
        if (i>=0&&i<=5&&j>=0&&j<=5 && qipan[i][j] == 0)
            flag =1;
        }
        Top->next->position = position;
        if(flag == 1)
            pushLstack(Top,i,j);
        }

    }
}
int  main ()
{
    int i,j;
    Horsepath(1,1);
    for(i=0;i<6;i++){
        for(j=0;j<6;j++)
            printf("%-2d ",qipan[i][j]);
        printf("\n");
    }    
}
