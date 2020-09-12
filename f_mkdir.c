#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

//program file to execute command "mkdir"
int f_mkdir(int agrc,char *argv[]){
	char *dir_name=argv[1];
	struct stat s;
	//to check if the directory already exits
	int rc=stat(dir_name,&s);
	if(rc==0){
		printf("mkdir: cannot create directory '%s' : File exists\n",dir_name);
	}
	else{
		//make directory
		mkdir(dir_name,0777);
	}
return 0;
}
