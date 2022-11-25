#include "kernel/types.h"
#include "user/user.h"

//primes.c

#define stop_num 35

int main()
{
	int num[stop_num];
	num[0]=stop_num-1; //int num[stop_num]=[totalnumfrom2~stop_num,2,3,,stopnum]
	for(int i=1;i<=stop_num-1;i++)
	{
		num[i]=i+1;
	}
	int fds[2];
	pipe(fds);
	write(fds[1],num,4*(stop_num));
	int pid;

	while(1)
	{
	pid = fork();
	if(pid==0)
	{
		//read
		int tem_count_value;
	        int *tem_count=&tem_count_value;
                read(fds[0],tem_count,4);
		
                int tem[tem_count_value];
                for(int j=0;j<=(tem_count_value-1);j++)
                {
                        read(fds[0],tem+j,4);

                }
		printf("prime %d\n",tem[0]);

		if(tem_count_value==1)
		{
			break;
		}

		//write
		int new_tem_count;
		int cal = tem[tem_count_value-1]/tem[0];
                int count=1;
		for(int k=1;k<=cal;k++)
		{
			for(int m=1;m<=tem_count_value-1;m++)
			{
				if(tem[m]==k*tem[0])
				{tem[m]=0;count=count+1;break;}
			}
		}

		new_tem_count=tem_count_value-count;
		int new_tem[new_tem_count];
                int p = 0;
		for(int n=1;n<=tem_count_value-1;n++)
		{
			if(tem[n]!=0)
			{
				new_tem[p]=tem[n];
			        p=p+1;
			}
		}
		



	        write(fds[1],&new_tem_count,4);
		write(fds[1],new_tem,4*new_tem_count);
		
		
	



	}
	else
	{
	        wait((int *)0);
		exit(0);
	}
        }
	exit(0);
}
