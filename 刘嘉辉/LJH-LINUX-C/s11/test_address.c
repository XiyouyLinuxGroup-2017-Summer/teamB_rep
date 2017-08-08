/*************************************************************************
	> File Name: test_address.c
	> Author:九五二七 
	> Mail: 
	> Created Time: 2017年08月08日 星期二 09时04分20秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main ()
{
    char  buffer[32];
    int   ret = 0;
    int   host = 0;
    int   network = 0;
    unsigned address = 0;
    struct  in_addr  in;
    in.s_addr = 0;   //唯一元素

    //输入一个以.分割字符字符串的IP地址
    printf("please input  your  ip address: \n");
        fgets(buffer, 31, stdin);
    buffer[31] = '\0';


    //实例使用inet_aton
    if ((ret = inet_aton(buffer, &in)) == 0 ) {//  buffer   到in中二进制网络字节序0
        printf("inet_aton: \t invaild address\n");
    }else
        printf("inet_aton: \t 0x%x\n ", in.s_addr);
    //使用inet_addr()     已过时  不能识别255。255。255.255
    if ((address = inet_addr(buffer)) == INADDR_NONE){
        printf("inet_addr :\t invaild address\n");
    }else 
        printf("inet_addr :\t0x%lx\n",address);
    //使用inet_network  
    if((address = inet_network( buffer)) == -1) {
        printf("inet_network :\t invaild address\n");
    } else 
        printf("inet_network :\t0x%lx\n",address);
    //示例使用in_lnaof() 与inet_netof函数
    host = inet_lnaof(in);  //从in中提取出主机地址   提取进制后两个点点
    network = inet_netof(in); //           提取网络地址   前两个点点          
    printf("inet_lnaof:0x%x\n", host);
    printf("inet_netof:\t0x%x\n", network);

    in = inet_makeaddr(network, host);   //将network与host两个地址组合为一个网络地址
    printf("inet_makeaddr:0x%x\n", in.s_addr);

    return 0;

}
