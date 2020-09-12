#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

//program file to execute command "cd"
int f_cd(int argc, char *argv[]){

	char *path =argv[1];
	//chdir(char *) returns 0 for success and -1 for failure
	if(argc<2){
		printf("less arguments");
		return 0;
	}
	if(chdir(path)!=0){
		perror("chdir() fialed");
	}
	
return 0;
}
