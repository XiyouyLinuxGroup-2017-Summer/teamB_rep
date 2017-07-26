/*************************************************************************
	> File Name: ls-l.c
	> Author:hxllhhy
	> Mail:hxllhhy@gmail.com
	> Created Time: 2017年06月30日 星期五 13时32分33秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<linux/limits.h>
#include<dirent.h>
#include<grp.h>
#include<pwd.h>
#include<errno.h>
#include<math.h>

#define width 120       //行宽
#define PARAM_NONE 0   //无参
#define PARAM_a    1   //-a
#define PARAM_l    2   //-l
#define PARAM_r    4   //-r
#define PARAM_i    8   //-R
#define PARAM_R    16  //-i

int maxlen;   //最长文件名长度(包含隐藏文件)
int maxlen2;  //最长文件名长度(不包含隐藏文件)
int leavelen=width;   //行剩余长度
int signino;  //输出节点编号标记

int  my_strlen(char *sss);  //计算字符串字节数，包括中文处理
int  part_param(int argcc,char **argvv);   //解析参数
void get_dirinfo(int flag,char *path);  //得到目录信息
void sort_pathname(int count,char **pathname);  //排序文件名
void deal_filename(int flag,char *fullpathname);  //处理完整路径文件名
void chose_param(int flag,char *name,char *fullpathname);  //根据参数调用函数
void show_fileinfo(struct stat st,char *name);  //打印文件信息
void show_filename(int flag,char *name);  //打印单个文件名 
void my_err(const char *err_string,int line);  //错误处理函数


//错误处理函数，打印出错误信息和错误所在行
void my_err(const char *err_string,int line) 
{
    fprintf(stderr,"line:%d",line);
    perror(err_string);
    exit(1);
}

//计算字符串字节数，并能将中文字节转化为英文
int my_strlen(char *sss)
{
    int i,sum=0;
    for(i=0;i<strlen(sss);i++)
    {
        if(sss[i]<0)
            sum++;
    }
    return (strlen(sss)-sum/3);
}

//获取文件的属性并打印
void show_fileinfo(struct stat st,char *name)
{
    
    struct passwd *psd;  //获取文件username
    struct group *grp;   //获取文件groupname
    char time[32];  //存储时间的字符串数组
    char str[11]={"----------"};
    
    //获取文件类型
    if(S_ISLNK(st.st_mode))   str[0]='l';
    if(S_ISDIR(st.st_mode))   str[0]='d';
    if(S_ISCHR(st.st_mode))   str[0]='c';
    if(S_ISBLK(st.st_mode))   str[0]='b';
    if(S_ISFIFO(st.st_mode))  str[0]='f';
    if(S_ISSOCK(st.st_mode))  str[0]='s';

    //获取文件u,g,o权限
    if(S_IRUSR & st.st_mode)  str[1]='r';
    if(S_IWUSR & st.st_mode)  str[2]='w';
    if(S_IXUSR & st.st_mode)  str[3]='x';
    if(S_IRGRP & st.st_mode)  str[4]='r';
    if(S_IWGRP & st.st_mode)  str[5]='w';
    if(S_IXGRP & st.st_mode)  str[6]='x';
    if(S_IROTH & st.st_mode)  str[7]='r';
    if(S_IWOTH & st.st_mode)  str[8]='w';
    if(S_IXOTH & st.st_mode)  str[9]='x';

    //获取用户名，组名
    psd=getpwuid(st.st_uid);
    grp=getgrgid(st.st_gid);

    strcpy(time,ctime(&st.st_mtime));  //将格林位置时间转化成正常格式
    time[strlen(time)-1]='\0';         //把字符串尾的\n换成\0
    
    if(signino==1)
        printf("%8ld ",st.st_ino);
    printf("%s %3lu %6s %6s %6ld %-s %-s\n",str,st.st_nlink,psd->pw_name,grp->gr_name,st.st_size,time,name);
}

//打印单个文件名，并对齐
void show_filename(int maxlenth,char *name)
{
    int i,len,blank;
    if(leavelen<maxlenth)  //该行不够打印一个文件名了，换行
    { 
        printf("\n");
        leavelen=width;
    }
    len=my_strlen(name);
    blank=maxlenth-len;   //在最长文件名长度范围内把剩余的长度补上空格
    printf("%s",name);
    while(blank--)
    {
        printf(" ");
    }
    printf("  ");
    leavelen-=(maxlenth+2);   //该行剩余长度
}

//显示目录下文件信息
void get_dirinfo(int flag,char *path)
{
    int count=0;
    DIR *dir;
    struct dirent *ptr;
    struct stat st;
    char **pathname,**fullpathname;
    int i,j,start,end;
    int sign_param_r=0;
    pathname=(char **)malloc(sizeof(char *)*35000);
    fullpathname=(char **)malloc(sizeof(char *)*35000);

    for(i=0;i<35000;i++)
    {
        pathname[i]=(char *)malloc(PATH_MAX+1);
        fullpathname[i]=(char *)malloc(PATH_MAX+1);
    }

    //获取目录下的文件名，文件总数和最长文件名长度，文件名存在数组pathname中
    dir=opendir(path); // 打开目录，返回DIR*形态的目录流
    if(dir==NULL)
    {
        if(errno==13)
        {
            printf("没有权限\n");
            return;
        }
        my_err("opendir",__LINE__);
    }

    while((ptr=readdir(dir))!=NULL)   //读取目录项信息，返回struct dirent结构的指针
    {
        if(ptr==NULL)
        {
            if(errno==2)
            {
                printf("虚拟文件\n");
                return;
            }
            if(errno==13)
            {
                printf("没有权限\n");
                return;
            }
            my_err("readdir",__LINE__);
        }
        strcpy(pathname[count],ptr->d_name);  //把文件名存入pathname数组里
        pathname[count][strlen(ptr->d_name)]='\0';

        if(my_strlen(ptr->d_name)>maxlen)  //得到最长文件名长度
        {
            maxlen=my_strlen(ptr->d_name);
        }
        if(pathname[count][0]!='.')
            if(my_strlen(ptr->d_name)>maxlen2)
                maxlen2=my_strlen(ptr->d_name);

        count++;
    }


    sort_pathname(count,pathname);  //文件名排序

 
    if(flag&PARAM_r)
    {
        start=-count+1;end=1;
        if(flag!=PARAM_r)
            flag=flag^PARAM_r;
        sign_param_r=1;
    }
    else
    {
        start=0;end=count;
    }
    for(i=start;i<end;i++)
    {
        strcpy(fullpathname[abs(i)],path);
        strcat(fullpathname[abs(i)],pathname[abs(i)]);   //补全文件名，得到完整路径文件名，存入fullpathname数组里
        deal_filename(flag,fullpathname[abs(i)]);  //调用
    }

    closedir(dir);   //关闭文件
    if((flag&PARAM_l)==0)
        printf("\n");

    if(flag&PARAM_R)
    {
        for(i=start;i<end;i++)
        {  
            if((flag&PARAM_a)==0)
            {
                if(pathname[abs(i)][0]=='.')
                    continue;
            }
            else
            {
                if(strcmp(pathname[abs(i)],".")==0||strcmp(pathname[abs(i)],"..")==0)
                    continue;
            }

                if(lstat(fullpathname[abs(i)],&st)==-1)
                {
                    if(errno==13)
                    {
                        printf("没有权限%d\n",__LINE__);
                        return;
                    }
                }
                if(S_ISDIR(st.st_mode))
                {
                    printf("\n%s:\n",fullpathname[abs(i)]);
                    strcat(fullpathname[abs(i)],"/");

                    get_dirinfo(flag,fullpathname[abs(i)]);

                    if(sign_param_r==1)
                    {
                        flag|=PARAM_r;
                    }
                    maxlen=maxlen2=0;
                    signino=0;
                    leavelen=width;
                }
                else
                    continue;

        }
    }
        for(i=0;i<35000;i++)
        {
            free(pathname[abs(i)]);
            free(fullpathname[abs(i)]);
        }

    

    free(pathname);
    free(fullpathname);
 }

//对文件名进行排序，冒泡
void sort_pathname(int count,char **pathname)
{
    int i,j;
    char t[PATH_MAX+1];

    for(i=0;i<count;i++)
        for(j=0;j<count-i-1;j++)
            if(strcmp(pathname[j],pathname[j+1])>0)
            {
                strcpy(t,pathname[j+1]);
                strcpy(pathname[j+1],pathname[j]);
                strcpy(pathname[j],t);
            }
}

//用完整路径文件名获取文件属性，再处理完整路径文件名解析出文件名
void deal_filename(int flag,char *fullpathname)
{
    int i,j,mark=0,k=0;
    char name[PATH_MAX+1];

    for(i=strlen(fullpathname)-1;i>0;i--)  //从后向前遍历
        if(fullpathname[i-1]=='/')  //遇到的第一个/，标记下标
        {
            mark=i;
            break;
        }
    for(j=mark;fullpathname[j]!='\0';j++)
    {
         name[k]=fullpathname[j];  //将下标从标记到尾的字符存入数组name里
         k++;
    }
    name[k]='\0';

    chose_param(flag,name,fullpathname);
}

//根据传入的参数信息，调用相应的函数
void chose_param(int flag,char *name,char *fullpathname)
{
    struct stat st;
    char *inodename;
    inodename=(char *)malloc(PATH_MAX+1);

    if(lstat(fullpathname,&st)==-1)
    {
        if(errno==13)
        {
            printf("没有权限%d\n",__LINE__);
            return;
        }
    } 

    if(flag&PARAM_i)
    {
        signino=1;
        flag=flag^PARAM_i;
        sprintf(inodename,"%8ld",st.st_ino);
        strcat(inodename," ");
        strcat(inodename,name);
    }

    switch(flag)
    {
        case PARAM_NONE:
                if(name[0]!='.')
                {
                    if(signino==1)
                        show_filename(maxlen2+9,inodename);
                    else
                        show_filename(maxlen2,name);
                }
                break;
        case PARAM_a:
                if(signino==1)
                    show_filename(maxlen+9,inodename);
                else
                    show_filename(maxlen,name);
                break;
        case PARAM_l:
                if(name[0]!='.')
                    show_fileinfo(st,name);
                break;
        case PARAM_r:
                if(name[0]!='.')
                    show_filename(maxlen2,name);
                break;
        case PARAM_R:
                if(name[0]!='.')
                {
                    if(signino==1)
                        show_filename(maxlen2+9,inodename);
                    else
                        show_filename(maxlen2,name);
                }
                break;
        case PARAM_a+PARAM_l:
                show_fileinfo(st,name);
                break;
        case PARAM_a+PARAM_R:
                if(signino==1)
                    show_filename(maxlen+9,inodename);
                else
                    show_filename(maxlen,name);
                break;
        case PARAM_l+PARAM_R:
                if(name[0]!='.')
                    show_fileinfo(st,name);
                break;              
        case PARAM_a+PARAM_l+PARAM_R:
                show_fileinfo(st,name);
                break;
        default:
                break;        
    }
}

//解析参数，得到一个整型的返回值
int part_param(int argc,char **argv)
{
    int i,k,flag;
    int num=0,j=0;
    char param[32];

    for(i=1;i<argc;i++)
    {
        if(argv[i][0]=='-')
        {
            for(k=1;k<strlen(argv[i]);k++,j++)
            {
                param[j]=argv[i][k];
            }
        }
        num++;  //保存-的个数
    }

    for(i=0;i<j;i++)
    {
        if(param[i]=='a')
        {
            flag|=PARAM_a;continue;
        }
        else if(param[i]=='l')
        {
            flag|=PARAM_l;continue;
        }
        else if(param[i]=='r')
        {
            flag|=PARAM_r;continue;
        }
        else if(param[i]=='i')
        {
            flag|=PARAM_i;continue;
        }
        else if(param[i]=='R')
        {
            flag|=PARAM_R;continue;
        }
        else
        {
            printf("my_ls:invalid option -%c\n",param[i]);
            exit(1);
        }
    }
    return flag; 
}

int main(int argc,char **argv)
{
    int i,k,flag;
    int num=0,j=0;
    struct stat st;
    char path[PATH_MAX];
    char param[32];

    
    if((argc==1)||(argc>1&&argv[argc-1][0]=='-'))  //不输入文件名或目录
    {
        strcpy(path,"./");
        path[2]='\0';
        flag=part_param(argc,argv);
        get_dirinfo(flag,path);
        return 0;   
    }

    i=1;
    do{
        flag=part_param(argc,argv);  //得到参数信息
        if(argv[i][0]=='-')  //寻找文件或目录，是参数就continue
        {
            i++;
            continue;
        }
        else
        {
            strcpy(path,argv[i]);

            if(lstat(path,&st)==-1)
            {
                my_err("stat",__LINE__);
            }

                
            if(S_ISDIR(st.st_mode))  //argv[i]是个目录
            {
                if(path[strlen(argv[i])-1]!='/')
                {
                    path[strlen(argv[i])]='/';
                    path[strlen(argv[i])+1]='\0';
                }
                else
                    path[strlen(argv[i])]='\0';

                get_dirinfo(flag,path);
                maxlen=maxlen2=0;
                i++;
            }
            else  //argv[i]是个文件
            {
                deal_filename(flag,path);
                i++;
            }
        }
    }while(i<argc);
    return 0;
}
