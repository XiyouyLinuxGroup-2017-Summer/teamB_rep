/*************************************************************************
	> File Name: A.c
	> Author:九五二七 
	> Mail: 
	> Created Time: 2017年07月29日 星期六 16时50分13秒
 ************************************************************************/

#include<stdio.h>
int  dir[8][2]={{-1.-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1} };  //包含八个方向  
char gird[105][105];  // 
int  n,m;   //计数

void dfs(int x, int y)
{
    int xx,yy,i;
    gird[x][y] = '*';
    for (i=0; i < 8; i++){
        xx = x + dir[i][0];
        yy = y + dir[i][1];
        
        if (xx<0 || yy< 0|| xx>= m || yy >= n || gird[xx][yy] == '*'  )  continue;
        if (gird[xx][yy] == '@') {
            gird[xx][yy]='*';
            dfs(xx,yy);

        }
    }
}
int main ()
{
    int  i,j;
    int cnt=0;
    while( scanf ("%d %d",&m,&n),  m   ){
        cnt = 0;
        for (i=0;i<m;i++) {
            for(j=0;j<n;j++) {
                scanf(" %c", &gird[i][j]);
            }
        }
        
        for(i=0;i<m;i++)
            for(j=0; j<n; j++){
                if(gird[i][j] == '@')  
                {
                    dfs(i, j);
                    cnt++;
                }    
            }
    printf("%d\n",cnt);   
    }

}
