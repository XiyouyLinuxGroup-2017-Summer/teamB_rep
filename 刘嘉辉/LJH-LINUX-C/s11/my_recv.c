/*************************************************************************
	> File Name: my-recv.c
	> Author:九五二七 
	> Mail: 
	> Created Time: 2017年08月08日 星期二 17时24分58秒
 ************************************************************************/
#define    MY_RECV_C

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include"my_recv.h"
#include<stdlib.h>
//
void  my_err (const char  *err_string, int  line)
{
    fprintf(stderr, "line:%d", line);
    perror (err_string);
    exit(1);
}

//my_recv   
//conn_fd  从该连接套字上接收数据
//date_buf 读取到的数据般存在此缓存中
//len -  date_buf  空间长度
//返回值  出错 返回-1  服务器端已关闭连接则返回0， 成功返回读取的字节数
int  my_recv(int conn_fd , char *date_buf, int  len  )
{
    static char  recv_buf[BUFSIZE];
    static char  *pread;      //指向下一次读取数据的位置
    static int  len_remain = 0;  // 自定义缓冲区 剩余字节数
    int           i;
    //如果自定义 缓冲区 没有数据   则从套接字  读取数据
    if (len_remain <= 0){
        if ((len_remain = recv (conn_fd, recv_buf, sizeof(recv_buf), 0))  < 0  ){
            my_err("recv", __LINE__ );
        }  else if ( len_remain ==  0 )   //目的计算机的socket连接关闭
                return  0;
        pread = recv_buf;    //重新初始化pread指针
    }
    // 从自定义缓冲区中读取一次数据
    for (i =0 ; *pread != '\n'; i++)
    {
        if (i > len )    return  -1;
        date_buf[i] = *pread++;
        len_remain--;
    }
    //去除结束标志
    len_remain--;
    pread++;

    return i;  //读取成功


}
