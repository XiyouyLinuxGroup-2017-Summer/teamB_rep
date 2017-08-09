/*************************************************************************
	> File Name: select.c
	> Author:九五二七 
	> Mail: 
	> Created Time: 2017年08月08日 星期二 10时57分57秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/time.h>
#include<unistd.h>
#include<time.h>

void display_time(const char *string)
{
    int     seconds;

    seconds = time((time_t *) NULL);//获取从1970 1 1 0 0 0 到此刻算起所经历过的秒数
    printf("%s, %d\n", string, seconds);
}

int main(void)
{
    fd_set      readfds;  //fd 是一个结构体 
    /*    typedef  struct fd_set {
              u_int fd_count;   集合中的套接的数量 
              SOCKET fd_array [FD_SETSIZE];    //集合中的一组套接字
             } fd_set;
    */
  //  struct    timeval   timeout;
    int         ret;
    
    //监视文件描述符0  是否有数据输入 ，文件描述符0表示标准输入 
    FD_ZERO(&readfds);//开始使用的一个文件描述符集合 前一般要将其清空
    FD_SET(0, &readfds);

    //设置阻塞时间为10秒

   // timeout.tv_sec = 10;
   // timeout.tv_usec = 0;    //微秒

    while(1)
    {
    struct    timeval   timeout;
    timeout.tv_sec = 10;        //初始化放在里边就是正确的计时
    timeout.tv_usec = 0;    //微秒
        display_time ("before select");

        ret = select(1,&readfds, NULL,NULL, &timeout); //监视数为1   可写文件描述符集合为null  异常文件描述符也为null；
        display_time ("after  select");
        
        switch(ret){
            case 0://都没有事件发生
                printf("NO date in ten seconds\n");
                exit(0);
                break;
            case -1://发生错误
                perror("select");
                exit(0);
                break;
            default :  // 成功状态
                getchar();   // 将数据读入  否则标准输入上一直为读就绪
                printf("Date is  available now .\n ");
        }
    }
    
    return 0;

}
