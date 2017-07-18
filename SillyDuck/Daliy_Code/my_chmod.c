/*************************************************************************
	> File Name: my_chmod.c
	> Author:hxllhhy
	> Mail:hxllhhy@gmail.com
	> Created Time: 2017年07月18日 星期二 21时47分15秒
 ************************************************************************/

#include<stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>  //基本系统数据类型
#include <sys/stat.h>   //文件状态

int main(int argc,char **argv) 
{
    int mode;     //权限
    int mode_u;   //所有者user的权限
    int mode_g;   //所属组group的权限
    int mode_o;   //其他用户other的权限
    char *path;

    if(argc<3)
    {
        printf("%s <mode num> <target file>\n",argv[0]);
        //argv[0]指向输入的程序路径及名称
        exit(0);
        //正常运行并退出程序，０返回给操作系统
    }

    //获取命令行参数
    //atoi()函数：将字符串转化为int类型变量
    mode=atoi(argv[1]);
    if(mode>777||mode<0)
    {
        printf("mode num error!\n");
        exit(0);     
    }
    mode_u=mode/100;
    mode_g=mode/10%10;
    mode_o=mode%10;
    mode=(mode_u*8*8)+(mode_g*8)+mode_o;   //八进制转换
    path=argv[2];


    //int chmod(const char * path, mode_t mode)
    //函数说明：chmod()会依参数mode权限来更改参数path指定文件的权限
    //更改失败返回-1
    if(chmod(path,mode)==-1)
    {
        perror("chmod error");
        //perror()是错误输出函数，在标准输出设备上输出一个错误信息
        exit(1);  
        //非正常运行并退出程序
    }
    return 0;
}
