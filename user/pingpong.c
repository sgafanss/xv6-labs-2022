#include "kernel/types.h"
#include "user/user.h"

//pingpong.c

int main()
{
        int pid;int fds[2];
        char buf[100];

        pipe(fds);

        pid = fork();
        if(pid == 0)
        {
               read(fds[0],buf,4) ;
	       printf("%d: received %s\n", getpid(),buf);
               write(fds[1],"pong",4);	      
	       exit(0);
        }
        else
        {
               write(fds[1],"ping",4);
               wait((int *)0);
	       //printf("chile is down");
               read(fds[0],buf,4);
	       //printf("read from child is %s\n",buf+1);
	       printf("%d: received %s\n", getpid(),buf);
        }
	return 0;
}


