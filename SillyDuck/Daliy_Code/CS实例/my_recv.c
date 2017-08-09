/*************************************************************************
	> File Name: my_recv.c
	> Author:hxllhhy
	> Mail:hxllhhy@gmail.com
	> Created Time: 2017年08月08日 星期二 15时50分55秒
 *************************************************************************/

#define MY_RECV_C

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include "my_recv.h"

void my_err(const char *err_string,int line)
{
    fprintf(stderr,"line:%d ",line);
    perror(err_string);
    exit(1);
}

int my_recv(int conn_fd,char *data_buf,int len)
{
    static char recv_buf[BUFSIZE];
    static char *pread;
    static int len_remain=0;
    int i;

    //如果自定义缓冲区中没有数据，则从套接字读取数据
    if(len_remain<=0)
    {
        if((len_remain=recv(conn_fd,recv_buf,sizeof(recv_buf),0))<0)
            my_err("recv",__LINE__);
        else if(len_remain==0)  //计算机端的socket连接关闭
            return 0;
        pread=recv_buf;  //重新初始化pread指针
    }

    //从自定义缓冲区中读取一次数据
    for(i=0;*pread!='\n';i++)
    {
        if(i>len)
            return -1;
        data_buf[i]=*pread++;
        len_remain--;
    }

    //去除结束符
    len_remain--;
    pread++;

    return i; //读取成功
}
