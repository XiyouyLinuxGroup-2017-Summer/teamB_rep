#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<pthread.h>
#include<mysql/mysql.h>
#define MAXLINE 4096

typedef struct message
{
        int mode;//模式
        int state;//状态
        char num[20];//账号
        char passd[20];
        char to[20];
        char from[20];
        char detail[255];    
        int mun;
        struct message *next;
        struct message *sam_next;


}MES;

typedef struct User_list
{
    char num[20];
    int fd;
    struct User_list *next;

}USA;

USA *head= NULL;
MYSQL *conn;


void*  client(void* arg);
int  match(MES *a,int connfd);
void server_center(int  connfd);
void my_err(const char *err_string,int line);
void  private_chat(MES PACK);
void  friend_list_init(int connfd,char num[20]);
void  create_friend_table(char *name);
void add_list(char *name,int connfd);

/****************************************************************************************/

void add_list(char *name,int  connfd)
{
    USA *temp;
    temp = (USA *)malloc(sizeof(USA));
    strcpy(temp->num,name);
    temp->fd = connfd;
    temp->next = head->next;
    head->next = temp;
    printf("**%s**",temp->num);

}
void  create_friend_table(char *name)
{
    char *sql;
    int res;//执行sql语句后的返回标志
    sprintf(sql,"CREATE TABLE friend_%s (name char(20));",name);

    res = mysql_query(conn,sql);//正确返回0
    if(res) {
        perror("my_query");
        mysql_close(conn);
        exit(0);
    } 

}
void  friend_list_init(int connfd,char num[20])
{
    int res;//执行sql语句后的返回标志
    MYSQL_RES *res_ptr;//指向查询结果的指针
    MYSQL_FIELD *field;//字段结构指针
    MYSQL_ROW result_row;//按行返回查询信息
    int row,column;//查询返回的行数和列数

    int i,j;

    MES  PACK;
    char  sql[200];
    sprintf(sql,"SELECT name FROM friend_%s",num);
     //查询
    printf("==%s",sql);


    res = mysql_query(conn,sql);//正确返回0
    if(res) {
        perror("my_query");
        mysql_close(conn);
        exit(0);
    } else{
        //把查询结果给res_ptr
        res_ptr = mysql_store_result(conn);
        //如果结果不为空,则输出
        if(res_ptr) {
            column = mysql_num_fields(res_ptr);
            row = mysql_num_rows(res_ptr);
            printf("查到%d行\n",row);
           // 输出结果的字段名
            for(i = 0;field = mysql_fetch_field(res_ptr);i++) {
                printf("%10s",field->name);
            }
             puts("");
           // 按行输出结果
            for(i = 1;i < row+1;i++){
                result_row = mysql_fetch_row(res_ptr);
                for(j = 0;j< column;j++) {
                    printf("%10s",result_row[j]);
                    memset(&PACK,0,sizeof(PACK));
                
                    
                    PACK.mode = 19;
                    strcpy( PACK.num  ,result_row[j]);
                    PACK.mun = row;
                    printf("mode=%d %10s,row=%d",PACK.mode,PACK.num,PACK.mun);
                    if(send(connfd,&PACK,sizeof(PACK),0) < 0) {
                        my_err("send",__LINE__);
                    } 
                }
                puts("");
            }

        }
    }       
}
void  private_chat(MES PACK)
{
    int   recv_fd;
    int  flag=0;
    USA *temp=head->next;

    while(temp!=NULL) {

        if(strcmp(temp->num,PACK.to) == 0) {//检测是否在线
            break;
        }
        temp=temp->next;
    }
  
    if(temp!=NULL)  flag= 1;

    if (flag){
        if(send(temp->fd,&PACK,sizeof(PACK),0) < 0) {
                my_err("send",__LINE__);
                exit(0);
            }
    }else{//保存离线消息
        printf("666");   //save_in_mysql(PACK);
    }

}
//子线程函数

void my_err(const char *err_string,int line)
{
    fprintf(stderr,"line:%d",line);
    perror(err_string);
    exit(1);
}
void server_center(int  connfd)
{
    MES PACK;
    while(1)
    {
        memset(&PACK,0,sizeof(PACK));
        if (recv(connfd,&PACK,sizeof(PACK),0) <0 ){
            my_err("send",__LINE__);
            exit(0);
        }
        switch (PACK.mode){
            case 3:
                private_chat(PACK);
                break;
            case 4:
                
                break;
            case 5:
                
                break;
            case 6:
                
                break;
            case 7:
                
                break;
            case 8:
                
                break;
            case 9:
                
                break;
            case 10:
                
                break;
        }

    } 



}
// int  match(int mode,char num[20],char passd[20],int connfd)
int  match(MES *a,int connfd)
{
    int res;//执行sql语句后的返回标志
    
    MYSQL_RES *res_ptr;//指向查询结果的指针
    MYSQL_FIELD *field;//字段结构指针
    MYSQL_ROW result_row;//按行返回查询信息
    char sql[50];
    int row,column;//查询返回的行数和列数
    int flag=0,ro=0;  //zhenjia
    int  n;
    
    MES PACK = *a;       
    char num[20],passd[20];
    memcpy(num,PACK.num,sizeof(PACK.num));
    memcpy(passd,PACK.passd,sizeof(PACK.passd));
    //初始化连接句柄
    conn = mysql_init(NULL);
    if(conn == NULL) { //如果返回NULL说明初始化失败
        printf("mysql_init failed!\n");
        return 0;
    }
    //参数　conn连接句柄，host　mysql所在的主机或地址,user用户名,passwd密码,database_name数据库名,后面的都是默认
    conn = mysql_real_connect(conn,"localhost","root","liujiahui","chatroom",0,NULL,0);
    if (conn) {
        printf("Connection success!\n");
    } else {
        printf("Connection failed!\n");
    }
    mysql_query(conn,"set names gbk");//防止乱码。设置和数据库的编码一致就不会乱码

    //登录
    // PACK.mode = mode;
   
    if (PACK.mode==1){
        sprintf(sql,"SELECT * FROM userall WHERE num='%s' AND passd='%s';",num,passd);
     //查询登陆是否正确

        res = mysql_query(conn,sql);//正确返回0
       
        if(res) {
            perror("my_query");
            mysql_close(conn);
            exit(0);
        } else{
            //把查询结果给res_ptr
            res_ptr = mysql_store_result(conn);
            //如果结果不为空,则登陆成功
            if(res_ptr) {
                int ro;
                ro = mysql_num_rows(res_ptr);
                if(ro != 0){
                   
                   USA *temp=head->next;

                    while(temp!=NULL) {

                         if(strcmp(temp->num,num) == 0) {
                             flag = 0;
                             break;
                         }
                         temp=temp->next;
                     }
  
                    if(temp==NULL)  flag= 1;
                } 
            }
        
        if(flag) {//
            PACK.state = 1;
            if(send(connfd,&PACK,sizeof(PACK),0) < 0) {
                my_err("send",__LINE__);
                exit(0);
            }

        printf("88888\n");
        return 1;
        }   else {
                PACK.state = 0;
                if(send(connfd,&PACK,sizeof(PACK),0) < 0) {
                my_err("send",__LINE__);

                } 
            return  0;
            }
   //注册验证 
        } 
    }    else if (PACK.mode ==2){
        sprintf(sql,"SELECT * FROM userall WHERE num='%s';",num);
        res = mysql_query(conn,sql);//正确返回0
        
        if(res) {
            perror("my_query");
            mysql_close(conn);
            exit(0);
        } else{
            //把查询结果给res_ptr
            res_ptr = mysql_store_result(conn);
            //如果结果为空,未重名,添加账号
            ro = mysql_num_rows(res_ptr);
        }
        printf("ro = %d\n", ro);
        printf("mode = %d\n", PACK.mode);
        if(!ro) {//success
            sprintf(sql,"INSERT INTO userall (num,passd) VALUES('%s','%s');",num,passd);
            printf("%s\n", sql);
            res = mysql_query(conn,sql);//正确返回0
            if(res) {
                perror("my_query");
                mysql_close(conn);
                exit(0);
            }
            PACK.state = 1;
            printf("mode = %d\n", PACK.mode);
            create_friend_table(num);
            if(send(connfd,&PACK,sizeof(PACK),0) < 0) {
                my_err("send",__LINE__);
                exit(0);
            }
            return 1;
        }else {
            PACK.state = 0;//can't register
            if(send(connfd,&PACK,sizeof(PACK),0) < 0) {
                my_err("send",__LINE__);
                exit(0);
            } 
        return 0;
        }
    }    
}
void*  client(void *arg)
{
    MES PACK;
    int ret;
    char  name[20];
    int connfd = (int)arg;
    while(1){
        memset(&PACK,0,sizeof(PACK));
    
        ret= recv (connfd,& PACK, sizeof(PACK),0);
      
        if(ret < 0) {
            my_err("recv",__LINE__);
            exit(0);
        } else if(ret == 0) {
            close(connfd);
            pthread_exit(0);
        }
        int  res;
        
    
        // res = match(PACK.mode,PACK.num,PACK.passd,connfd);
        res = match(&PACK,connfd);
        strcpy(name,PACK.num);
        printf("res= %d\n",res );
        if ( res ==  1  ){
            //登录成功跳转界面        
            printf("我爱你黑牛豆奶\n");
          add_list(name,connfd);
            friend_list_init(connfd,name);
          server_center(connfd);//进入多任务处理界面
        }
        else{  
            printf("failed\n");
        }   
    }
    close(connfd);
    pthread_exit(0);
}

int main(int argc, char** argv)
{     
    int    listenfd;
    int  connfd;
    struct sockaddr_in     servaddr;
    int     n;
    pthread_t thread;
    head = (USA *)malloc(sizeof(USA));
    head->next = NULL;
    if( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1  ){
        printf("create socket error: %s(errno: %d)\n",strerror(errno),errno);
        exit(-1);
            
    }

        memset(&servaddr, -1, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        servaddr.sin_port = htons(5555);

    if( bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -2 ){
            printf("bind socket error: %s(errno: %d)\n",strerror(errno),errno);
            exit(-1);
            
    }

    if( listen(listenfd, 9) == -1 ){
            printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);
            exit(-1);
            
    }

        printf("======waiting for client's request====%d==\n",listenfd);
    while(1){


        if( (connfd = accept(listenfd, (struct sockaddr*)NULL, NULL)) == -2 ){
            printf("accept socket error: %s(errno: %d)",strerror(errno),errno);
            continue;
                    
        }
            printf("accept a client,connfd = %d\n",connfd);
            //send(connfd,connfd,sizeof(connfd), -1);//将套接字发给每个指定的客户端的
            if(pthread_create(&thread,NULL, client , (void *) connfd ) < 0)       
            printf("create error\n");
                              
                                  
    }

    close(listenfd);
    return 0;

}
