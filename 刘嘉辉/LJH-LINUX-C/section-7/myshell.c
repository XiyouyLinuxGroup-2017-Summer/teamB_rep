/*************************************************************************
	> File Name: myshell.c
	> Author:九五二七 
	> Mail: 
	> Created Time: 2017年07月26日 星期三 08时29分45秒
 ************************************************************************/
 
#include <pwd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<errno.h>
#include<dirent.h>
#include<sys/wait.h>
#include<fcntl.h>
#include <signal.h>
#include <sys/resource.h> 
#include <readline/readline.h>  
#include <readline/history.h>



#define normal           0  //一般的命令
#define out_redirect     1  //输出重定向
#define in_redirect      2  //输入重定向
#define have_pipe        3  //命令中有管道
#define out_redirect2     4   // >>   
struct passwd *pw;  //用户信息结构体  


void get_input(char *buf,char *path,int *history_count,char history[][256]);      //
void explain_input(char *buf,int *argcount, char  arglist[100][256]);   // 对输入的命令进行解析
void do_cmd(int argcount, char arglist[100][256],int *history_count,char history[][256],char *path,char last_path[][256] ,int * last_count);                   //　执行命令　　
int   find_command(char *command);                       //　查找命令中的可执行程序

#define  MAX_SIZE  256


int  main(int argc , char **argv)
{
    int i;

    char history[256][256];//存储历史  
    int history_count=0;       //历史的数量  

    
    int    argcount = 0;//待执行命令的参数个数
    char   arglist[100][256];//存放命令
    char   **arg = NULL;
    char    *buf = NULL;
    char  *color = "--color=auto";
    /*******忽略键盘信号即ctrl -c ********/
    
    signal(SIGINT, SIG_IGN);
    
    char path [MAX_SIZE];   //进程所在路径  
    char last_path[256][256];//用来辅助实现cd -
    
    int    last_count = 0;  
    
    for (i=0 ; i<100; i++)  //初始化整个二维数组
        {
            last_path[i][0] = '\0';
        }
    
    
    buf = (char *) malloc (256);
    if ( buf == NULL )
    {
        perror("malloc failed!");
        exit(-1);
    }
    
    while(1) {
        memset(buf, 0,256);
        getwd(path);
        if(strcmp(arglist[0],"cd") == 0)
            strcpy(last_path[last_count++] ,path);

        while (strlen(buf) == 0)     //如果没有输入 或只是回车   就继续输入
            get_input(buf,path,&history_count,history);

        for (i=0 ; i<100; i++)  //初始化整个二维数组
        {
            arglist[i][0] = '\0';
        }
        argcount = 0;
        
        explain_input(buf , &argcount, arglist);
        // 添加颜色
        if (strcmp(arglist[0],"ls")== 0 || strcmp (arglist[0],"grep") == 0  ){
            strcpy(arglist[argcount], color);
            argcount++;
            arglist[argcount][0] = '\0';

        }
        
        
    /*    
        for(int i = 0; i < argcount; i++)
        {
            printf("arglist[%d]: %s\n", i, arglist[i]);
        }
    */
        do_cmd(argcount, arglist,&history_count,history,path,last_path,&last_count);
    }

    if (buf!=NULL)
    {
        printf("debug1\n");
        free (buf);
        buf = NULL;
    }
    exit (0);
}    
//准备使用sprintf来合称一个提示 

void get_input(char *buf,char *path,int * history_count,char history[][256])
{
    int  count=0,i,len;
    uid_t uid;
    char *temp;
    char str[500];
    
    
    uid = getuid();  //得到uid
    pw = getpwuid (uid);//得到用户信息

    if (!pw){
        printf("can't find ");
        return;
    
    }
    sprintf(str,"%c\033[;31m%s@\033[0m\033[;31mmyshell\033[0m\033[;32m%s\033[0m\033[;33m$\033[0m",'\b',pw -> pw_name,path);     //加上颜色，合成提示语句str
    
    //fflush(stdin);
    temp = (char *) malloc (sizeof(char)*256);     //readline返回值只能用malloc申请的指针来接受
    memset (temp, 0, sizeof(temp));
    temp = readline(str);
    strcpy(buf, temp);
    //历史记录的问题
    len = strlen (str);
    for (i=0; i<len ;i++){
        if (buf[0] == ' '|| buf[i] == '\n' )  //后用用于排除全是空格 或换行的问题 
            count++;
    }
    if(count != len ) {
        strcpy(history[*history_count],buf);  
        *history_count = *history_count + 1;  
        add_history(buf);  
    }   
}    
void explain_input(char *buf, int *argcount, char arglist[100][256])
{
    char *p = buf;
    char *q = buf;
    int number = 0;

    while(1)
    {
        if( p[0] == '\0')
            break;
        if( p[0] == ' ')
            p++;
        else {
            q = p;
            number = 0;
            while ((q[0] != ' ') && (q[0] != '\0' ))
            {
                number++;
                q++;
            }
            strncpy(arglist[*argcount],p, number +1);
            arglist[*argcount][number] = '\0';
            *argcount = *argcount + 1;
            p = q;
        }
    }
}
void do_cmd(int argcount, char arglist[100][256],int *history_count,char  history[][256],char *path,char last_path[][256],int *last_count)
{
    int     flag = 0,galf= 0;
    int     how  = 0; //用于指示命令中是否含有> < |
    int     background = 0;   // 标示命令中是否含有后台运行的标示符&
    int     status;
    int     fd,i;
    char*   arg[argcount+1];
    
    char*   argnext[argcount+1];
    char*   file;
    
    pid_t   pid;
    
    
        
    //cd命令
        if (strcmp(arglist[0],"cd")== 0) {
            
            printf("cd\n");
            if (argcount == 1 )
            { 
                printf("1\n");
                chdir("/home/holy666/");
                strcpy(path,"/home/holy666/"); 
            }
            if (argcount == 2){
                if (strcmp(arglist[1], "~") == 0 ){
                    chdir("/home/holy666/");
                    strcpy(path,"/home/holy666/");
                }
                if( strcmp(arglist[1], "-") == 0 ){
                    chdir(last_path[*last_count-2]);
                    strcpy(path, last_path[*last_count-2]);
                }
                else {
                    printf("chdir\n");
                    chdir(arglist[1]);
                    strcpy(path,arglist[1]);          
                }
            }
                
        return;
        }
    
    
    
    /*将命令取出*/
    for (i=0; i < argcount; i++)
    {
        arg[i] =( char *) arglist[i]; //存放每一段命令的指针
    }
    arg[argcount] = NULL;
    
    /*查看命令中是否有后台运行符*/
    for (i=0; i<argcount; i++)
    {
        if (strncmp(arg[i],"&", 1) == 0)   //
        {
            if (i == argcount-1) {
                background = 1;
                arg[argcount-1] = NULL;
                break;
            }
            else {
                printf("wrong command\n");
                return ;
            }    
        }
    }   
    
    for (i=0; arg[i]!=NULL ; i++)
    {
        if (strcmp(arg[i] , ">") == 0)
        {
            flag++;
            how = out_redirect;
            if (arg[i+1] == NULL)
                flag++;
        }
        if ( strcmp(arg[i] , "<") == 0 )
        {
            flag++;
            how = in_redirect;
            if (i == 0)
            
            flag++;
        }
        if (strcmp(arg[i] , ">>") == 0 )
        {
            flag++;
            how = out_redirect2;
            if (i==0) 
            flag++;

        }
        if ( strcmp(arg[i] , "|") == 0 )
        {
            flag++;
            how = have_pipe;
            if(i==0)
                flag++;
        }    
    }
/*flag > 1说明命令中含有多个> < | 符号，本程序是不支持这样的命令的*/
    if(flag >1)
    {
        printf("wrong command\n");
        return;
    }
    if (how == out_redirect)
    {
        for(i=0; arg[i] != NULL; i++)
            if (strcmp(arg[i], ">" ) == 0)
            {
                file = arg[i+1];
                arg[i] = NULL;
            }
    }
    if (how == out_redirect2)
    {
        for(i=0; arg[i] != NULL; i++)
            if (strcmp(arg[i], ">>" ) == 0)
            {
                file = arg[i+1];
                arg[i] = NULL;
            }
    }

    if (how == in_redirect)
    {
        for(i=0; arg[i] != NULL; i++)
            if (strcmp(arg[i], "<" ) == 0)
            {
                file = arg[i+1];
                arg[i] = NULL;
            }
    }
    int k=0;

    if (how == have_pipe)      //管道文件 
        for(i=0 ;arg[i] != NULL; i++)
        {
            if (strcmp(arg[i],"|") == 0 )
            {
            //    printf(+ )
                arg[i]  = NULL;
                int j;
                for (j = i+1; arg[j] != NULL; j++)
                {
                    argnext[j-i-1] = arg[j];
                }
                    argnext[j-i-1] = arg[j];
                    break;

            }
        }
      
        for(i=0 ;arg[i] != NULL; i++){
            printf("%s",arg[i]);
        }
    // 如果命令为history 则输出历史。  
    if(strcmp(arg[0],"history") == 0 && argcount == 1){  
        printf("tolal num %d :\n",*history_count);  
        for(i=0; i < *history_count; i++){  
            printf("%d\t%s\n",i+1,history[i]);  
        }  
    return ;  
    }  
                                                         
    if (strcmp(arg[0],"exit") == 0 ||  strcmp(arg[0],"logout") == 0 )
        {
            printf("白白\n");
            exit(0);
        }
    
    
    
    
    
    if ((pid = fork()) < 0)
    {
        printf("fork error\n");
        return ;
    }
    
 //   printf("how: %d\n", how);
    switch(how){
        case 0:                  
            if (pid == 0)
            {
                if (!(find_command(arg[0])) ){
                    printf("%s : command not found !\n",arg[0]);
                    exit(0);
                }
                execvp(arg[0], arg);
                printf("---->begin2\n");
                exit(0);
            }
            break ;
        case 1:
            if (pid ==0)
            {
                if (!(find_command(arg[0])) ){
                    printf("%s : command not found !\n",arg[0]);
                    exit(0);              
                }
            fd = open (file, O_RDWR|O_CREAT|O_TRUNC,0644);
            dup2(fd,1);
            execvp(arg[0],arg);
            exit(0);
            }
            break;
        case 4 :
            if (pid == 0)
            {
                if (!  (find_command(arg[0])))
                {
                    printf("%s : command not found !\n",arg[0]);
                    exit(0); 
                }
            fd = open (file , O_APPEND|O_RDWR,0644);
            dup2(fd , 1);

            execvp(arg[0],arg);
            exit(0);
            }
        case 2:
            if (pid == 0)
            {
                if(! (find_command(arg[0]) ))
                {
                    printf("%s : command not found !\n",arg[0]);
                    exit(0); 
                }
            fd = open(file, O_RDONLY);
            dup2(fd ,0);
            execvp(arg[0],arg);
            exit(0);
            }
            break;
        case 3:
        /*命令中含有管道符*/
        if(pid == 0)  
        {
                pid_t  pid2;
                int status2;
                int fd2;
            pid2=fork ();
            if (pid2  < 0)    
            {
                    printf("fork2 error");
                    return ;
            }
            else  if (pid2 == 0 ) 
            {
                printf("^^^^^^^^^^55555555555");
                if (!(find_command(arg[0]))) 
                {
                    printf("%s : command not found !\n",arg[0]);
                    exit(0); 
                }
                
                    fd2 = open("/tmp/youdonotknowfile", O_WRONLY|O_CREAT|O_TRUNC,0644);
                    dup2(fd2, 1);
                    printf("%s",arglist[0]);
                    execvp(arg[0], arg);
                    exit(0);
            } 
                
            if (waitpid (pid2, &status2, 0) < 0) 
                printf("wairt child  process error!\n");
                
            if (! (find_command (argnext[0])) )
            {
                printf("%s : command not  found\n",arg[0]);
                exit(0);
            }
                                                                                                                                                        
            fd2  = open ("/tmp/youdonotknowfile", O_RDONLY) ;
            dup2(fd2,0);
            printf("%s",argnext[0]);
            execvp (argnext[0], argnext);
            if ( remove ("/tmp/youdonotknowfile") )
                    printf("remove error \n");
            exit(0);
        }            
            break;     
        default: 
            break;
           
    }    //
    
    
    if ( background == 1 )
        { 
            printf("prcess id %d\n", pid) ;
            return ;
        }
        //父进程等待子进程退出
    if (waitpid (pid, &status, 0) == -1)
        {
            printf("wait for child process error \n");
        }
    
}
//查找命令中的可执行程序

int find_command ( char *command )
{
    DIR  *dp;
    struct dirent*  dirp;
    char *path[]= {"./","/bin","/usr/bin",NULL};

    //使当前目录下的程序可以运行
    if ( strncmp(command,"./",2) ==2 )
    {
        command = command+2;
    }

    //分别在当前目录下 ，
    int  i=0;
    while (path [i] != NULL ) 
    {
        if ( (dp = opendir (path[i])) == NULL )
            printf ("can not open /bin \n");
        while ( (dirp = readdir (dp)) != NULL ){
            if  (strcmp (dirp->d_name,command) == 0)
            {
                closedir(dp);
                return 1;
            }
        }
        closedir (dp);
        i++;
    }
    return  0;
}




