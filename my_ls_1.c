
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<time.h>
#include<dirent.h>
#include<grp.h>
#include<errno.h>
#include<pwd.h>
#include<string.h>

#define PARAM_NONE 0
#define PARAM_A    1
#define PARAM_L    2
#define PARAM_r    4
#define PARAM_R    8
#define PARAM_I    16

void my_err(const char *err_string ,int line )
{
    fprintf(stderr,"line:%d " ,line) ; 
    perror(err_string) ; 
    exit(1) ;
}

void display_attribute(struct stat buf,char *name,int flag_param)  //以-l参数 显示文件, struct stat *buf 保存文件状态信息的结构体
{
    char buf_time[32];
    struct passwd *psd; //struct passwd 保存文件所有者的信息
    struct group *grp; //struct group  保存文件所有者所属组的信息
    int temp ;
    temp=flag_param ;
    temp=temp>> 4 & 1; //取出第五位,代表 -i 参数
    if(temp)
        printf("%10d  ",buf.st_ino);
    switch (buf.st_mode & S_IFMT) {
    case S_IFBLK:  printf("b");        break;
    case S_IFCHR:  printf("c");        break;
    case S_IFDIR:  printf("d");        break; //入队列？？？？
    case S_IFIFO:  printf("f");        break;
    case S_IFLNK:  printf("l");        break;
    case S_IFREG:  printf("-");        break;
    case S_IFSOCK: printf("s");        break;
    default:       printf("unknown?"); break;
    }
    
/*所有者的权限*/
    if(buf.st_mode & S_IRUSR) //与对应的权限取与运算即可
        printf("r");
    else printf("-");
    if (buf.st_mode & S_IWUSR)
        printf("w");
    else printf("-");
    if(buf.st_mode & S_IXUSR )
        printf("x");
    else printf("-");
/*用户组的权限*/
    if(buf.st_mode & S_IRGRP)
        printf("r");
    else printf("-");
    if (buf.st_mode & S_IWGRP)
        printf("w");
    else printf("-");
    if(buf.st_mode & S_IXGRP )
        printf("x");
    else printf("-");
/*其他人的权限*/
    if(buf.st_mode & S_IROTH)
        printf("r");
    else printf("-");
    if (buf.st_mode & S_IWOTH)
        printf("w");
    else printf("-");
    if(buf.st_mode & S_IXOTH)
        printf("x");
    else printf("-");
    printf(".    ");
    printf("%-4d",buf.st_nlink);
    psd=getpwuid(buf.st_uid); //getpwuid 通过uid 找到用户名
    grp=getgrgid(buf.st_gid); //getgrgid   通过gid 找到用户名组
    printf("%15s",psd->pw_name);
    printf("%15s",grp->gr_name);
    printf("%10d",buf.st_size);
    strcpy(buf_time,ctime(&buf.st_mtime));//ctime 把日期和时间转换为字符串
    buf_time[strlen(buf_time)- 1]='\0'; //去掉换行符
    printf(" %20s",buf_time); 
}

char type_print(struct stat buf,char *name)  //判断文件类型，按颜色打印文件名
{
    switch (buf.st_mode & S_IFMT)      //printf ("%8s\n")
    {
        case S_IFBLK:  printf("\e[1;33m  %20s\033[0m\n",name);        break;
        case S_IFCHR:  printf("\e[1;33m  %20s\033[0m\n",name);        break;
        case S_IFDIR:  printf("\e[1;34m  %20s\033[0m\n",name);        break;
        case S_IFIFO:  printf("\e[1;33m  %20s\033[0m\n",name);        break;
        case S_IFLNK:  printf("\e[0;34m  %20s\033[0m\n",name);        break;
        case S_IFREG:  printf("  %20s\n",name);        break;
        case S_IFSOCK:  printf("\e[1;35m  %30s\033[0m\n",name);        break;
        default:       printf("  unknown?\n"); break;
    }
}

void display(int flag_param,char *pathname)  ///home/liushengxi/test.c   /home/liushengxi/.vimrc  处理一个目标文件
{
    int i,j;
    struct stat buf;
    char name[NAME_MAX + 1];    //NAME_MAX     一个单独文件最长的名字
    for(i= 0,j= 0;i<strlen(pathname);i++)  //作用：把pathname (/home/liushengxi/****) 的文件名****存储于name 中
    {
        if(pathname[i]=='/')
        {
            j= 0;
            continue;
        }
        name[j++]=pathname[i];
    }
    name[j]='\0';

    if(lstat(pathname,&buf) < 0)   //文件信息存于 buf 中
        my_err("lstat",__LINE__);

    switch(flag_param)
    {
        case PARAM_NONE :
                       if(name[0] != '.')
                       type_print(buf,name);//编写一个函数，根据文件类型，按颜色 printf 
                       break;
        case PARAM_r :
                       if(name[0] != '.')
                       type_print(buf,name);
                       break;
        case PARAM_A:
                    type_print(buf,name);
                    break;
        case PARAM_L:
                     if(name[0] != '.')
                     {
                         display_attribute(buf,name,flag_param); //传入flag_param 参数，以判断 i 和 l 参数 
                         type_print(buf,name);
                     }
                     break;
        case PARAM_I :
                    if(name[0] != '.')
                    {
                        printf("%10d  ",buf.st_ino);
                        type_print(buf,name);
                    }
                    break;
        case PARAM_A+PARAM_L :
                     display_attribute(buf,name,flag_param);
                     type_print(buf,name);
                     break;
        case PARAM_A+PARAM_I:
                     printf("%10d  ",buf.st_ino);
                     type_print(buf,name);
                     break;
        case PARAM_I+PARAM_L:
                    if(name[0] != '.')
                    {
                        display_attribute(buf,name,flag_param);
                        type_print(buf,name);
                    }
                     break;
        case PARAM_r+PARAM_A :
                     type_print(buf,name);
                     break;
        case PARAM_r+PARAM_L :
                    if(name[0] != '.')
                    {
                         display_attribute(buf,name,flag_param);
                        type_print(buf,name);
                    }
                     break;
        case PARAM_r+PARAM_I :
                    if(name[0]!= '.')
                    {
                         printf("%10d  ",buf.st_ino);
                        type_print(buf,name);
                    }
                     break;
        case PARAM_I+PARAM_L+PARAM_A:
                     display_attribute(buf,name,flag_param);
                     type_print(buf,name);
                     break;
        case PARAM_r+PARAM_L+PARAM_A:
                     display_attribute(buf,name,flag_param);
                     type_print(buf,name);
                     break;
        case PARAM_r+PARAM_I+PARAM_A:
                     printf("%10d  ",buf.st_ino);
                     type_print(buf,name);
                     break;
        case PARAM_r+PARAM_I+PARAM_L:
                    if(name[0] != '.')
                    {
                        display_attribute(buf,name,flag_param);
                        type_print(buf,name);
                    }
                        break;
        case PARAM_r+PARAM_I+PARAM_L+PARAM_A:
                     display_attribute(buf,name,flag_param);
                     type_print(buf,name);
                     break;

        default:     break;
    }
}
void display_dir(int  flag_param,char *path)  //path 目录名，即：/home/liushengxi/***/    或者是   /
{
    DIR *dir;   //目录指针
    struct  dirent  *ptr; //struct dirent 保存目录的信息
    int count = 0;
    char filename[500][PATH_MAX+ 1],temp[PATH_MAX + 1]; 
    int flag_temp ;
    dir=opendir(path);
    if(dir == NULL)
        my_err("opendir",__LINE__);

    while((ptr=readdir(dir)) != NULL)   //目标就是求该目录下的文件总数 count
        count++ ;

    closedir(dir);

    if(count > 500)
        my_err("too many files in the dir ",__LINE__);
    int i,j,len=strlen(path) ;  
    dir=opendir(path);
    for(i= 0;i< count;i++) //一个文件一个文件的打开
    {
        ptr=readdir(dir);
        if(ptr == NULL )
        {
            my_err("readdir",__LINE__);
        }
        strncpy(filename[i],path,len);//把目录名考到filename中
        filename[i][len]='\0';

        strcat(filename[i],ptr->d_name); //把文件名考到filename中,其实就是让filename中存储文件的完整路径

        filename[i][len+strlen(ptr->d_name)]='\0';
    }

    //实现  -r   参数
    flag_temp=flag_param ;
    flag_temp=flag_temp >> 2 & 1; //取出第三位,代表 -r 参数
        
    for(i= 0;i< count- 1;i++)  //冒泡排序文件名, 考虑-r 参数
    {
        for(j= 0;j< count -1 -i ;j++)
        {

                if (strcmp(filename[j],filename[j + 1]) > 0 )
                {
                    strcpy(temp,filename[j+ 1]);
                    strcpy(filename[j + 1],filename[j]);
                    strcpy(filename[j],temp);
                }
        }
    }
    if(flag_temp)
    {
        for(i= count - 1;i>= 0; i-- )
        {
            display(flag_param,filename[i]);//多次调用函数
            
        }
    }else 
    {
        for(i= 0;i< count; i++ )
            display(flag_param,filename[i]);//多次调用函数
    }
    closedir(dir); 
}
int main(int argc,char **argv)  
{
    int i,j,k,num;
    char path[PATH_MAX+ 1]; //路径
    int param[32];    //保存命令行参数alirR
    struct stat buf; //文件信息 
    int flag_param= PARAM_NONE; //参数种类
    j= 0;
    num = 0;
    for(i= 1;i< argc;i++)   //ls    -a   
    {
        if(argv[i][0] == '-')
        {
            for(k= 1;k < strlen(argv[i]);k++,j++)
                param[j]=argv[i][k];
            num=num + 1;
        }
    } 
   

    for(i=  0;i< j;i++)
    {
        switch(param[i])
        {
            case 'a':flag_param |= PARAM_A ;continue ;
            case 'l':flag_param |= PARAM_L ;continue ;
            case 'i':flag_param |= PARAM_I ;continue ;
            case 'r':flag_param |= PARAM_r ;continue ;
            case 'R':flag_param |= PARAM_R ;continue ;
            default :printf("Sorry !! We are only suport -a -l -i -r  -R   !!!!\n");exit(-1);
        }
    }
    param[j]='\0';
    
    if((num + 1) == argc) //只输入a.out ,即 ls  
    {
        strcpy(path,"./");
        path[2]='\0';
        display_dir(flag_param,path);//path== './' 
        return 0;
    }
    i= 1;
    do
    {
        if(argv[i][0] == '-') //ls   -a    -l  ***** , 就是找****
        {
            i++;
            continue;
        }
        else 
        {
            strcpy(path,argv[i]); //argv[i] 就是**** ,但可能有很多个文件需要显示，所以需要 do while {}循环

            if(stat(path,&buf)< 0)
                my_err("stat",__LINE__);
            

            if(S_ISDIR(buf.st_mode))  //argv[i] 是一个目录
            {
                if(path[strlen(argv[i]) - 1] != '/')
                {
                    path[strlen(argv[i])] ='/';
                    path[strlen(argv[i]+ 1)] ='\0';
                }
                else  path[strlen(argv[i])] ='\0';

                display_dir(flag_param,path);//flag_param ==  0
                i++ ;
            }
            else    // arhv[i]是一个文件
            {
                display(flag_param,path);
                i++ ;
            }
        }
    }while(i< argc);
    return 0;
}

