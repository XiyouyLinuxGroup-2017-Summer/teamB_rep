 #include<stdio.h>
 #include<stdlib.h>
 #include<unistd.h>
 #include<sys/types.h>
 #include<string.h>
 #include<fcntl.h>
 #include<sys/wait.h>
 #include<sys/stat.h>
 #include<dirent.h>
 #include<readline/readline.h>
 #include<readline/history.h>
 #include<signal.h>

 #define   normal 0
 #define   out_direct     1
 #define   int_redirect   2
 #define   pipe           3
 
 
 void explain_input(char buf[],int *argcount,char arglist[100][256]);
 void do_cmd(int argcount ,char arglist[100][256]);
 int find_cmd(char *cmd) ;
  
 int main(void)
 {
     int i ;
     int argcount = 0;
     char arglist[100][256];

     struct stat temp ;
     time_t now ;     
     char  *line ;
     signal(SIGINT,SIG_IGN);
     char  str[520];
     while(1)
     { 
         memset(str,0,sizeof(str));
         time(&now);
         strcpy(str ,"\e[1;31m ");
         strcat(str ,ctime(&now));
         strcat(str ,"\e[0m \e[1;32mMyshell $$ \e[0m\0 ");
         for(i= 0; i< 100 ;i++)
             arglist[i][0]='\0';
         argcount = 0;
         line=readline(str);
         if(*line)
             add_history(line);
         explain_input(line,&argcount,arglist);
         if(strcmp(arglist[0],"exit") == 0 || strcmp(arglist[0],"logout") == 0 )
             break;
         if(strcmp(arglist[0],"cd") == 0) //实现cd 命令
         {
             if(*arglist[1] == '-' || *arglist[1] == '~' || *arglist[1] == '\0')
                chdir("/home/liushengxi/");
             else 
             {
                 if(lstat(arglist[1],&temp) < 0)
                 {
                     printf("lstat error !!! \n");
                     continue ;
                 }
                if(S_ISREG(temp.st_mode))
                 {
                     printf("Sorry ,It's a file !!\n");
                     continue ;
                 }
                 else  if(arglist[1][strlen(arglist[1])-1] != '/')
                            strcat(arglist[1] ,"/\0") ;
                  chdir(arglist[1]) ;
             }
             continue ;
         }
         do_cmd(argcount,arglist); //处理命令
     }
     return 0;
 }
 




 void explain_input(char *buf,int *argcount,char arglist[100][256])  //没问题
 {
     int i,j= 0,k = 0;
     for(i= 0;i< strlen(buf)- 1 ;i++)   //i=strlen -2   "china\n\0"
     {
         if(buf[i] !=' ')
         {   if(i != strlen(buf)-2)
                     arglist[j][k++ ]= buf[i];
             else
             {
                  arglist[j][k++]=buf[i];
                  arglist[j][k]='\0';
             } 
         }
         else if ( buf[i+ 1] != ' ') 
         {
             arglist[j++][k]='\0';
             k= 0;
             if (arglist[j-1][0] == '\0')    j= j-1;
         }
     }
     *argcount= j + 1 ; //arglist 等价于argc,j 就是数组个数,老铁，为什么加一就是对的？？？？
 }
 
 
 
 
 void do_cmd(int argcount ,char arglist[100][256])
 {
     int flag= 0;   //判断命令的正确性
     int how= 0,temp ;   //命令格式
     int background = 0;//判断后台运行
     int i,j,next= 0;
     int fd, status ;
     char *argnext[argcount]; //指针数组 
     char *arg[argcount]; //指针数组
     char *file ;
     pid_t pid ;
     for(i= 0;i< argcount ;i++)
     {
         arg[i] =(char *)arglist[i];
     }
 
     arg[argcount]=NULL ;
 
     for(i= 0;arg[i] ;i++)
     {
         if(*arg[i] == '&' && arg[i + 1] != NULL) //ls & -l 
         {
             printf("Wrong command !!\n");
             exit(-1);
         }
         else if(*arg[i] == '&' && arg[i + 1] == NULL ) 
         {
             background= 1;
             arg[i]=NULL;
             break;
         }
     }
 
     for(i= 0;arg[i] ;i++)
     {
         if(*arg[i] == '>' && arg[i + 1] == NULL)
         {
             printf("Wrong command !!\n");
             exit(-1);
         }
         else if(*arg[i]== '>' && arg[i + 1] != NULL ) 
         {
             how=out_direct ;
             flag++ ;
             break;
         }
     }
 
     for(i= 0;arg[i] ;i++)
     {
         if(*arg[i] == '<' && arg[i + 1] == NULL)
         {
             printf("Wrong command !!\n");
             exit(-1);
         }
         else if(*arg[i]== '<' && arg[i + 1] != NULL ) 
         {
             how= int_redirect;
             flag++ ;
             break;
         }
     }
     for(i= 0;arg[i] ;i++)
     {
         if(*arg[i] == '|' && arg[i + 1] == NULL)
         {
             printf("Wrong command !!\n");
             exit(-1);
         }
         else if(*arg[i]== '|' && arg[i + 1] != NULL ) 
         {
             how=pipe ;
             flag++ ;
             break;
         }
     }
 
     if(flag > 1)
     {
         printf("Wrong command !! \n");
         exit(-1);
     }
     switch(how)
     {
         case out_direct:for(i= 0 ;arg[i];i++)
                         {
                             if(*arg[i] == '>')
                             {
                                 file=arg[i+ 1];
                                 arg[i]=NULL ;
                             }
                         }
                         break;
         case int_redirect:for(i= 0 ;arg[i];i++)
                         {
                             if(*arg[i] == '<')
                             {
                                 file=arg[i+ 1];
                                 arg[i]=NULL ;
                             }
                         }
                         break;
         case pipe:for(i= 0 ;arg[i];i++)
                      {
                         if(*arg[i] == '|')
                         {
                             temp= i;
                             for(j= i+ 1;arg[j];j++)
                                 argnext[next++]=arg[j];
                         }
                         argnext[next]=NULL ;
                     }
                     arg[temp]=NULL ;
                     break;
     }
 
     pid=fork();
 
     if(pid < 0)
     {
         printf("creat process failed !! \n");
         exit(-1);
     }
     switch(how)
     {
         case 0:if(pid == 0)   //第一次fork    ls 
                {
                    if(!find_cmd(arg[0]))
                    {
                        printf("the cmd is not find !!\n");
                        exit(-1);
                    }
                
                     execvp(arg[0],arg) ;  // arg 传参
                     exit(0);   //退出子进程
                }
               break;
         case 1:if(pid == 0)  // ls > 111 
                {
                    if(!find_cmd(arg[0]))
                    {
                        printf("the cmd is not find !!\n");
                        exit(-1);
                    }
                  fd=open(file,O_RDWR |O_CREAT |O_TRUNC,0644);  //创建file 文件,如何处理的?????
                  dup2(fd ,1);
                  execvp(arg[0],arg) ;
                  exit(0); //退出子进程
                }
               break;
         case 2:if(pid == 0) //ls  < 
                {
                    if(!find_cmd(arg[0]))
                    {
                        printf("the cmd is not find !!\n");
                        exit(-1);
                    }
                 fd=open(file,O_RDONLY) ;
                 dup2(fd ,0);
                 execvp(arg[0],arg) ;
                 exit(0); //退出子进程
                }
               break;
         case 3:if(pid == 0) // ls / | wc -l 
                {
                    pid_t pid2;
                    int  fd2 ;
                    pid2= fork();//第二次 fork
                    if(pid2 < 0)
                    {
                        printf("creat process failed !! \n");
                        exit(-1);
                    }
                    else if(pid2 == 0)
                    {
                         if(!find_cmd(arg[0]))
                         {
                             printf("the cmd is not find !!\n");
                             exit(-1);
                         }
                         fd2=open("/tmp/just_a_test",O_RDWR |O_CREAT |O_TRUNC,0644);
                         dup2(fd2 ,1);
                         execvp(arg[0],arg) ;
                         exit(0);//退出子子进程
                    }
                    if(waitpid(pid2 ,&status, 0) == -1 ) //子进程等待子子进程的执行
                    {
                        printf("waitpid is failed !! \n");
                        exit(-1);
                    }
                    if(!find_cmd(argnext[0]))
                    {
                         printf("the cmd is not find !!\n");
                         exit(-1);
                    }
                  fd2=open("/tmp/just_a_test",O_RDONLY);
                    puts("open file \n");
                  dup2(fd2,0);
                  execvp(argnext[0],argnext) ;
                  if(remove("/tmp/just_a_test") < 0)
                  {
                      printf("rm failed !! \n");
                      exit(-1);
                  }
                  exit(0);//退出子进程
                }
               break;
     }
     if(background == 1)
         return ;
     if(waitpid(pid ,&status, 0) == -1 )
     {
         printf("waitpid is failed !! \n");
         exit(-1);
     }
 }
 
 
 
 















 int find_cmd(char *cmd)   //没问题 
 {
     DIR *dir ;
    int i= 0 ;
    struct dirent *dirp ;
    char *path[]={"/bin","/usr/bin",NULL};
    while(path[i])
    {
        if((dir=opendir(path[i])) == NULL)
        {
            printf("opendir is failed !! \n");
            exit(-1);
        }
        while((dirp=readdir(dir)) ) 
        {
            if(strcmp(dirp->d_name,cmd) == 0)
            {
                closedir(dir);
                return 1;
             }
         }
         closedir(dir);
         i++ ;
     }
     return 0;
 }
