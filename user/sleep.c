#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc , char *argv[])
{
	int buf;
	
	if( argc == 2 )
	{
	       buf = atoi(argv[1]);
	       sleep(buf);	
	}
	else
	{
	       write(3,"error\n",6);	
	}

	exit(0);

}
