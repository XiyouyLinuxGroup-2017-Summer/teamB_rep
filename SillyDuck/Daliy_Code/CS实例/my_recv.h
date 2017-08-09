/*************************************************************************
	> File Name: my_recv.h
	> Author:hxllhhy
	> Mail:hxllhhy@gmail.com
	> Created Time: 2017年08月08日 星期二 15时46分49秒
 ************************************************************************/

#ifndef _MY_RECV_H
#define _MY_RECV_H
    #define BUFSIZE 1024
    void my_err(const char *err_string,int line);
    int my_recv(int conn_fd,char *data_buf,int len);
#endif
