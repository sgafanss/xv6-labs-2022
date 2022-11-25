

#include "kernel/types.h"
#include "user/user.h"

// pipe2.c: communication between two processes

int
main()
{
  int n, pid;
  int fds[2];
  char buf[100];
  
  // create a pipe, with two FDs in fds[0], fds[1].
 

  pipe(fds);
  pid = fork();
  
  if (pid == 0) {
    write(fds[1], "this is pipe2\n", 14);

  } else {
	 wait((int *)0);
    n = read(fds[0], buf, 14);
    write(1, buf, n);
    int a=8;int b=35;
    printf("%d / %d = %d\n",b,a,b/a);
  }

  exit(0);
}


