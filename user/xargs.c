#include "kernel/types.h"
#include "user/user.h"


int main(int argc, char *argv[])
{
    char buf[100],*p;
    p=buf;
    char*q[10];
    q[0]=buf;
    int pid;
    char *arg[argc+1];
    for (int i = 0; i < argc-1; i++)
    {
        arg[i]=argv[i+1];
    }
//read standard input till the last "\n"
    int n=1;
    int line=0;
    while(1)
    {        
        do
        {       
            n=read(0,p,1);
            if (n==0)
            {
                break;
            }
                        p=p+1;

        } while (((p-1)[0])!='\n');
        
        if (n==0)
        {
            break;
        }
        
        line=line+1;
        (p-1)[0]=0;
        q[line]=p;
    }

//execute the command
for (int j = 0; j <line; j++)
    {
      pid = fork();
        if (pid==0)
            {
            arg[argc-1]=q[0];
            arg[argc]=0;
            exec(arg[0], arg);
            printf("error\n");
            }
        else
        {
           // printf("round: %d  pid: %d\n",j,getpid());
        }
    }   
    wait(0);
    exit(0);
}