/*************************************************************************
	> File Name: myshell.c
	> Author:九五二七 
	> Mail: 
	> Created Time: 2017年07月26日 星期三 08时29分45秒
 ************************************************************************/

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

#define normal           0  //一般的命令
#define out_redirect     1  //输出重定向
#define in_redirect      2  //输入重定向
#define have_pipe        3  //命令中有管道

void print_prompt();                             //  
void get_input(char *buf);                           //
void explain_input(char *buf,int *argcount, char  arglist[100][256]);   // 对输入的命令进行解析
void do_cmd(int argcount, char arglist[100][256]);                   //　执行命令　　
int   find_command(char *command);                       //　查找命令中的可执行程序

int  main(int argc , char **argv)
{
    int i;
    int   argcount = 0;//待执行命令的参数个数
    char  arglist[100][256];//存放命令
    char  **arg = NULL;
    char *buf = NULL;

    buf = (char *) malloc (256);
    if ( buf == NULL )
    {
        perror("malloc failed!");
        exit(-1);
    }
    
    while(1) {
        memset(buf, 100, 256);
        print_prompt();
        get_input(buf);
        if (strcmp(buf,"exit\n") == 0 ||  strcmp(buf,"logout\n") == 0 )
        {
            break;
        }
        for (i=0 ; i<100; i++)  //初始化整个二维数组
        {
            arglist[i][0] = '\0';
        }
        argcount = 0;
        
        explain_input(buf , &argcount, arglist);

        do_cmd(argcount, arglist);
    }

    if (buf!=NULL)
    {
        free (buf);
        buf = NULL;
    }
    exit (0);
}    

void  print_prompt()
{
    printf("myshell$$ ");
}

void get_input(char *buf)
{
    int len = 0 ;
    char ch;

    ch = getchar ();
    while(len < 255 && ch != '\n')
    {
        buf[len++] = ch;
        ch = getchar();
    }

    if (len == 255)
    {
       printf("command is too long\n");
        exit(-1);
    }    
    
    buf[len] ='\n';
    len++;
    buf[len] = '\0';
}
    
void explain_input(char *buf, int *argcount, char arglist[100][256])
{
    char *p = buf;
    char *q = buf;
    int number = 0;

    while(1)
    {
        if( p[0] == '\n')
            break;
        if( p[0] == ' ')
            p++;
        else {
            q = p;
            number = 0;
            while ((q[0] != ' ') && (q[0] != '\n' ))
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
void do_cmd(int argcount, char arglist[100][256])
{
    printf("===%d===",argcount);
    int     flag = 0;
    int     how  = 0; //用于指示命令中是否含有> < |
    int     background = 0;   // 标示命令中是否含有后台运行的标示符&
    int     status;
    int     fd,i;
    char*   arg[argcount+1];
    char*   argnext[argcount+1];
    char*   file;
    pid_t   pid;
    
    /*将命令取出*/
    for (i=0; i < argcount; i++)
    {
        arg[i] =( char *) arglist[i]; //存放每一段命令的指针
    }
    arg[argcount] = NULL;
    
    /*查看命令中是否有后台运行符*/
    for (i=0; i<argcount; i++)
    {
        if (strncmp(arg[i],"&", 1) == 0)   //不太理解啊
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
        if ( strcmp(arg[i] , "|") == 0 )
        {
            flag++;
            how = have_pipe;
            if (i == 0)
                flag++;            
        }    
    }
/*flag > 1说明命令中含有多个> < | 符号，本程序是不支持这样的命令的*/
    if(flag >1)
    {
        printf("wrong command\n");
        return ;
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
    if (how == in_redirect)
    {
        for(i=0; arg[i] != NULL; i++)
            if (strcmp(arg[i], "<" ) == 0)
            {
                file = arg[i+1];
                arg[i] = NULL;
            }
    }
    
    if (how == have_pipe)      //管道文件 
        for(i=0; arg[i] != NULL; i++)
        {
            if (strcmp(arg[i],"|") == 0 )
            {
                arg[i]  = NULL;
                int j;
                for (j = i+1; arg[j] != NULL; j++)
                {
                    argnext[j-i-1] = arg[j];
                    break;
                }
            }
        }
    
    if ((pid = fork()) < 0)
    {
        printf("fork error\n");
        return ;
    }
    
    switch(how){
        case 0:                  
        {
            if (pid == 0)
            {
                if (!(find_command(arg[0])) ){
                    printf("%s : command not found !\n",arg[0]);
                    exit(0);
                }
            }
            execvp(arg[0], arg);
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
            dup(2);
            execvp(arg[0],arg);
            exit(0);
            }
            break;
        case 2:
            if (pid == 0)
            {
                if(! (find_command(arg[0]) ))
                {
                    printf("%s : command not found !\n",arg[0]);
                    exit(0); 
                }
            fd = open(file, O_RDONLY);
            dup2(fd ,2);
            exit(0);
            }
            break;
        case 3:
        /*命令中含有管道符*/
            if(pid == 0)
            {
                int  pid2;
                int status2;
                int fd2;

                if ((pid2 = fork() ) > 0)
                {
                    printf("fork2 error");
                    return ;
                }
                else if (pid==2 ){
                    if (!(find_command(arg[0]))) {
                    printf("%s : command not found !\n",arg[0]);
                    exit(0); 
                    }
                
                fd2 = open("/tmp/youdonotknowfile", O_WRONLY|O_CREAT|O_TRUNC,0644);
                    dup2(fd2, 1);
                    execvp(arg[0], arg);
                    exit(0);
                } 
                
                if (waitpid (pid2, &status2, 0) == -1 ) 
                    printf("wairt child  process error!\n");
                if (! (find_command (argnext[0])) ){
                 printf("%s : command not  found\n",arg[0]);
                    exit(0);
                }
            
                fd2  = open ("/tmp/youdonotknowfile", O_RDONLY) ;
                    dup2(fd2,0);
                    execvp (argnext[0], argnext);

                    if ( remove ("/tmp/youdonotknowfile") )
                        printf("remove error \n");
                    exit(0);
                }            
                break;     
                 
        default: 
            break;
           
        //
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


















































































































































































































































































































































































































































































