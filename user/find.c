#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"


void find (char *path, char *dst);


void find(char *path, char *dst)
{
	char buf[512], *p;
	

	int fd;struct stat st;
	struct dirent de;
  	if((fd = open(path, 0)) < 0)
	{
    	fprintf(2, "ls: cannot open %s\n", path);
    	return;
	}
	if(fstat(fd, &st) < 0)
	{
    	fprintf(2, "ls: cannot stat %s\n", path);
     	close(fd);
    return;
	}
    
	switch(st.type){
	case T_DIR:
		if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf)
		{
     		printf("ls: path too long\n");
    		break;
		}
		strcpy(buf, path);
		p = buf+strlen(buf);
  	  	*p++ = '/';
		while (read(fd,&de,sizeof(de))==sizeof(de))
		{
			if(de.inum == 0)
        	continue;
	    	memmove(p, de.name, DIRSIZ);
			p[DIRSIZ] = 0;
			if(stat(buf, &st) < 0)
			{
        		printf("ls: cannot stat %s\n", buf);
        		continue;
			}
			if (st.type==T_DIR )
		 
	    	{
				

       		      //printf("find dir %s\n",de.name);
				if (!(strcmp(de.name,".")))
				{
					continue;
				}
				if (!(strcmp(de.name,"..")))
				{
					continue;
				}

				find(buf,dst);
			}

			else if (st.type==T_FILE)
			{

        		//printf("find file %s\n",de.name);

				if(!(strcmp(de.name,dst)))
				{
					printf("%s\n",buf);
				}
			}
			
			
		}
	
	
	
	default:
	break;
		
    }
   close(fd);
}






int main(int argc ,char *argv[])
{
	
	if(argc!=3){printf("error");exit(0);}
    
  
    find(argv[1],argv[2]);

	exit(0);

}	
