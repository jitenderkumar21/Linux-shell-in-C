#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>


//program file to execute command "cat"
int f_cat(int argc,char *argv[]){
	int fd;
	char ch;
	
	//eliminating invalid input
	if(argc<2){
		printf("Less arguments\n");
	}
	for(int i=1;i<argc;i++){
		//open directory in Read_Only mode
		fd=open(argv[i],O_RDONLY);
		if(fd<0){
			perror("open");
		}
		else{
			//reading the file using file descriptor(fd)
			while(read(fd,&ch,1)){
				write(STDOUT_FILENO,&ch,1);

			}	
		}
	}

return 0;
}
