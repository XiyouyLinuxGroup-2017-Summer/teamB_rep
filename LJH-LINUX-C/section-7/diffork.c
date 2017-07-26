/*************************************************************************
	> File Name: diffork.c
	> Author:九五二七 
	> Mail: 
	> Created Time: 2017年07月24日 星期一 11时26分34秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

int globVar = 5; 

int  main ()
{
    pid_t  pid;
    int i;
    int var = 1;
    printf("fork is different with vfork \n");

    //pid = fork();
    pid = vfork();

    switch(pid) {
        case 0:
            i=3;
            while(i--)
            {
                printf("Child process is running \n");
                globVar++;
                var++;
            //    sleep(1);
            }
            printf("Child's globVar = %d,var = %d\n",globVar,var);
            exit(0);
        case -1:
            perror("parents proess is running \n");
            exit(0);
        default:
            i = 5;
            while (i--) 
            {
                printf("parents process is running \n");
                globVar++;
                var++;
              
                //  sleep(1);
            }    
            printf("parents's globVar = %d,var = %d\n",globVar,var);    
            exit(0);
    }
}
