

#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"
// pipe2.c: communication between two processes

int
main(int argc ,char *argv[])
{
  char a[50];
 // for(int i=0;i<5;i++)
//  {
//	  a[i]="0";
 // }

  strcpy(a,"abcd");
  a[4]='1';
  printf("%s,%d,%d",a,a[4],a[6]);

  return 0;
}


