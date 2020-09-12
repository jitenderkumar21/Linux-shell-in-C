#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

//program file to execute command "pwd"

int f_pwd(int argc,char *argv[]){
	char *s; 

	//getcwd() finds the current workinf directory and store in "char *s"
	printf("%s\n",getcwd(s,1000));
	
	return 0;
}
