/*************************************************************************
	> File Name: my_shell.c
	> Author:hxllhhy
	> Mail:hxllhhy@gmail.com
	> Created Time: 2017年07月26日 星期三 10时46分32秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<dirent.h>
#include<signal.h>
#include<pwd.h>
#include<sys/utsname.h>
#include<readline/readline.h>
#include<readline/history.h>

#define normal          0  //一般的命令
#define out_redirect1   1  //输出重定向>
#define out_redirect2   2  //输出重定向>>
#define in_redirect     3  //输入重定向<
#define have_pipe       4  //命令中有管道|

void ctrl_c(int signum);
void get_pwd(char *pwd);
void myhistory();
void handle_shell();
void explain_input(char *buf,int *argcount,char arglist[100][256]);  //对输入的命令进行解析
void do_cmd(int argcount,char arglist[100][256]); //执行命令
int find_command(char *command);  //查找命令中的可执行程序

//信号处理函数
void ctrl_c(int signum)
{
}

//获得当前工作路径
void get_pwd(char *pwd)
{
    int len,i,j=0;
    char truepath[256];

    getcwd(truepath,256);

    char path[50]="/home/";    
    struct passwd *pw;
    pw = getpwuid(getuid());
    strcat(path,pw->pw_name);
    len=strlen(path);

    if(strncmp(path,truepath,len)==0)
    {
        pwd[j++]='~';
        for(i=len;truepath[i]!='\0';i++)
        {
            pwd[j]=truepath[i];
            j++;
        }
        pwd[j]='\0';
    }
    else
    {
        strcpy(pwd,truepath);
    }
}

//读取myhistory
void myhistory()
{
    int i=0,j;
    char his[1000][512];
    FILE *fp;

    fp=fopen("/home/hxll/myhistory","r");
    if(fp==NULL)
        perror("fopen");
    else
    {
        while(fgets(his[i],512,fp)!=NULL)
        {
            i++;
        }
    }
    fclose(fp);
    for(j=0;j<i-1;j++)
        printf("%5d  %s",j+1,his[j]);
}

//对输入的信息进行整体处理判断
void handle_shell()
{
    int i;
    int fd;
    int len=0;
    int argcount=0;
    char arglist[100][256];
    char *buf=NULL;

    struct stat st;
    struct passwd *psd;
    struct utsname uts;
    char computer[256];
    char pwd[256];
    char shellname[512];
    char *str=NULL;
    
    while(1)
    {
        buf=(char *)malloc(256);
        str=(char *)malloc(512);
        //将buf所指向的空间清0
        memset(buf,0,256);
        memset(str,0,512);
        
        //打印用户名，主机名，工作路径
        psd=getpwuid(getuid());
        strcpy(shellname,psd->pw_name);
        strcat(shellname,"@");
        if(gethostname(computer,255)!=0||uname(&uts)<0)
        {
            fprintf(stderr,"获取主机信息失败!/n");
            exit(1);    
        }
        strcat(shellname,uts.nodename);
        strcat(shellname,"\0");
        get_pwd(pwd);
        sprintf(str,"\033[1;32m%s\033[0m:%s\033[0m$ ",shellname,pwd);
        
        //获取输入信息,tab补全,上下翻
        buf=readline(str);
        if(*buf)
            add_history(buf);
        
        //将输入信息写入history文件中
        if((fd=open("/home/hxll/myhistory",O_CREAT|O_RDWR|O_APPEND,0644))==-1)
            perror("open");
        len=strlen(buf);
        if(len!=0)
        {
            write(fd,buf,len);
        }
        close(fd);

        //若输入的命令为exit/logout/quit则退出本程序
        if(strcmp(buf,"exit")==0||strcmp(buf,"logout")==0||strcmp(buf,"quit")==0)
            break;
        
        //如果按下回车键，换行
        if(strcmp(buf,"")==0)
            continue;
                    
        for(i=0;i<100;i++)
        {
            arglist[i][0]='\0';                
        }
        argcount=0;

        //提取输入信息中的命令
        explain_input(buf,&argcount,arglist);
        
        //cd
        if(strcmp(arglist[0],"cd")==0)
        {
            if(*arglist[1]=='\0'||*arglist[1]=='~')
                chdir("/home/hxll/");
            else
            {   
                if(S_ISREG(st.st_mode))
                    printf("Please input dir!\n");
                else if(arglist[1][strlen(arglist[1])-1]!='/')
                    strcat(arglist[1],"/");
                chdir(arglist[1]);
            }
            continue;
        }

        //history
        if(strcmp(arglist[0],"history")==0)
        {
            myhistory();
            continue;
        }

        //执行命令
        do_cmd(argcount,arglist);
    }
    free(buf);
    free(str);
}

//解析buf中的命令，将结果存入arglist中
//如输入命令为"ls -l /tmp"，则arglist[0],arglist[1],arglist[2]分别为ls,-l,/tmp
void explain_input(char *buf,int *argcount,char arglist[100][256])
{
    int i,mark=0,j=0;

    for(i=0;buf[i]!='\0';i++)
    {
        if(buf[i]!=' ')
        {
            mark=1;
            arglist[*argcount][j]=buf[i];
            j++;
        }
        if((buf[i]==' '&&(buf[i+1]==' '||buf[i+1])=='\0')||mark==0)
        {
            continue;
        }
        if(buf[i]==' '&&buf[i+1]!=' ')
        {
            arglist[*argcount][j]='\0';
            (*argcount)++;
            j=0;
        }
    }
    arglist[*argcount][j]='\0';
    (*argcount)++;
}

//执行命令
void do_cmd(int argcount,char arglist[100][256])
{
    int flag=0;
    int how=0;
    int background=0;
    int status;
    int i;
    int fd;
    char* arg[argcount+1];
    char* argnext[argcount+1];
    char* file;
    pid_t pid;

    //如果第一个命令是ls,把--color插在ls之后，ls显示颜色
    if(strcmp(arglist[0],"ls")==0)
    {
        argcount++;
        for(i=argcount;i>=2;i--)
            strcpy(arglist[i],arglist[i-1]);
        strcpy(arglist[1],"--color");
    }

    //将命令取出
    for(i=0;i<argcount;i++)
    {
        arg[i]=(char *)arglist[i];
    }
    arg[i]=NULL;
    
    //查看命令行是否有后台运行符
    for(i=0;i<argcount;i++)
    {
        if(strncmp(arg[i],"&",1)==0)
        {
            if(i==argcount-1)
            {
                background=1;
                arg[argcount-1]=NULL;
                break;
            }
            else
            {
                printf("wrong command\n");
                exit(1);
            }
        }
    }

    //查看命令行是否有>,>>,<,|
    for(i=0;arg[i]!=NULL;i++)
    {
        if(strcmp(arg[i],">")==0)
        {
            flag++;
            how=out_redirect1;
            if(arg[i+1]==NULL)
                flag++;
        }
        if(strcmp(arg[i],">>")==0)
        {
            flag++;
            how=out_redirect2;
            if(arg[i+1]==NULL)
                flag++;
        }
        if(strcmp(arg[i],"<")==0)
        {
            flag++;
            how=in_redirect;
            if(i==0)
                flag++;
        }
        if(strcmp(arg[i],"|")==0)
        {
            flag++;
            how=have_pipe;
            if(arg[i+1]==NULL)
                flag++;
            if(i==0)
                flag++;
        }
    }

    //flag大于1,说明命令中含有多个>,<,|符号，本程序不支持
    if(flag>1)
    {
        printf("wrong command\n");
        exit(1);
    }

    if(how==out_redirect1)
    {
        //命令中只含有一个输出重定向符号>
        for(i=0;arg[i]!=NULL;i++)
        {
            if(strcmp(arg[i],">")==0)
            {
                file=arg[i+1];
                arg[i]=NULL;
            }
        }
    }

    if(how==out_redirect2)
    {
        //命令中只含有一个输出重定向符号>>
        for(i=0;arg[i]!=NULL;i++)
        {
            if(strcmp(arg[i],">>")==0)
            {
                file=arg[i+1];
                arg[i]=NULL;     
            }
        }
    }

    if(how==in_redirect)
    {
        //命令中只含有一个输出重定向符号<
        for(i=0;arg[i]!=NULL;i++)
        {
            if(strcmp(arg[i],"<")==0)
            {
                file=arg[i+1];
                arg[i]=NULL;
            }
        }
    }

    if(how==have_pipe)
    {
        //命令中只含有一个管道符号|
        //把管道符号后面的部分存入argnext中， 管道后面的部分是一个可执行的shell命令
        for(i=0;arg[i]!=NULL;i++)
        {
            if(strcmp(arg[i],"|")==0)
            {
                arg[i]=NULL;
                int j;
                for(j=i+1;arg[j]!=NULL;j++)
                {
                   argnext[j-i-1]=arg[j];
                }
                argnext[j-i-1]=arg[j];
                break;
            }
        }
    }

    if((pid=fork())<0)
    {
        printf("fork error\n");
        return ;
    }

    switch(how)
    {
        case 0:
            //pid为0说明是子进程，在子进程中执行输入的命令
            //输入的命令不含<>|
            if(pid==0)
            {
                if(!(find_command(arg[0])))
                {
                    printf("%s :command not found\n",arg[0]);
                    exit(0);
                }
                execvp(arg[0],arg);
                exit(0);
            }
            break;
        
        case 1:
            //输入的命令中含有输出重定向符>
            if(pid==0)
            {
                if(!(find_command(arg[0])))
                {
                    printf("%s :command not found\n",arg[0]);
                    exit(0);
                }
                fd=open(file,O_RDWR|O_CREAT|O_TRUNC,0644);
                dup2(fd,1);
                execvp(arg[0],arg);
                exit(0);
            }
            break;
        
        case 2:
            //输入的命令中含有输出重定向符>>
            if(pid==0)
            {
                if(!(find_command(arg[0])))
                {
                    printf("%s :command not found\n",arg[0]);
                    exit(0);
                }
                fd=open(file,O_APPEND|O_WRONLY,0644);
                dup2(fd,1);
                execvp(arg[0],arg);
                exit(0);
            }
            break;
        case 3:
            //输入的命令中含有输入重定向符<
            if(pid==0)
            {
                if(!(find_command(arg[0])))
                {
                    printf("%s :command not found\n",arg[0]);
                    exit(0);
                }
                fd=open(file,O_RDONLY);
                dup2(fd,0);
                execvp(arg[0],arg);
                exit(0);
            }
            break;
        case 4:
            //输入的命令中含有管道符|
            if(pid==0)
            {
                int pid2;
                int status2;
                int fd2;

                if((pid2=fork())<0)
                {
                    printf("fork2 error\n");
                    return ;
                }
                else if(pid2==0)
                {
                    if(!(find_command(arg[0])))
                    {
                        printf("%s :command not found\n",arg[0]);
                        exit(0);
                    }
                    fd2=open("/tmp/youdonotknowlife",O_WRONLY|O_CREAT|O_TRUNC,0644);
                    dup2(fd2,1);
                    execvp(arg[0],arg);
                    exit(0);
                }

                if(waitpid(pid2,&status2,0)==-1)
                    printf("wait for child process error\n");

                if(!(find_command(argnext[0])))
                {
                    printf("%s :command not found\n",argnext[0]);
                    exit(0);
                }
                fd2=open("/tmp/youdonotknowlife",O_RDONLY);
                dup2(fd2,0);
                execvp(argnext[0],argnext);

                if(remove("/tmp/youdonotknowlife"))
                    printf("remove error\n");
                exit(0);
            }
            break;
        default:
            break;
    }

    //若命令中有&，表示后台执行，父进程直接返回，不等待子进程结束
    if(background==1)
    {
        printf("[%d]\n",pid);
        return ;
    }

    //父进程等待子进程结束
    if(waitpid(pid,&status,0)==-1)
        printf("wait for child process error\n");
}

int find_command(char *command)
{
    DIR* dp;
    struct dirent* dirp;
    char* path[]={"./","/bin","/usr/bin",NULL};

    //使当前目录下的程序可以运行，如命令"./fork"可以被正确解释的执行
    if(strncmp(command,"./",2)==0)
        command+=2;

    //分别在当前目录、/bin和/usr/bin目录查找要执行的程序
    int i=0;
    while(path[i]!=NULL)
    {
        if((dp=opendir(path[i]))==NULL)
            printf("can not open /bin \n");
        while((dirp=readdir(dp))!=NULL)
        {
            if(strcmp(dirp->d_name,command)==0)
            {
                closedir(dp);
                return 1;
            }
        }
        closedir(dp);
        i++;
    }
    return 0;
}

int main(int argc,char **argv)
{
    signal(SIGINT,ctrl_c);

    handle_shell();

    exit(0);
}

