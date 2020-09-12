#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>

//program file to execute inbuilt binaries
int compile(int argc,char *argv[]){
	char *new_argv[argc+1];
	//execvp needs an array terminated by NULL 
	for(int i=0;i<argc;i++){
		new_argv[i]=argv[i];
	}
	new_argv[argc]=NULL;
	//execvp call to create the process
	pid_t rc=execvp(argv[0],new_argv);
	return rc;
}