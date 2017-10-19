/*************************************************************************
	> File Name: 迷宫.c
	> Author:九五二七 
	> Mail: 
	> Created Time: 2017年09月25日 星期一 19时50分13秒
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
int migong[10][10]=
{
    {1,1,1,1,1,1,1},
    {1,0,1,0,1,0,1},
    {1,0,0,1,0,0,1},
    {1,1,0,0,0,0,1},
    {1,1,1,1,1,1,1},
};
typedef  struct{
    int i;//行
    int j;//列
    int position;//表示下一可走方块的方位
}BOX;
typedef struct{
    BOX   data[100];
    int top;
}STACK;
void mgpath(int s_x,int s_y,int  m,int n )
{
    int i,j,k,position,flag;
    STACK  MG;
    MG.top = -1;//栈的初始化
    MG.top++;
    MG.data[MG.top].i = s_x;//初始行
    MG.data[MG.top].j = s_y;//初始列
    MG.data[MG.top].position = 0;//初始化无方位
    migong[s_x][s_y]=-1;
    while(MG.top>-1) 
    {
        i=MG.data[MG.top].i;
        j=MG.data[MG.top].j;
        position = MG.data[MG.top].position;
        flag = 0;
        if(i==m && j==n){
            for(k=0;k<=MG.top;k++){
                printf("x=%d,y=%d,position=%d\n",MG.data[k].i,MG.data[k].j,MG.data[k].position);
            }        
        return ;
        }

        while (position<5  && flag ==0 )
        {
            position++;
            switch (position){
            
                case 1:  
                    i=MG.data[MG.top].i-1;         
                    j=MG.data[MG.top].j;          
                    break;
                case 2: 
                    i=MG.data[MG.top].i;         
                    j=MG.data[MG.top].j+1;          
                    break;
                case 3: 
                    i=MG.data[MG.top].i+1;         
                    j=MG.data[MG.top].j;          
                    break;
                case 4:
                    i=MG.data[MG.top].i;         
                    j=MG.data[MG.top].j-1;          
                    break;
            }  
        if(migong[i][j] ==0 )  flag=1;
        }
        if(flag==1){
            
            MG.data[MG.top].position = position;
            MG.top++;
            MG.data[MG.top].i = i;
            MG.data[MG.top].j = j;
            migong[i][j]=-1;
            MG.data[MG.top].position = 0;
        }
        else{
            migong[MG.data[MG.top].i][MG.data[MG.top].j]=0;
            MG.top--;
        }
 
    }
    if(MG.top <=0)
        printf("此迷宫无解\n");
}

int  main()
{
    int i,j;
    for (i=0;i<5;i++){
        for(j=0;j<7;j++)
            printf("%d ",migong[i][j]);
        printf("\n");
    }
    mgpath(1,1,3,5);
}
