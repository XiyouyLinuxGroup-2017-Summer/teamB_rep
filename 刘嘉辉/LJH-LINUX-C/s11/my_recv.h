/*************************************************************************
	> File Name: my_recv.h
	> Author:九五二七 
	> Mail: 
	> Created Time: 2017年08月08日 星期二 17时43分58秒
 ************************************************************************/

#ifndef _MY_RECV_H
#define _MY_RECV_H
    #define  BUFSIZE    1024
    void  my_err(const char *err_string, int  line);
    int  my_recv(int  conn_fd, char  *date_buf ,int  len );
#endif
