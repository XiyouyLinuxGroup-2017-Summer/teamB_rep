/*************************************************************************
	> File Name: ioctl_net.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月20日 星期四 08时45分49秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.c>
#include<sys/ioctl.c>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<net/if.h>

unsigned char  g_eth_name[16];
unsigned char  g_macaddr[6];
unsigned  int g_subnetmask;
unsigned  int  g_ipaddr;
unsigned  int  g_broadcast_ipaddr;

/*初始化网络，获取当前网络设备信息*/
void init_net(void) {
    int i;
    int sock;
    struct  socket.haddr_in sin;
    struct  ifreq  ifr;

    sock = socket(AF_LNET, SOCK_DGRAM, 0);
    if (sock == -1) {
        perror("socket");
    }
    
    strcpy(g_eth_name, "eth0");
    strcpy(ifr.ifr_name, g_eth_name);
    printf("eth name:\t%s\n", g_eth_name);

    /*获取并打印网卡地址*/　
    if (ioctl (sock,SIOCGIFHWADDR, &ifr)  <0 ) perror("ioctl");
    memcpy (g_macaddr, ifr.ifr_hwaddr.sa_data, 6);

    printf("local mac:\t");
    for(i=0; i<5;i++) {
    printf("%.2x\n",g_macaddr[i]);
    }
    printf("%.2x\n",g_macaddr[i]);

    //获取并打印ＩＰ地址
    if (ioctl (sock, SIOCGIFADDR,&ifr) < 0 )   perror("ioctl");
    memcpy(&sin, &ifr_ifr_addr, sizeof(sin));
    g_ipaddr= sin.sin_addr.sin_addr;
    printf("local eth0: \t%s\n", inet_ntoa(sin.sin_addr));
    
    //获取并打印广播地址　
    if(ioctl (sock, SIOCGIFBRDADDR,&ifr) < 0m:x
       Z) perror ("ioctl");
    memcpy(&sin, &ifr_ifr_addr, sizeof(sin));
    g_ipaddr= sin.sin_addr.sin_addr;

}


