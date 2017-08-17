/*************************************************************************
	> File Name: client.c
	> Author:九五二七 
	> Mail: 
	> Created Time: 2017年08月12日 星期六 09时34分18秒
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<pthread.h>

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>






#define MAXLINE 4096
//切记两边结构体要完全相同   ！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
typedef struct message
{
        int mode;//模式
        int state;//状态
        char num[20];//账号
        char passd[20];
        char to[20];
        char from[20];
        char detail[255];    
        char  time_mes[50];
        int  mun;


}MES;


typedef struct User_list
{
    char num[20];
    int   n;
    struct User_list *next;

}USA;
USA *head= NULL;
typedef struct MES_box{
    int  n;
    MES PACK;
    int  flag;
    struct  MES_box  *next;
}BOX ;

typedef struct group_nam{
    
    int  n;
    char group_name[20];
    struct  group_nam  *next;
}GROUP ;


GROUP  *APPLE = NULL;



BOX  *HEAD = NULL;



int serv_fd;//

char send_num[20];//
char my_num[20];
int  online = 1;

void my_err(const char *err_string,int line);
void my_err(const char *err_string,int line)
{
    fprintf(stderr,"line:%d",line);
    perror(err_string);
    exit(1);
}

int  start();
int  chose_mode();
void sign_in_register(int mode);
void get_passd(char *passd);
void get_one_chat(MES  PACK);
void add_list(char *num);
void private_chat(void);
void show_fri_list();
int  friend_list_init(MES PACK);
int  select_fri(void);
void list_friend_add();
void chat_to_one();
void client_center();
void logout(void);
void Box_mes_append(MES PACK);//将此消息添加至消息盒子
void search_friend();
int  fri_repeat(char *name);
int   message_select_fri(void);
void  mess_box_solve();  //消息执行
void mess_box_center();  //消息盒子处理
void mess_box_view();    //消息盒子预览
void   friend_request(MES PACK);//好友请求的处理
void  create_group();//创建 群聊

void  chat_to_group();//主动群聊天
void  group_select_friend();//选择进入群聊的好友
/****************************************************************************************/



int   select_fri(void)//选择好友进行聊天
{
    int  n;
    USA *temp = head->next;
    memset(&send_num,0,sizeof(send_num));
    printf("请输入你要选择的好友序号\n");
    scanf("%d",&n);
    while(temp != NULL) {
        if(n == temp->n) {
            strcpy(send_num,temp->num);//消息接收方， 全局变量 
            break;
        }
        temp=temp->next;
    }
    if (temp == NULL) return 0;
    
    else {
        return 1;
    
    }   

}
int   select_group(void)//选择群序号进行聊天
{
    int  n;
    GROUP *temp = APPLE->next;
    memset(&send_num,0,sizeof(send_num));
    printf("请输入你要选择的群序号\n");
    scanf("%d",&n);
    while(temp != NULL) {
        if(n == temp->n) {
            strcpy(send_num,temp->group_name);//消息接收方， 全局变量 
            break;
        }
        temp=temp->next;
    }
    if (temp == NULL) return 0;
    
    else {
        return 1;
    }
}

int   message_select_fri(void)//选择好友
{
//    getchar();
    char  a;
    char name[20];
    USA *temp = head->next;
    MES PACK;


    memset(&PACK, 0 ,sizeof( PACK)) ;


    printf("请输入你要选择的好友名称\n");
    scanf("%s",name);
    printf(" 您的选择为 %s\n",name);
    while(temp != NULL) {
        if(strcmp(temp->num,name) ==0 ){
           // strcpy(send_num,temp->num);//消息接收方， 全局变量 
            break;
        }
    temp=temp->next;
    }
    if (temp == NULL){
        printf(" %s 不存在\n", name);
        return 0;
    } 
    else {
        
        PACK.mode = 11;
        strcpy(PACK.from, my_num);
        strcpy(PACK.to, name);
        if(send(serv_fd,&PACK,sizeof(PACK),0) < 0) {
        my_err("send",__LINE__);
        exit(0);
        }
        printf("presss  q to  quit\n");    
        while( ( a=getchar())   != 'q');        
   }
}
void  friend_request(MES PACK)//好友请求的处理
{
    char str[20];
    int  sel;
    while(1){
        printf("请输入 1,0 来回复好友请求: \n");
        //scanf("%d",&sel);
        sel = chose_mode();
        printf("sel = %d\n",sel);
        if(sel == 1 || sel ==0 ) break;
    
    }
    if (sel==1){
        PACK.state = 1;
    } else if(sel ==0){
        PACK.state = 0;
    } 
    //调换 from,to 顺序
    printf("你的选择是sel ===%d",PACK.state);
    strcpy( str, PACK.from);
    memset( &PACK.from, 0, sizeof(PACK.from));
    memset( &PACK.to, 0, sizeof(PACK.to));
    strcpy( PACK.from, my_num);
    strcpy( PACK.to,  str);
    //发射
  //  printf(" ==%s== %s*****state=%d@@@\n",PACK.to,PACK.from, PACK.state );
    
    if(send(serv_fd,&PACK,sizeof(PACK),0) < 0) {
        my_err("send",__LINE__);
        exit(0);
    }

}

void  group_request(MES PACK)//请求的处理
{
    char str[20];
    int  sel;
    while(1){
        printf("请输入 1,0 来回复群请求: \n");
        sel = chose_mode();
        printf("sel = %d\n",sel);
        if(sel == 1 || sel ==0 ) break;
    
    }
    if (sel==1){
        PACK.state = 1;
    } else if(sel ==0){
        PACK.state = 0;
    } 
    //调换 from,to 顺序
  //  printf("你的选择是sel ===%d",PACK.state);
    strcpy( str, PACK.from);
    memset( &PACK.from, 0, sizeof(PACK.from));
    memset( &PACK.to, 0, sizeof(PACK.to));
    strcpy( PACK.from, my_num);
    strcpy( PACK.to,  str);
    //发射
  //  printf(" ==%s== %s*****state=%d@@@\n",PACK.to,PACK.from, PACK.state );
    
    if(send(serv_fd,&PACK,sizeof(PACK),0) < 0) {
        my_err("send",__LINE__);
        exit(0);
    }

}


int  fri_repeat(char *name)//判断好友重复
{
    USA *temp;
    temp = head->next;
    while(temp!= NULL)
    {
        if (strcmp(name,temp->num)==0 )
            return 1;
    temp= temp->next;
    }
    if(temp== NULL) return 0;
}


void search_friend()//添加好友大功能
{
    char name[20];
    MES PACK;
    printf("请输入你要添加的好友ID\n");
    scanf("%s",name);
    printf("%s\n", name);
    if (fri_repeat(name)){
        printf("不能重复添加\n");

    }else if(strcmp(name,my_num) == 0) {
        printf("添加自己干嘛？？？\n");
    }else if (strcmp(name,my_num) != 0 ){
        memset(&PACK,0,sizeof(PACK));
        strcpy(PACK.from,my_num);
        strcpy(PACK.to ,name);
        PACK.mode = 8;
        PACK.state = -1;
        
        if(send(serv_fd,&PACK,sizeof(PACK),0) < 0) {
            my_err("send",__LINE__);
            exit(0);
        }
     //   printf("全局变量%s",my_num);
    //    printf("===%s\n", name);
        printf("已发送请求请稍后\n");
    }



}

void list_friend_add()
{
    system("clear");
    printf("1.摇一摇\n");
    printf("2.扫一扫\n");
    printf("3.返回主界面");
    int  sel;
    do{
        sel = chose_mode();
    }while(sel<1||sel>3);
    switch(sel){
        case 1:
            // list_all();
            list_friend_add();
            break;
        case 2:
            search_friend();
            list_friend_add();
            break;
        case 3:
            break;
    }
}

void  show_fri_list()//打印好友列表
{
    USA  *temp;
    temp = head->next;
    char  cnt;
    int  n=0;
    while (temp != NULL)
    {
        temp->n = (++n);
        printf("%d. %s\n",temp->n,temp->num);
        temp = temp->next;
    }
    printf("press q to return\n");
    while (scanf("%c",&cnt) && cnt !='q');

    system("clear");
}
void show_group_list()
{
    GROUP *temp;
    temp = APPLE->next;
    char  cnt;
    int  n=0;
    while (temp != NULL)
    {
        temp->n = (++n);
        printf("%d. %s\n",temp->n,temp->group_name);
        temp = temp->next;
    }
    printf("press q to return\n");
    while (scanf("%c",&cnt) && cnt !='q');

    system("clear");
}
void chat_to_one()
{
    MES PACK;
    printf("---enter to send--\n");
    printf("---quit  to leave-\n");
    getchar();
    while(1)
    {   
        memset(& PACK.detail, 0 , sizeof(PACK.detail) );
        gets(PACK.detail);
        printf("detail = %s\n",PACK.detail);
        if (strcmp(PACK.detail,"quit")== 0)
            break;

        setbuf(stdin,NULL);
        PACK.mode = 3;
        
        printf("my_num  %s \n",my_num);
        puts("");
        strcpy(PACK.from,my_num);
        
        strcpy(PACK.to,send_num);
        
        printf("PACK. from=%s***,send_num= %s*** ",PACK.from,send_num);
        if(send(serv_fd,&PACK,sizeof(PACK),0) < 0) {
            my_err("send",__LINE__);
            exit(0);
        }
    }
}

void  private_chat()
{
    system("clear");
    int sel,a;
    MES PACK;
    memset(&PACK,0,sizeof(PACK));
    USA *temp;
    USA *drop;
    temp = head->next;
    while(temp != NULL)
    {
    
    drop= temp->next;
    free(temp);
    temp = drop;
    }
    head->next= NULL;

           PACK.mode = 19;   
            if(send(serv_fd,&PACK,sizeof(PACK),0) < 0) {
                my_err("send",__LINE__);
                exit(0);
            }
    
    printf("1.好友列表\n");
    printf("2.选择好友聊天\n");
    printf("3.删除好友\n");
    printf("4.查看聊天记录\n");
    printf("5.返回上一级菜单\n");
    do{
        sel = chose_mode();
    }while(sel<1||sel>5);
   
    switch (sel){
        case 1:
            show_fri_list();
            private_chat();
            break;
        case 2:
            a = select_fri();//选择好友聊天
            if(a)  chat_to_one();
            else   private_chat();
            
            break;
        case 3:
            //删除好友
            break;
        case 4 :
            // 
            message_select_fri();//查看聊天记录
            break;
        case 5:
            break;
    }
}
void add_list(char *num)//添加至好友列表
{
    USA *temp;
    temp = (USA *)malloc(sizeof(USA));
    strcpy(temp->num ,num);
    temp->next = head->next;
    head->next = temp;
}
void group_add_list(char *name)//添加至QUN列表
{
    GROUP *temp;
    temp = (GROUP *)malloc(sizeof(GROUP));
    strcpy(temp->group_name ,name);
    temp->next = APPLE->next;
    APPLE->next = temp;
}
int  friend_list_init(MES PACK)//更新好友列表
{
//    printf("friend_list_init \n");


 //   printf("好友名%s \n", PACK.num);
        
    add_list(PACK.num);
    return  0;
}
int  group_list_init(MES PACK)//更新QUN列表
{
   // printf("group_list_init \n");


  //  printf("qun%s \n", PACK.num);
        
    group_add_list(PACK.num);
    return  0;
}
void get_group_chat(MES PACK)//获取群聊天信息 
{
    if(strcmp(PACK.num,send_num) == 0){//      num为群名 
        //如果是当前用户则直接输出
        printf("%s",PACK.detail);
        printf("**from**%s**",PACK.from);
        puts("");
    }else{
            printf("%s发来一条群%s的消息,请到消息盒子处理\n",PACK.from,PACK.num);
            Box_mes_append(PACK);
        //不是当前聊天的用户就放进消息盒子
    }

}

void get_one_chat(MES PACK)//获取私聊聊天内容 
{
    if(strcmp(PACK.from,send_num) == 0){//  from 为用户名  
        //如果是当前用户则直接输出
        printf("%s",PACK.detail);
        printf("**from**%s**",PACK.from);
        puts("");
    }else{
            printf("%s发来一条消息,请到消息盒子处理\n",PACK.from);
            Box_mes_append(PACK);
        //不是当前聊天的用户就放进消息盒子
    }
}
void Box_mes_append(MES PACK)//将此消息添加至消息盒子
{
    BOX *temp;
    temp = (BOX *)malloc(sizeof(BOX));
    
    temp ->PACK = PACK;
    temp->next = HEAD->next;
    HEAD->next = temp;
}
//只用来接收信息的子线程
void only_recv(void)
{
    //只用来接收信息的子线程
    while(1) {
        MES PACK;
        memset(&PACK,0,sizeof(MES));
        int re =0;
        while (re != sizeof(PACK)){
     //       printf("-------------------\n");
            re = recv(serv_fd,&PACK,sizeof(PACK),0);
        
        
        
        
        
    //    printf("PACK.mode =  %d, PACK.num= %s\n ",PACK.mode,PACK.num);
        if(re == 0) {
            puts("服务器开始维护,你已断开连接!");
            exit(0);
        } else if(re<0){
            my_err("recv",__LINE__);
            exit(0);
        }
        }
        switch(PACK.mode) {
        case 3:
            //私聊消息
            get_one_chat(PACK);
            break;
        case 4:
             get_group_chat(PACK);
            // //群聊消息
             break;
        case 5:
             break;
        case 6:
        case 7:
            // //我的群
            // if(PACK.resault == -1) {
            //     puts("你没有群,快去创建或者让好友邀请你吧!"WHITE);
            // }
            // List_Add(PACK);
             break;
        case 8:
            //加好友
            if(PACK.state==-1) {
                printf("\t%s请求加你为好友,请到消息盒子处理\n",PACK.from);
                //添加至消息盒子 
                 Box_mes_append(PACK);
            } else if(PACK.state == 0) {
                printf("%s拒绝了你的好友请求\n",PACK.from);
            } else if(PACK.state == 1) {
                printf("%s同意了你的好友请求\n",PACK.from);
            } else if(PACK.state == -2) {
                printf("%s 该用户不存在\n",PACK.from);
            }
            sleep(1);
            break;
        case 9:
           // 加群
            if(PACK.state==-1) {
                printf("\t%s邀请你加入群%s,请到消息盒子处理\n",PACK.from,PACK.num);
                 Box_mes_append(PACK);
            } else if(PACK.state == 0) {
                printf("%s拒绝进入群%s\n",PACK.to,PACK.num);
            } else if(PACK.state == 1) {
                printf("%s同意进入群%s\n",PACK.to,PACK.num);
            } else if(PACK.state == -2) {
                printf("%s已是该群成员,无需重复邀请\n",PACK.to);
            } 
            sleep(1);
            break;
        case 10:
            //退出登陆
            online = 0;
            pthread_exit(0);
            break;
        case 11:
            // //私聊记录
            printf("%s: %s--%s\n",PACK.num,PACK.detail,PACK.time_mes);
            break;
        case 12:
            //群聊记录
            // printf("%s:"WHITE" %s\n",PACK.from,PACK.detail);
            // break;
        case 13:
            //删好友
            // printf("%s已经删除了你...\n"WHITE,PACK.from);
            break;
        case 15:
            recv_file(PACK);
            break;
        case 18:
            group_list_init(PACK);
            break;
        case 19:
            //sleep(19);
            friend_list_init(PACK);//好友列表的更新
            break;
        }
    }
}

void mess_box_view()//消息盒子预览
{
    int  y=0;
    BOX *temp;
    temp = HEAD->next;
    while(temp != NULL)
    {
        temp->n = (++y);
        temp->flag = 0;
        printf("%d. %s的消息请处理\n",y ,temp->PACK.from );
    temp = temp->next;    
    }

           
}
void  mess_box_solve()//消息执行
{
    int  sel; 
    BOX *temp,*ptr;
    temp = HEAD->next;
    printf("请输入你要选择的消息序号\n");
    sel = chose_mode();
    ptr = HEAD;
    while(temp != NULL)
    {

        if(temp->n == sel){
            printf("%d. %s的消息请处理\n",temp->n ,temp->PACK.from );    
            break;
        }
    temp = temp->next;
    ptr = ptr->next; 
    }
    switch (temp->PACK.mode){
        case  3:
            //读取消息
            //sleep(2);
            printf("%s",temp->PACK.detail);
            printf("---from--%s<-",temp->PACK.from);
            puts("");
            printf("本条处理完毕\n");

            break;
        case  4:    
            //群聊消息
            //sleep(2);
            printf("%s",temp->PACK.detail);
            printf("--group-%s-from--%s<-",temp->PACK.num,temp->PACK.from);
            printf("本条处理完毕\n");
            break;
        case 8:
            //好友请求
            friend_request(temp->PACK);//好友请求的处理         &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&7
            //sleep(2);
            printf("本条处理完毕\n");
            break;
        case 9:
            //群请求
            group_request(temp->PACK);
            //sleep(2);
            printf("本条处理完毕\n");
            break;
    }   
    ptr->next= temp->next;
}
void mess_box_center()//消息盒子处理中心
{
    
    system("clear");
    
    int n =0,sel;
    

    printf("1.待处理消息列表\n");
    printf("2.选择消息并处理\n");
    printf("3.退出消息盒子\n");
    do{
        sel = chose_mode();
    }while(sel<1 || sel >3);
    switch(sel){
        case 1:
            mess_box_view();//消息盒子预览
            mess_box_center();
            break;
        case 2:
            mess_box_solve();//消息执行
            mess_box_center();
            break;
        case 3:
            break;
   }

}

void  group_select_friend(char *group_name)//选择进入群聊的好友
{
    MES  PACK;
    USA *temp;
    temp= head->next;
    char  name[20];
while(1){
    memset(&PACK, 0 , sizeof(PACK));
    printf("请输入你要选择的好友名称\n");
    printf("press quit  end\n");
    
    temp= head->next;
    scanf("%s",name);
  //  printf("name = %s\n",name);
    if (strcmp (name, "quit") == 0)
        return ;
           
        while(temp != NULL) {//检测好友是否存在 
            if(strcmp(temp->num,name) ==0 ){
                break;
            }
        temp=temp->next;
        }
    
    if (temp == NULL){
        printf("%s no exits\n", name);
        continue ;
    } 
    else {
        
        PACK.mode = 9;
        PACK.state = -1;
        strcpy(PACK.from, my_num);
        strcpy(PACK.to, name);
        strcpy(PACK.num,group_name);
  //      printf("PACK.to=%s  ,PACK.from =%s,PACK.GROUPNAME =%s\n",PACK.to ,PACK.from, PACK.num  );
        if(send(serv_fd,&PACK,sizeof(PACK),0) < 0) {
            my_err("send",__LINE__);
            exit(0);
        }        
   }

 }
}
void create_group ()
{
    char group_name[20];
    MES PACK;
    memset(&PACK, 0 , sizeof(PACK));  
    printf("请输入您想要创建的群名 \n ");
    
    scanf("%s",group_name);
    

    strcpy(PACK.from,my_num );
    
    strcpy(PACK.num, group_name);//群名
    PACK.mode= 9;  //群请求
    PACK.state = 3;
    

  //  printf("$$ser_fd = %d PACK.mode=%d, PACK.state=%d\n ",serv_fd,PACK.mode,PACK.state);
    if(send(serv_fd,&PACK,sizeof(PACK),0 ) <0 ){
        my_err("send",__LINE__);
    }
    
    printf("您创建的群名为%s\n ",group_name );
    
    //选择进入群聊的好友
    group_select_friend(group_name);
}

void group_chat()//主动群聊天
{
    int sel,a;
    MES PACK;
    memset(&PACK,0,sizeof(PACK));
    
            PACK.mode = 18;   //更新群列表
            if(send(serv_fd,&PACK,sizeof(PACK),0) < 0) {
                my_err("send",__LINE__);
                exit(0);
            }
    
    printf("1.群列表\n");
    printf("2.选择群聊天\n");
    printf("3.删除群\n");
    printf("4.查看群聊天记录\n");
    printf("5.返回上一级菜单\n");
    do{
        sel = chose_mode();
    }while(sel<1||sel>5);
   
    switch (sel){
        case 1:
            show_group_list();
            group_chat();
            break;
        case 2:
            a = select_group();//选择qun聊天
            if(a)  chat_to_group();
            else   group_chat();
            
            break;
        case 3:
            //删除好友
            break;
        case 4 :
            // 
           // message_select_group();//查看聊天记录
            break;
        case 5:
            break;
    }
}

void  chat_to_group()//在群聊天 
{
    MES PACK;
    printf("---enter to send--\n");
    printf("---quit  to leave-\n");
    getchar();
    while(1)
    {   
        memset(& PACK.detail, 0 , sizeof(PACK.detail) );
        gets(PACK.detail);
//        printf("detail = %s\n",PACK.detail);
        if (strcmp(PACK.detail,"quit")== 0)
            break;

        setbuf(stdin,NULL);
        PACK.mode = 4;
        
  //      printf("my_num  %s \n",my_num);
        puts("");
        strcpy(PACK.from,my_num);
        
        strcpy(PACK.num,send_num);//复制群名 
        
    //    printf("PACK. from=%s***,send_num= %s*** ",PACK.from,send_num);
        if(send(serv_fd,&PACK,sizeof(PACK),0) < 0) {
            my_err("send",__LINE__);
            exit(0);
        }
    }


}


void  group_talk ()//发起群聊
{
    system("clear");
    int sel;
    printf("1. 创建群名\n");
    printf("2. 进群聊条\n");
    printf("3. 返回上一级菜单\n");

    do{
        sel = chose_mode();
    }while(sel < 1 || sel > 3);
    
    switch(sel){
        case 1:
            create_group();//创建群
            break;
        case 2:
            group_chat();//进行群聊
            break;
        case 3:
            break;
    }

}
int  recv_file(MES PACK)//保存文件
{
    int fd;
    int len;
    if (( fd = open("/home/holy666/1.jpg" ,O_RDWR |O_APPEND|O_CREAT,  S_IRUSR|S_IWUSR ) ) <0  )  {
        my_err("send",__LINE__);
    }
   // len =  strlen(PACK.detail);
    len = write(fd, PACK.detail,PACK.mun ); 
    //printf("len = %d,PACK.mun= %d \n", len , PACK.mun);
    // printf("file detail %s\n" , PACK.detail);
    
    close(fd);

}



int send_file(int fd,char *friend_name )//发送文件函数
{
    MES PACK;
    int sum=0,len=0,file_len=0;
    int   i =0 ;
    char file_buf[255];
    if ((len = lseek (fd, 0,SEEK_END)) == -1 ){
        my_err("lseek",__LINE__);
    }
    lseek(fd, 0, SEEK_SET);//读写指针置于开头

    printf("待发送文件大小为 %d \n", len);
    
    // 添加一个确定接收文件请求



    while(sum != len){
        memset(file_buf, 0, sizeof(file_buf));
        memset(&PACK, 0 , sizeof(PACK));
        file_len = read (fd, file_buf, 255);
       // printf("读取到的信息为%s\n" , file_buf );
        sum += file_len;
        ++i;
      //  printf("file_len= %d\n",file_len);
        strcpy( PACK.from ,my_num);
        strcpy( PACK.to , friend_name );
        memcpy(PACK.detail, file_buf,file_len );
        PACK.mode = 15;
        PACK.mun = file_len;
        
        if (send(serv_fd, &PACK, sizeof(PACK),0 ) <0 ){
            my_err("send", __LINE__ );
        }
    }
    printf("发送完成 \n" );
    printf("发送次数为 %d \n",i);
}


void   select_file_to_friend()
{
    system("clear");
    USA *temp;
    temp = head->next;
 
    char file_name[50];
    
    char file_buf[255];
    char friend_name[20];
    int file_fd =0;
    getchar();
    printf("请输入您要选择发送文件的名称(绝对路径)\n");
    gets(file_name);
   // printf("file_name %s" ,file_name);
    file_fd = open( file_name , O_RDONLY);
 
    if ( file_fd ){//找到这个文件
        printf("请输入你要选择的好友名称\n");
        gets(friend_name);
        
        while(temp != NULL) {//检测好友是否存在 
            if(strcmp(temp->num,friend_name) ==0 ){
                break;
            }
        temp=temp->next;
        }
    
        if (temp == NULL){
            printf("%s no exits\n",friend_name);
            return ;
        }
        else   //发送文件
        
                   
            send_file(file_fd,friend_name );
    }
    else {
        printf("该文件不存在!!! \n");

    }




}
void  file_center()
{
    system("clear");
    printf("1.选择文件并发送\n");
    printf("2.返回上一级菜单\n");
    int sel=0 ;
    do{
        sel = chose_mode();
    }while(sel<1 || sel >2 );
    switch(sel) {
        case 1:
            select_file_to_friend();
            break;
        case 2:
            break;
        
    }
}

void client_center()
{
    
    system("clear");
    int  mun;
    printf("1.摇一摇\n");
    printf("2.我的好友\n");
    printf("3.我的群\n");
    printf("4.消息盒子\n");
    printf("5.*******\n");
    printf("6.文件传输\n");
    printf("7.退出登陆\n");
    int sel;
    do{
        sel=chose_mode();
      //  printf("main thread sel = %d\n",sel);
    }while(sel<1||sel>7);
    switch(sel) {
    case 1:    
        //all_list_init();
        list_friend_add();
        client_center();
        break;
    case 2:
        
        private_chat();
        client_center();
        break;
    case 3:
        group_talk ();//发起群聊
        client_center();
        break;
    case 4:
        mess_box_center();//消息盒子处理
        client_center();
        break;
    case 5:
        //create_group();//发起群聊//背景音乐
        client_center();
        break;
    case 6:
        //传输文件
        file_center();
        client_center();
        break;
    case 7:
        logout();
        sleep(1);
        if(online == 0) {
            puts("成功下线");
            exit(0);
        } else {
            puts("下线失败...");
            client_center();
        }
        break;
    }
}


void logout(void)
{
    MES PACK;
    PACK.mode = 10;
    strcpy(PACK.from,my_num);
    if(send(serv_fd,&PACK,sizeof(PACK),0) < 0) {
        my_err("send",__LINE__);
        exit(0);
    }
    printf("正在服务器发送下线请求...\n");
}



void get_passd(char *passd)
{
    scanf("%s",passd);
}
void sign_in_register(int mode)
{
    MES PACK;
    int ret;
    char  name[20];
    char  passd[20];

    memset(&PACK,0,sizeof(PACK));
    memset(&name,0,sizeof(name)); 
    printf("账号 :");
    scanf("%s",PACK.num);
    strcpy(name,PACK.num);
  //  printf("name = %s",name);
    if (mode == 1){
        printf("密码 :");
        get_passd(PACK.passd);
        
    }    
    if (mode == 2){
        do{
            memset(PACK.passd,0,sizeof(PACK.passd));
            memset(passd , 0, sizeof (passd));
            printf("\n密码 :");
            get_passd(PACK.passd);
            printf("密码 :");
            get_passd(passd);
            if (strcmp (PACK.passd , passd ) == 0 )
                break;
            else 
                    printf("两次密码不一致请重新输入\n");

        }while(1);
    }
    PACK.mode = mode;
    if (send (serv_fd, &PACK,sizeof(PACK),0) < 0){
        my_err("send",__LINE__);
        exit(0);
    } 
        printf("mode=%d state=%d\n", PACK.mode,PACK.state);
    memset(&PACK,0,sizeof(PACK));
    recv(serv_fd,&PACK,sizeof(PACK),0);
    //system("clear");
    printf("mode=%d state=%d\n", PACK.mode,PACK.state);
    if ( PACK.mode==1 && PACK.state == 1) {
        printf("登录成功\n");
       // printf("正在加载...");
       // sleep();
        strcpy(my_num,name);

        system("clear");
        
            pthread_t thid;
            pthread_create(&thid,NULL,(void*)only_recv,NULL);
        client_center();
    }else if( PACK.mode==1 && PACK.state != 1)  {
        printf("login failed\n");
        system("clear");
    }
    if ( PACK.mode==2 && PACK.state == 1) {
        printf("success register\n");
        system("clear");
        //client_center();
    }else if( PACK.mode==2 && PACK.state != 1) {
        printf("register failed\n");
        system("clear");
    }



}
int  chose_mode()//清空缓冲区问题
{
    int ret;
   setbuf(stdin, NULL);
    scanf("%d",&ret);
    return ret;
}
int start()
{
    int  type;
    printf("\t\t\t\t微信\n");
    printf("\t\t\t\t1.登录\n");
    printf("\t\t\t\t2.注册\n");
    
    do{
        type = chose_mode();
    }while(type != 1 && type != 2);
    switch (type){
        case 1:
            sign_in_register(type);
            start();
            break;
        case 2:
            sign_in_register(type);
            start();
            break;
        case 0:
            exit(0);
    }
}

int main(int argc, char** argv)
{
    int    sockfd, n;
    struct sockaddr_in    servaddr;
    head = (USA *)malloc(sizeof(USA));
    head->next = NULL;
    //消息盒子的初始化 

    HEAD = (BOX *)malloc(sizeof(BOX));
    HEAD->next = NULL;
    
    //群列表的初始化
    APPLE = (GROUP *)malloc(sizeof(GROUP));
    APPLE->next = NULL;

    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
    printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);
    exit(0);
    }
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(5555);
    
    if( inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr) <= 0){
    printf("inet_pton error for %s\n",argv[1]);
    exit(0);
    }

    if( connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
        printf("connect error: %s(errno: %d)\n",strerror(errno),errno);
        exit(0);
    }
    serv_fd = sockfd;
    start();
   
 
    
    close(sockfd);
    exit(0);
}























