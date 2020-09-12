#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#define buf1 5054

//program file to execute command "grep"
int f_grep(int argc,char *argv[]){
FILE *fp;
struct stat st;
char *line=NULL;
size_t len=0;
ssize_t read;
int status=0;
if(argc>2){

	for(int i=2;i<argc;i++){
		//checking if "argv[i]" file exists
			if(strcmp(argv[2],"\"")==0){
				break;
			}
		if(stat(argv[i],&st)==0){
			// open file in read mode
			fp=fopen(argv[i],"r");
			if(fp==NULL){
			//indicate error if file cannot be opened
			printf("wgrep:cannot open file :%s",argv[i]);
			status=1;
			}else{
				//read line by line in each file
				while((read=getline(&line,&len,fp)!=-1)){
					//scan pattern to be matched in each line using strstr(char *,char *)
					if(strstr(line,argv[1])){
						if(argc>3){
						printf("%s: ",argv[i]);
						}
						printf("%s",line);

					}
					
				}

			}				

		}
		else{
			// if argc is less than 3
			status=1;
			perror("stat()");
		}

	}

}
else if(argc==2){
	//taking input from stdin
	while(1){
		char input[buf1];
		fgets(input,buf1,stdin);
		if(strstr(input,argv[1])){
		printf("%s",input);	
		}
	}
	
}
else{
	printf("wgrep: searchitem[file...]\n");
	
	status=1;
}
return status;
}