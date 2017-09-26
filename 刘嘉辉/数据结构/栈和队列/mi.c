# include <stdio.h>  
# include <stdlib.h>  
# include <math.h>  
# define ROWS 8  
# define COLS 8  
int cheesboard [ROWS] [COLS];  
const int moveX [8] = {-2,-1,1,2,2,1,-1,-2};  
const int moveY [8] = {1,2,2,1,-1,-2,-2,-1};  
//初始化棋盘,将棋盘所有的位置赋值为0  
void initBoard (int board[][COLS]){  
    int i ,j;  
    for(i = 0; i < 8; i ++){  
        for( j = 0; j < 8; j ++){  
            board[i][j] = 0;  
        }  
    }  
}  
//从待选的下一个点的集合中路径最短的一个  
int getMinPath (int a[],int num){  
    //定义下标为  
    int i = 0,index=0;  
    //定义最小的值为a【0】，找到最小的值，而且大于0的值  
    int min= a[0];  
    for(i = 0 ; i< num; i++)  
    {  
        if(a[i] >0)  
        {  
            min = a[i];  
            index = i;  
            break;  
        }  
    }  
    for(i = index + 1; i < num ;  i++)  
    {  
        if(a[i] > 0 && min > a[i])  
        {  
            min = a[i];  
            index = i;  
        }  
    }  
    if(a[index] > 0)  
        return index;  
    return -1;  
}  
// 打印路径  
void printPath (int board[][COLS]){  
    int i,j;  
    for (i = 0; i < ROWS; i++){  
        for ( j = 0; j < COLS; j++){  
            printf("%d\t",board[i][j]);  
        }  
        printf("\n\n");  
    }  
}  
// 获得马行走的路径  
void getPath (int board [][COLS], int startX, int startY){  
    //下一个可行位置的数目  
    int next = 0;  
    //路径最短的可行位置在数组中的位置  
    int min;  
    //下一个可行位置的可行位置数目  
    int nextNext;  
    //将棋盘初始化  
    initBoard (board);  
    // 存放下一个位置对应的下一个位置的数目  
    int nextNum[8] = {0,0,0,0,0,0,0,0};  
    //下一个位置的在二维数组中对应位置，初始为0  
    int nextX[8] = {0,0,0,0,0,0,0,0};  
    int nextY[8] = {0,0,0,0,0,0,0,0};  
    //第一个位置赋值为1  
    board [startX] [startY] = 1;  
    int m,i,j;  
    //走完所有的点要循环63次  
    for ( m = 1; m < 64; m++){  
            //当前点其后面可行的位置设为0  
            next = 0;  
    //通过循环来判断该位置是否还可以向下面位置移动  
    for ( i =  0; i < 8; i++){  
        if(startX + moveX[i] < 0 || startX + moveX[i] >= ROWS  
            || startY + moveY[i] < 0 || startY + moveY[i] >= COLS  
            || board[startX+moveX[i]][startY+moveY[i]] != 0){  
                continue;  
            }  
            //如果可以向下一个位置移动的话，通过next数组保存下来，通过next记录下有多少个  
        nextX [next] = startX + moveX[i];  
        nextY [next] = startY + moveY[i];  
        next ++;  
    }  
    //循环结束之后，对next的值进行判断，当为1的时候  
    if (next == 1){  
        //让min=0，表示现在所需要的位置是在我们的保存next数组中的第一位  
        min = 0;  
    //设置初始点  
        goto set_nextpoint;  
    }  
    //无法向下一个位置移动了  
    else if (next == 0){  
        printf("没有路径可走了\n");  
        goto print_path;  
    }  
    else {  
            /*当有多个路径可以走的时候,检测每一个点还可不可以继续向下走然后 
            记录下来该点有几个点可以向下走，找到最少的一个但是不为0的哪一个 
            */  
        for (i = 0; i<next; i++){  
            nextNext = 0;  
            for(j = 0; j < 8; j++){  
                if(nextX[i] + moveX[j] >=0 && nextX[i] + moveX[j] < ROWS  
                    && nextY[i] + moveY[j] >= 0 && nextY[i] + moveY[j] <COLS  
                    && board [nextX[i]+moveX[j]][nextY[i]+moveY[j]] == 0){  
                        nextNext ++;  
                    }  
  
            }  
            nextNum[i] = nextNext;  
        }  
        if ((min = getMinPath(nextNum,next))>=0 )  
        {  
            goto set_nextpoint;  
        }  
        else{  
            printf("没有路径可走了\n");  
            goto print_path;  
        }  
    }  
set_nextpoint:  
        startX = nextX[min];  
        startY = nextY[min];  
        board[startX][startY] = m+1;  
    }  
print_path:  
    printPath(board);  
  
}  
int main (){  
    int i, j;  
    //获得最开始的位置  
    printf ("请输入第一个棋子所在位置\n");  
    scanf ("%d%d" , & i , & j);  
    printf("%d,%d",i,j);  
    //调用该函数获取路径  
    getPath(cheesboard, i, j);  
    return 0;  
}  
