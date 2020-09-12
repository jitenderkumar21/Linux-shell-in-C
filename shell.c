#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

//header.h includes function declaraions and command codes
#include "headers.h"

#define separators " "
#define max_arg 64
#define buf 1024


// function to find argc
int count(char *line);

//function to execute the commands(coded)
int execute(int argc,char *argv[]);

//function to execute the commands in background
int background_run(int argc,char *argv[]);

int main(){
	int run=1;
	while(run==1){	
		//setting up the shell
		printf("jitender@LAPTOP-ENIE740");
		char *s;
		//get current working directory
		getcwd(s,100);
		char *promt= "$";
		strcat(s,promt);
		printf("%s",s);
		char line[buf];
		fgets(line,buf,stdin);
		//getting arguments count=argc
		int argc =count(line);
		
		char *argv[argc];
		line[strlen(line)-1]='\0';
		
		//checking for the exit command
		if(strcmp(line,"exit")==0){
			run=0;
			exit(1);
		}
		//tokenizing the input string
		char *word=strtok(line,separators);
		int i=0;
		while(word!=NULL){
			argv[i]=word;
			word=strtok(NULL,separators);
			i+=1;
		}
		//checking if command has to executed in background or not
		if(strcmp(argv[argc-1],"&")!=0){
			execute(argc,argv);
		}
		else{
			argc=argc-1;
			argv[argc]=NULL;
			background_run(argc,argv);
		}
		
	}
	exit(1);
}

int count(char *line1){
	int a=0;
	char *line=malloc(strlen(line1)+1);
	strcpy(line,line1);
	char *word=strtok(line,separators);
	// counts the number of arguments
	while(word!=NULL){
		a+=1;
		word=strtok(NULL,separators);
	}
	return a;
}

int execute(int argc,char *argv[]){
		//checking for the command and calling the appropriate function
		if(strcmp(argv[0],"pwd")==0){
				char *s;
				printf("%s\n",getcwd(s,100));
		}
		else if(strcmp(argv[0],"mkdir")==0){
				f_mkdir(argc,argv);
		}
		else if(strcmp(argv[0],"cat")==0){
				f_cat(argc,argv);
		}
		else if(strcmp(argv[0],"cd")==0){
				f_cd(argc,argv);
		}
		else if(strcmp(argv[0],"mv")==0){
				f_mv(argc,argv);
		}
		else if(strcmp(argv[0],"ls")==0){
				f_ls(argc,argv);
		}
		else if(strcmp(argv[0],"grep")==0){
				f_grep(argc,argv);
		}
		else if(strcmp(argv[0],"cp")==0){
				f_cp(argc,argv);
		}
		else if(strcmp(argv[0],"chmod")==0){
				f_chmod(argc,argv);
		}
		else if(strcmp(argv[0],"rm")==0){
				f_rm(argc,argv);
		}
		//running inbuilt binaries
		else{	pid_t rc;
			int status;
			
				rc=fork();
				if(rc<0){
					//fork() failed
					printf("Fork failed");
				}
				else if(rc==0){
					//child process
					pid_t rc2 = compile(argc,argv);
					if(rc2==-1){
						printf("%s :command not found\n",argv[0]);
						exit(1);
					}
	
				}
				else{
					//parent process
					waitpid(rc,&status,0);
				}
		}	
	return 0;
}

int background_run(int argc,char *argv[]){
	pid_t rc;
	int status;
	rc=fork();
	if(rc<0){
		//fork() failed
		printf("Fork failed");
		exit(0);
	}
	else if(rc==0){
		//child process
		execute(argc,argv);
		exit(1);
	}
		return 0;
}