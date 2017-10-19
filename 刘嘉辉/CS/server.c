//刘嘉辉的微信聊天 
//2017 8 17 23:36完成



#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<pthread.h>
#include<mysql/mysql.h>
#define MAXLINE 4096
//切记两边的结构体要完全相同！！！！！！！！！！！！！！！！！！！！！！！！
typedef struct message
{
        int mode;//模式
        int state;//状态
        char num[20];//账号
        char passd[20];
        char mem_name[20];//群成员姓名
        char host[20];
        char to[20];
        char from[20];
        char detail[255];//消息内容    
        char  time_mes[100];
        int mun;


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
void  friend_list_init(int connfd);
void  create_friend_table(char *name);
void add_list(char *name,int connfd);
void logout(int connfd);//退出登陆
void    del_fd(int   connfd);//将次节点从登录链表中删除
void  save_in_mysql(MES PACK);//保存离线消息
void  leave_mess(int connfd,char * name);//离线消息的处理
int  search_friend(char * num);// 在数据库中查找是否有这个用户
int  online_fri(char* num); //根据用户ID号进性查询好友是否在线  
void delete_member(char *group_name,char *mem_name);
void  select_message_log(MES PACK,int connfd);
void   save_message_log (MES PACK);//保存聊天记录
void  create_message_log(char *fri_1,char *fri_2);  //添加好友成功时 创建聊天记录表
void  group_friend_append(char*from,char *name);//添加好友信息至数据库中   
void  group_create_mes_log(char *from,char *name);//创建聊天记录的表格
void  group_chat(MES PACK);//处理群消息 
void  show_group_member (int connfd,char *group_name);//群成员展示
/****************************************************************************************/

void add_list(char *name,int  connfd)
{
    USA *temp;
    temp = (USA *)malloc(sizeof(USA));
    strcpy(temp->num,name);
    temp->fd = connfd;
    temp->next = head->next;
    head->next = temp;
    printf("**%s**\n",temp->num);

}
void  create_friend_table(char *name)
{
    char sql[200] ;
    int res;//执行sql语句后的返回标志
    sprintf(sql,"CREATE TABLE friend_%s (name varchar(20));",name);
    printf("注册账户成功  sql = %s\n",sql);
    res = mysql_query(conn,sql);//正确返回0
    if(res) {
        perror("my_query");
        mysql_close(conn);
        exit(0);
    } 

}
char *select_name(int fd)
{
    USA *temp;
    temp = head->next;
    while(temp != NULL)
    {
        if (fd == temp->fd) break;
    temp = temp->next;
    }
    return temp->num;


}
void  friend_list_init(int connfd)//发送好友列表
{
    int res;//执行sql语句后的返回标志
    MYSQL_RES *res_ptr;//指向查询结果的指针
    MYSQL_FIELD *field;//字段结构指针
    MYSQL_ROW result_row;//按行返回查询信息
    int row,column;//查询返回的行数和列数
    char num[20];
    int i,j;

    MES  PACK;
    char  sql[200];
    
    //根据fd去链表查名字

     strcpy (num , select_name(connfd));
    
    sprintf(sql,"SELECT name FROM friend_%s",num);
     //查询


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
           // 输出结果的字段名
             puts("");
           // 按行输出结果
            for(i = 1;i < row+1;i++){
                result_row = mysql_fetch_row(res_ptr);
                for(j = 0;j< column;j++) {
                    memset(&PACK,0,sizeof(PACK));
                
                    
                    PACK.mode = 19;
                    strcpy( PACK.num  ,result_row[j]);
                    
                    PACK.mun = row;
                    if(send(connfd,&PACK,sizeof(PACK),0) < 0) {
                        my_err("send",__LINE__);
                    } 
                }
                puts("");
            }

        }
    }       
}
void  group_list_init(int connfd)//发送QUN列表
{
    int res;//执行sql语句后的返回标志
    MYSQL_RES *res_ptr;//指向查询结果的指针
    MYSQL_FIELD *field;//字段结构指针
    MYSQL_ROW result_row;//按行返回查询信息
    int row,column;//查询返回的行数和列数
    char num[20];
    int i,j;

    MES  PACK;
    char  sql[200];
    
    //根据fd去链表查名字

    strcpy (num , select_name(connfd));
    

    sprintf(sql,"SELECT * FROM my_group_%s",num);
     //查询


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
                printf("column = %d\n",column);
                
                    printf("%s %s\n",result_row[0],result_row[1]);
                    memset(&PACK,0,sizeof(PACK));
                
                    
                    PACK.mode = 18;
                    strcpy( PACK.num  ,result_row[0]);
                    strcpy(PACK.host, result_row[1]);
                   // printf("mode = %d, group_name = %s, row = %d\n",PACK.mode, PACK.num, row);    
                    if(send(connfd,&PACK,sizeof(PACK),0) < 0) {
                        my_err("send",__LINE__);
                    } 
                }
                puts("");
            }

        }
}       

void  show_group_member (int connfd,char *group_name)//群成员展示
{
    int res;//执行sql语句后的返回标志
    MYSQL_RES *res_ptr;//指向查询结果的指针
    MYSQL_FIELD *field;//字段结构指针
    MYSQL_ROW result_row;//按行返回查询信息
    int row,column;//查询返回的行数和列数
    char num[20];
    int i,j;

    MES  PACK;
    char  sql[200];
    
    //根据fd去链表查名字

     strcpy (num , select_name(connfd));
    
    sprintf(sql,"SELECT name FROM group_%s",group_name);
     //查询


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
           // 输出结果的字段名
             puts("");
           // 按行输出结果
            for(i = 1;i < row+1;i++){
                result_row = mysql_fetch_row(res_ptr);
                for(j = 0;j< column;j++) {
                    memset(&PACK,0,sizeof(PACK));
                
                    
                    PACK.mode = 17;
                    strcpy( PACK.mem_name ,result_row[j]);
                    
                    PACK.mun = row;
                    if(send(connfd,&PACK,sizeof(PACK),0) < 0) {
                        my_err("send",__LINE__);
                    } 
                }
                puts("");
            }

        }
    }       


}
void  group_dismiss(char *group_name,char *from,char *to )//解散群
{
     int res;//执行sql语句后的返回标志
    MYSQL_RES *res_ptr;//指向查询结果的指针


    char  sql[300];
    sprintf(sql,"drop table group_%s;",group_name);
    res = mysql_query(conn,sql);//正确返回0
    res_ptr = mysql_store_result(conn);

    
    sprintf(sql,"delete from my_group_%s  where name = '%s';",from,to);
    res = mysql_query(conn,sql);//正确返回0
    res_ptr = mysql_store_result(conn);
    memset(&sql,0,sizeof(sql));


    printf("delete  group \n");



}



void  leave_mess(int  connfd,char *name )//离线消息的处理
{
    int res;//执行sql语句后的返回标志
    MYSQL_RES *res_ptr;//指向查询结果的指针
    MYSQL_FIELD *field;//字段结构指针
    MYSQL_ROW result_row;//按行返回查询信息
    int row,column;//查询返回的行数和列数

    int i,j;

    MES  PACK;
    char  sql[200];
    sprintf(sql,"SELECT *  FROM offline_mes where ot = '%s';",name);
     //查询
    printf("==%s\n",sql);


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
   //             printf("column = %d\n",column);
                    memset(&PACK,0,sizeof(PACK));
                
                PACK.mode = atoi( result_row[0]);
                PACK.state = atoi(result_row[1]);
                strcpy( PACK.from,result_row[2]);
                strcpy(PACK.to , result_row[3]);
                strcpy(PACK.detail,result_row[4]);
 //               printf("%d,%d,%s,%s,%s\n " ,PACK.mode,PACK.state,PACK.from,PACK.to,PACK.detail); 
                
                     if(send(connfd,&PACK,sizeof(PACK),0) < 0) {
                         my_err("send",__LINE__);
                    } 
                puts("");
            }

        }
    }       
}
void  save_in_mysql(MES PACK)//保存离线消息
{
    int res;//执行sql语句后的返回标志
    MYSQL_RES *res_ptr;//指向查询结果的指针


    char  sql[3000];
    sprintf(sql,"INSERT INTO offline_mes  VALUES(%d,%d,'%s','%s','%s');",PACK.mode,PACK.state,PACK.from,PACK.to,PACK.detail);
    res = mysql_query(conn,sql);//正确返回0
    res_ptr = mysql_store_result(conn);
//    printf("==%s",sql);
}
void   save_message_log (MES PACK)//保存聊天记录
{
   
    int res;//执行sql语句后的返回标志
    MYSQL_RES *res_ptr;//指向查询结果的指针
    char  time_mes[20];
    time_t   timep;   
    time   (&timep);   
    //ctime(&timep);
    strcpy(time_mes, ctime(&timep));
    char  sql[200];
    sprintf(sql,"INSERT INTO %s_to_%s  VALUES('%s','%s','%s');",PACK.from,PACK.to, PACK.from,PACK.detail,time_mes);
    
    
    
    res = mysql_query(conn,sql);//正确返回0
    res_ptr = mysql_store_result(conn);
    printf("==%s",sql);
    
    memset(&sql,0,sizeof(sql));
    sprintf(sql,"INSERT INTO %s_to_%s  VALUES('%s','%s','%s');",PACK.to,PACK.from, PACK.from,PACK.detail,time_mes);
    res = mysql_query(conn,sql);//正确返回0
    res_ptr = mysql_store_result(conn);
  //  printf("==%s",sql);


}


void  private_chat(MES PACK)//私聊处理哦
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
        
          printf("在线消息\n");   
        // 保存聊天记录
        
        save_message_log(PACK);

        if(send(temp->fd,&PACK,sizeof(PACK),0) < 0) {
                my_err("send",__LINE__);
                exit(0);
            }
    }else{//保存离线消息
          printf("离线消息\n");   
          save_in_mysql(PACK);
    }

}
//子线程函数

void my_err(const char *err_string,int line)
{
    fprintf(stderr,"line:%d",line);
    perror(err_string);
    exit(1);
}
int  search_friend(char * num)// 在数据库中查找是否有这个用户
{
    int res;//执行sql语句后的返回标志
    MYSQL_RES *res_ptr;//指向查询结果的指针
    MYSQL_FIELD *field;//字段结构指针
    MYSQL_ROW result_row;//按行返回查询信息
    int row,column;//查询返回的行数和列数

    char  sql[200];
    sprintf(sql,"SELECT * FROM userall WHERE num='%s';",num);

     //查询
   // printf("==%s",sql);
    res = mysql_query(conn,sql);//正确返回0
    if(res) {
        perror("my_query");
        mysql_close(conn);
        exit(0);
    } else{
        //把查询结果给res_ptr
        res_ptr = mysql_store_result(conn);
            row = mysql_num_rows(res_ptr);
        //如果结果不为空,则
        if(row) {
            return 1;//找到
        }else {
            return 0;//查无此人
        }    
    }    

}
int  online_fri(char* num)//根据用户ID号进性查询好友是否在线并返回套接字
{
    USA *temp=head->next;

    while(temp!=NULL) {
        if(strcmp(temp->num,num) == 0) {
        return  temp->fd;  //在线
    }
        temp=temp->next;
    }
  
    if(temp==NULL)  return 0;   //不在线
}
void friend_append(char*fri_1 ,char*fri_2 )//添加好友的处理
{
    int res;//执行sql语句后的返回标志
    MYSQL_RES *res_ptr;//指向查询结果的指针


    char  sql[200];
    sprintf(sql,"INSERT INTO friend_%s  VALUES('%s');",fri_1,fri_2);
    res = mysql_query(conn,sql);//正确返回0
    res_ptr = mysql_store_result(conn);
  //  printf("==%s",sql);
    
    memset(&sql,0,sizeof(sql));
    sprintf(sql,"INSERT INTO friend_%s  VALUES('%s');",fri_2,fri_1);
    res = mysql_query(conn,sql);//正确返回0
    res_ptr = mysql_store_result(conn);
  //  printf("==%s",sql);

}
void  create_message_log(char *fri_1,char *fri_2)//添加好友后创建聊天记录的表格
{

    int res;//执行sql语句后的返回标志
    MYSQL_RES *res_ptr;//指向查询结果的指针

    char  sql[200];
    sprintf(sql,"create table  %s_to_%s  (name varchar(20),detail varchar(255),time  varchar(100) );",fri_1,fri_2);

    res = mysql_query(conn,sql);//正确返回0
    res_ptr = mysql_store_result(conn);
  //  printf("==%s",sql);
    
    memset(&sql,0,sizeof(sql));
    sprintf(sql,"create table  %s_to_%s  (name varchar(20),detail varchar(255),time  varchar(100) );",fri_2,fri_1);
    res = mysql_query(conn,sql);//正确返回0
    res_ptr = mysql_store_result(conn);
  //  printf("==%s",sql);

}

void search_friend_add(MES PACK)//对添加好友请求而的处理的函数
{
    int  to_fd,from_fd;
    to_fd = online_fri(PACK.to);
    from_fd = online_fri(PACK.from);
    if (search_friend(PACK.to) ){ //判断用户是否存在 
        if(to_fd){                //判断用户是否在线
           if ( PACK.state == -1)  printf("&&&& mode= %d",PACK.mode );    
            if(PACK.state ==0) ;
            if (PACK.state ==1){
                printf("添加账号\n");
                friend_append(PACK.from,PACK.to);//添加好友信息至数据库中               
                create_message_log(PACK.from,PACK.to);//创建聊天记录的表格
                printf("已添加至数据库中\n");      
            }
            
            if(send(to_fd,&PACK,sizeof(PACK),0) < 0) { 
                my_err("send",__LINE__);
                exit(0);
            }
        } else//保存为离线消息
            save_in_mysql(PACK);

    }else{                             
        PACK.state = -2;//该用户不存在    
        printf(" state = %d\n",PACK.state );     
        if(send(from_fd,&PACK,sizeof(PACK),0) < 0) { ///**************这个send有问题啊***********************************``
            my_err("send",__LINE__);
            exit(0);
        }
    }
}

void  group_friend_append(char* from,char *group_name)//添加好友至群列表中  
{
    int res;//执行sql语句后的返回标志
    MYSQL_RES *res_ptr;//指向查询结果的指针


    char  sql[200];
    sprintf(sql,"INSERT INTO  group_%s  VALUES ('%s');",group_name,from);

    res = mysql_query(conn,sql);//正确返回0
 
    res_ptr = mysql_store_result(conn);
   // printf("==%s",sql);


}

void  group_create_mes_log(char* from,char* group_name)//为此成员创建群聊天记录的表格
{
    int res;//执行sql语句后的返回标志
    MYSQL_RES *res_ptr;//指向查询结果的指针


    char  sql[200];
    sprintf(sql,"create table  %s_group_%s  (name varchar(20),detail varchar(255),time  varchar(100) );",group_name,from);

    res = mysql_query(conn,sql);//正确返回0
    res_ptr = mysql_store_result(conn);
  //  printf("==%s",sql);


}
void group_create_table(char* from,char* group_name) // 创建群成员表格 并将群主加入表内
{
    int res;//执行sql语句后的返回标志
    MYSQL_RES *res_ptr;//指向查询结果的指针


    char  sql[200];
    sprintf(sql,"create table  group_%s  (name varchar(20));",group_name);

    res = mysql_query(conn,sql);//正确返回0
    res_ptr = mysql_store_result(conn);
   // printf("==%s",sql);
    
    res_ptr =NULL;
    
    memset(sql, 0, sizeof(sql));
    
    sprintf(sql,"INSERT INTO  group_%s  VALUES('%s');",group_name,from);
    res = mysql_query(conn,sql);//正确返回0
    res_ptr = mysql_store_result(conn);
 //   printf("==%s",sql);


    memset(sql, 0, sizeof(sql));
    sprintf(sql,"INSERT INTO  my_group_%s  VALUES('%s','%s');",from,group_name,from);
    res = mysql_query(conn,sql);//正确返回0
    res_ptr = mysql_store_result(conn);
  //  printf("==%s",sql);

    memset(sql, 0, sizeof(sql));
    sprintf(sql,"create table message_group_%s  (name varchar(20), detail varchar(20), time  varchar(100));",group_name);
    res = mysql_query(conn,sql);//正确返回0
    res_ptr = mysql_store_result(conn);

}


void my_group_append(char *from,char *group_name,char *to )//将此群添加至我的群列表中
{

    int res;//执行sql语句后的返回标志
    MYSQL_RES *res_ptr;//指向查询结果的指针   num QUN_NAME   


    char  sql[200];
    
    memset(sql, 0, sizeof(sql));
    sprintf(sql,"INSERT INTO  my_group_%s  VALUES('%s','%s');",from,group_name,to );
    res = mysql_query(conn,sql);//正确返回0
    res_ptr = mysql_store_result(conn);
  //  printf("==%s",sql);


}


void  group_request(MES PACK)//处理 群添加请求
{
    printf("开始群请求处理");
    int  to_fd,from_fd;
    to_fd = online_fri(PACK.to);
    from_fd = search_friend(PACK.from);
    if (PACK.state ==3){
        group_create_table(PACK.from,PACK.num);
        return ;
    }
    if (search_friend(PACK.to) ){ //判断用户是否存在 
        if(to_fd){                //判断用户是否在线
            if (PACK.state == -1)  printf("&&&& mode= %d",PACK.mode );    
            if (PACK.state ==0) ;// 拒绝请求
            if (PACK.state ==1){//同意请求并添加至群列表中 
                printf("添加群成员账号\n");
                
                group_friend_append(PACK.from,PACK.num);//添加群信息至数据库中    num QUN_NAME             
                my_group_append(PACK.from,PACK.num,PACK.to);//
               // group_create_mes_log(PACK.from,PACK.num);//创建聊天记录的表格
               
                                printf("已添加至数据库中\n");      
            }
            
            if(send(to_fd,&PACK,sizeof(PACK),0) < 0) { 
                my_err("send",__LINE__);
                exit(0);
            }
        } else//保存为离线消息
            save_in_mysql(PACK);

    }else{                             
        PACK.state = -2;//该用户不存在    
        printf(" state = %d\n",PACK.state );     
        if(send(from_fd,&PACK,sizeof(PACK),0) < 0) { ///**************这个send有问题啊***********************************``
            my_err("send",__LINE__);
            exit(0);
        }
    }
}


void    del_fd(int   connfd)//将次节点从登录链表中删除
{
    USA *temp;
    temp = head;

    while(temp->next !=  NULL)
    {
        if (connfd == temp->next->fd) 
            break;

    temp = temp->next;
    }
    
    temp->next = temp->next->next;


}



//退出登陆
void logout(int connfd)
{
    MES PACK;
    PACK.mode = 10;
    if(send(connfd,&PACK,sizeof(PACK),0) < 0) {
        my_err("send",__LINE__);
        exit(0);
    }
    del_fd(connfd);
    close(connfd);
    pthread_exit(0);
}

void  select_message_log(MES PACK,int connfd)//读取私聊聊天记录
{
    int res;//执行sql语句后的返回标志
    MYSQL_RES *res_ptr;//指向查询结果的指针
    MYSQL_FIELD *field;//字段结构指针
    MYSQL_ROW result_row;//按行返回查询信息
    int row,column;//查询返回的行数和列数

    int i,j;

    char  sql[200];
    sprintf(sql,"SELECT *  FROM %s_to_%s ;",PACK.from,PACK.to);
     //查询
   // printf("==%s\n",sql);


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
                printf("column = %d\n",column);
                    memset(&PACK,0,sizeof(PACK));
                
                PACK.mode = 11;
        
                strcpy( PACK.num,result_row[0]);

                strcpy(PACK.detail,result_row[1]);

                strcpy(PACK.time_mes,result_row[2]);                

     //           printf("mode = %d,%s,%s,%s,row = %d\n " ,PACK.mode,PACK.num,PACK.detail,PACK.time_mes, row); 
 
                    if(send(connfd,&PACK,sizeof(PACK),0) < 0) {
                         my_err("send",__LINE__);
                    } 
                }
                puts("");
            }

        }
}

char group_all_member(MES PACK)//向所有群成员发消息
{
    int res;//执行sql语句后的返回标志
    MYSQL_RES *res_ptr;//指向查询结果的指针
    MYSQL_FIELD *field;//字段结构指针
    MYSQL_ROW result_row;//按行返回查询信息
    int row,column;//查询返回的行数和列数

    int i,j;
    int  connfd;//

    char  sql[200];
    
    char  time_mes[20];
    time_t   timep;   
    time   (&timep);   

    strcpy(time_mes, ctime(&timep));
    sprintf(sql,"INSERT INTO message_group_%s  VALUES('%s','%s','%s');",PACK.num, PACK.from,PACK.detail,time_mes);
    
    res = mysql_query(conn,sql);//正确返回0
    res_ptr = mysql_store_result(conn);
    printf("==%s",sql);

    sprintf(sql,"SELECT *  FROM group_%s ;",PACK.num);
     //查询
   // printf("==%s\n",sql);

    char message[255];
    strcpy(message, PACK.detail);
    char from[20];
    strcpy(from, PACK.from);
    char group_name[20];
    strcpy(group_name,PACK.num);


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
                printf("column = %d\n",column);
                for(j = 0;j< column;j++) {
                    printf("%10s\n",result_row[j]);
                    memset(&PACK,0,sizeof(PACK));
                
                    
                    PACK.mode = 4;
                    strcpy(PACK.to , result_row[j]);
                    strcpy( PACK.num  ,group_name);
                    strcpy(PACK.from, from);
                    strcpy(PACK.detail, message);
                    PACK.mun = row;
    //                printf(" group_name= %s, from = %s,PACK.to=%s, message = %s\n",PACK.num, PACK.from,PACK.to ,PACK.detail);    
                    
                    connfd = online_fri(result_row[j]);
      //              printf("connfd = %d\n", connfd);
                    if (connfd){        
                        if(send(connfd,&PACK,sizeof(PACK),0) < 0) {
                            my_err("send",__LINE__);
                        } 
                        //save message
                    }else {//保存离线消息
                        
                        save_in_mysql(PACK);
                    }


                }
                puts("");
            }
        }
    }          

}
void file_center(MES PACK)
{
    int connfd;
    connfd = online_fri(PACK.to);
    if(connfd){
        if( send (connfd ,&PACK ,sizeof(PACK),0) < 0 ){
            my_err("send", __LINE__);
        }
    }else {
        printf("对方不在线\n");
    }


}

void delete_friend_center(MES PACK)//删除好友
{
    int res;//执行sql语句后的返回标志
    MYSQL_RES *res_ptr;//指向查询结果的指针
    char  time_mes[20];

    char  sql[200];
    
    sprintf(sql,"delete from friend_%s  where name = '%s';",PACK.from,PACK.to);
    res = mysql_query(conn,sql);//正确返回0
    res_ptr = mysql_store_result(conn);
    memset(&sql,0,sizeof(sql));
    
    sprintf(sql,"drop table %s_to_%s  ;",PACK.from,PACK.to);
    res = mysql_query(conn,sql);//正确返回0
    res_ptr = mysql_store_result(conn);
    memset(&sql,0,sizeof(sql));
    
    sprintf(sql,"drop table %s_to_%s  ;",PACK.to,PACK.from);
    res = mysql_query(conn,sql);//正确返回0
    res_ptr = mysql_store_result(conn);
    memset(&sql,0,sizeof(sql));
    printf("%s\n", sql );

    sprintf(sql,"delete from friend_%s  where name = '%s';",PACK.to,PACK.from);
    res = mysql_query(conn,sql);//正确返回0
    res_ptr = mysql_store_result(conn);
    memset(&sql,0,sizeof(sql));

    printf("delete   frinend \n");

}

void group_message_logg(MES PACK,int connfd) //查询群聊天记录
{

    int res;//执行sql语句后的返回标志
    MYSQL_RES *res_ptr;//指向查询结果的指针
    MYSQL_FIELD *field;//字段结构指针
    MYSQL_ROW result_row;//按行返回查询信息
    int row,column;//查询返回的行数和列数

    int i,j;

    char  sql[200];
    sprintf(sql,"SELECT *  FROM message_group_%s ;",PACK.num);
     //查询
    printf("==%s\n",sql);


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
                printf("column = %d\n",column);
                    memset(&PACK,0,sizeof(PACK));
                
                PACK.mode = 12;
        
                strcpy( PACK.num,result_row[0]);

                strcpy(PACK.detail,result_row[1]);

                strcpy(PACK.time_mes,result_row[2]);                

     //           printf("mode = %d,%s,%s,%s,row = %d\n " ,PACK.mode,PACK.num,PACK.detail,PACK.time_mes, row); 
 
                    if(send(connfd,&PACK,sizeof(PACK),0) < 0) {
                         my_err("send",__LINE__);
                    } 
                }
                puts("");
            }

        }

}   




void server_center(int  connfd)
{
    MES PACK;
    int re;
    while(1)
    {
        memset(&PACK,0,sizeof(PACK));
        if ((re=  recv(connfd,&PACK,sizeof(PACK),0)) <0 ){// <0 出错 =0 连接关闭 
            my_err("send",__LINE__);
            exit(0);
        } else if(re == 0) {
            printf("%s异常离线了\n",select_name(connfd));
                    
            logout(connfd);
            close(connfd);
            pthread_exit(0);
            
        }
        printf("-----------mode= %d\n ", PACK.mode  );
        switch (PACK.mode){
            case 3:
                private_chat(PACK);//处理私聊消息
                break;
            case 4:
                group_all_member(PACK); //处理群消息
                break;
            case 5:
                
                break;
            case 6:
                
                break;
            case 7:
                
                break;
            case 8:
                //好友请求处理    
                search_friend_add(PACK);
                break;
            case 9:
                
                group_request(PACK);//处理群请求
                break;
            case 10:
                //退出登陆
                printf("%s下线\n",PACK.from);
                logout(connfd);
                break; 
            case 11:
                //私聊记录
                select_message_log(PACK,connfd);
                break;
            case 12:
                //群聊记录
                group_message_logg(PACK,connfd);
                break;

            case 13:
                //删除好友
                delete_friend_center(PACK);
                
            case 15:
                //文件处理
                file_center(PACK);                    
                break;                    
            case 16:
                group_dismiss(PACK.num,PACK.from,PACK.to);
            case 17:
                show_group_member(connfd  , PACK.num);
                break;
            case 18:
                group_list_init(connfd);
                break;
            case 19:
                
                friend_list_init(connfd); //这个好友了列表初始化需要放到一个比较合适的位置，之后再说
                break;
            case 20:
                delete_member(PACK.num,PACK.mem_name);
            case 21:
               // quit_group();//退出群聊
                delete_member(PACK.num,PACK.from);
        }
    } 

}

void delete_member(char *group_name,char *mem_name)//踢成员
{
    int res;//执行sql语句后的返回标志
    MYSQL_RES *res_ptr;//指向查询结果的指针
    char  time_mes[20];

    char  sql[200];
    
    sprintf(sql,"delete from group_%s  where name = '%s';",group_name,mem_name);
    res = mysql_query(conn,sql);//正确返回0
    res_ptr = mysql_store_result(conn);
    memset(&sql,0,sizeof(sql));
    
    sprintf(sql,"delete from my_group_%s  where name = '%s';",mem_name,group_name);
    res = mysql_query(conn,sql);//正确返回0
    res_ptr = mysql_store_result(conn);
    memset(&sql,0,sizeof(sql));

}

int  match(MES *a,int connfd)//登录，注册的处理
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
    con = mysql_init(NULL);
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
        
        if(flag) {// 没有重复登录
            PACK.state = 1;
            if(send(connfd,&PACK,sizeof(PACK),0) < 0) {
                my_err("send",__LINE__);
                exit(0);
            }

    //    printf("88888\n");
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
        printf("=====%s=====\n",sql);
        res = mysql_query(conn,sql);//正确返回0
            res_ptr = mysql_store_result(conn);
        if(res) {
            perror("my_query");
            mysql_close(conn);
            exit(0);
        } else{
            //把查询结果给res_ptr
           // res_ptr = mysql_store_result(conn);
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

            res_ptr = mysql_store_result(conn);
            PACK.state = 1;
            printf("mode = %d\n", PACK.mode);
            create_friend_table(num);
            
            mkdir(num,S_IRWXU|S_IRWXG|S_IROTH | S_IXOTH);



            memset(sql, 0, sizeof(sql));
            sprintf(sql,"create table  my_group_%s  (name varchar(20) ,host varchar(20));",num );

            res = mysql_query(conn,sql);//正确返回0
            res_ptr = mysql_store_result(conn);
            printf("==%s",sql);




            if(send(connfd,&PACK,sizeof(PACK),0) < 0) {
                my_err("send",__LINE__);
                exit(0);
            }
            return 2;
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
  //  puts("dasdasd");
  //  printf("**fd:%d\n",(int *) arg);
    MES PACK;
    int ret;
    char  name[20];
    int connfd = (int*)arg;
    int a= connfd;
    while(1){
        memset(&PACK,0,sizeof(PACK));
            ret= recv (connfd,& PACK, sizeof(PACK),0);// <0 出错 =0 连接关闭 
      
            if(ret < 0) {
                my_err("recv",__LINE__);
            close(connfd);
            pthread_exit(0);
                exit(0);
            } else if(ret == 0) {
        
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
        
          leave_mess(connfd,name);//离线消息的处理
        
        add_list(name,connfd);
            
          server_center(connfd);//进入多任务处理界面
        }
        else if (res==2){    //成功注册的情况
            client((void*)a);           
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

    int  optval = 1;
    if(setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,(void*)&optval,sizeof(int)) < 0) //设定端口，要是异常退出還可以在绑定
    {
        my_err("setsockopt",__LINE__);         
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
