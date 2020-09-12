#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

//program file to execute command "chmod"
int f_chmod(int argc,char *argv[]){
	//eliminate invalid use of chmod
	if(argc<3){
		printf("less arguments\n");
		return 0;
	}
	char *mode=argv[1];
	char *file=argv[2];
	int i;
	i=strtol(mode,0,8);
	int rc=chmod(file,i);
	if(rc==-1){
		fprintf(stderr,"%s error in chmod-%d(%s)\n",argv[2],errno,strerror(errno));
	}
return 0;
}
