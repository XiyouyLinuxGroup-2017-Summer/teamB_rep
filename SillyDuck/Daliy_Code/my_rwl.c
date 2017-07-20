/*************************************************************************
	> File Name: my_rwl.c
	> Author:hxllhhy
	> Mail:hxllhhy@gmail.com
	> Created Time: 2017年07月19日 星期三 16时45分32秒
 ************************************************************************/

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

//自定义错误处理函数
void my_err(const char *err_string,int line)
{
    fprintf(stderr,"line:%d ",line);  //标准错误输出
    perror(err_string);  //输出错误原因
    exit(1);
}

//自定义读数据函数
int my_read(int fd)
{
    int len;
    int ret;
    int i;
    char read_buf[64];

    //获取文件长度并保持文件读写指针在文件开始处
    if(lseek(fd,0,SEEK_END)==-1)  //将文件读写指针移动到文件末尾，有错误返回-1
    {
        my_err("lseek",__LINE__);  //调用错误处理函数，定位错误
    }
    if((len=lseek(fd,0,SEEK_CUR))==-1)  //获取文件读写指针的当前位置
    {
        my_err("lseek",__LINE__);  //__LINE__为预编译器内置宏，表示行数
    }
    if(lseek(fd,0,SEEK_SET)==-1)  //将文件读写指针移动到文件开头
    {
        my_err("lseek",__LINE__);
    }

    printf("len:%d\n",len);  //打印文件长度

    //读数据
    if((ret=read(fd,read_buf,len))<0)  //调用read函数
    {
        my_err("read",__LINE__);
    }

    //打印数据
    for(i=0;i<len;i++)
        printf("%c",read_buf[i]);
    printf("\n");

    return ret;  //ret为实际读到字节数
}
int main()
{
    int fd;
    char write_buf[32]="Hello World!";

    //在当前目录下创建文件example_2.c
    //if((fd=creat("example_2.c",S_IRWXU))==-1)
    if((fd=open("example_2.c",O_RDWR|O_CREAT|O_TRUNC,S_IRWXU))==-1)
    {
        my_err("open",__LINE__);
    }
    else
    {
        printf("create file success\n");
    }

    //写数据
    if(write(fd,write_buf,strlen(write_buf))!=strlen(write_buf))
    //返回值与写入字节数不相等，有错误发生
    {
        my_err("write",__LINE__);
    }
    my_read(fd);  //调用自定义读数据函数

    //演示文件的间隔
    printf("————————————————————————————————————————————\n");
    if(lseek(fd,10,SEEK_END)==-1)  //文件偏移量被设置为文件长度12+10，即22
    {
        my_err("lseek",__LINE__);
    }
    if(write(fd,write_buf,strlen(write_buf))!=strlen(write_buf))
    //在文件第23个字节处开始再写12个字节
    {
        my_err("write",__LINE__);
    }
    my_read(fd);  //读了共34个字节长度

    close(fd);
    return 0;
}
