#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>

//program file to execute command "ls"
int f_ls(int argc,char *argv[]){
	DIR *dp;
	struct dirent *dirp;
	char *file;
	if(argc==1){
		// if user input is "ls" then open the current directory and read the files/folders inside it
		file =".";
		if( (dp = opendir(file))==NULL){
			perror("ls()");
			return 0;
		}
		else{
			while((dirp = readdir(dp)) != NULL){
				// avoid printing "."(current directory) and ".."(parent directory)
				if((strcmp(dirp->d_name,".")!=0) && (strcmp(dirp->d_name,"..")!=0)){
					printf("%s\n",dirp->d_name);
				}
			}
			closedir(dp);
		}
	}
	else{
		for(int i=1;i<argc;i++){
			//file contains the directory that needs to be opened
			file=argv[i];
			printf("%s:\n",file);
			//open the current directory and read the files/folders inside it
			if((dp = opendir(file))==NULL){
				perror("ls()");
				continue;
			}
			else{
				while((dirp= readdir(dp)) !=NULL){
					// avoid printing "."(current directory) and ".."(parent directory)
					if((strcmp(dirp->d_name,".")!=0) && (strcmp(dirp->d_name,"..")!=0)){
						printf("%s\n",dirp->d_name);
					}
				}
			//closing directory
			closedir(dp);
			}
		}
	}
return 0;
}
