#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#define buf 1024

//program file to execute command "rm"

//function to delete a directory using recursive approach
int del_dir(char *dir_name){
	DIR *dp;
	struct dirent *dirp;
	struct stat std;
	char src_p[buf];
	chdir(dir_name);
	//get current working path 
	getcwd(src_p,buf);
	if((dp = opendir(src_p))!=NULL){
		while((dirp=readdir(dp))!=NULL){
				stat(dirp->d_name,&std);
				if(S_ISDIR(std.st_mode)){
					
					if((strcmp(dirp->d_name,".")!=0) && (strcmp(dirp->d_name,"..")!=0)){
						//if dirp->d_name is a directory remove its subdirectories first
						del_dir(dirp->d_name);
						chdir(src_p);
						remove(dirp->d_name);
					}
				}
				else{
					//if dirp->d_name is a file remove it
					if(remove(dirp->d_name)!=0){
						perror("remove()");
					}
				}
		}
		
	}else{
		printf("cannot open directory\n");
	}

	
}
int f_rm(int argc,char *argv[]){
	DIR *dp;
	struct dirent *dirp;
	struct stat st;
	char *src_p;
	src_p=malloc(buf);
	getcwd(src_p,buf);
	//checking for -r flag
	if(strcmp(argv[1],"-r")!=0){
		//only files have to be removed
		for(int j=1;j<argc;j++){
			if(remove(argv[j])!=0){
				perror("remove()");
			}	
		}
	}else{
		
		for(int j=1;j<argc;j++){
			//checking if a file/folder exist 
			if(stat(argv[j],&st)==0){
				if(S_ISDIR(st.st_mode)){
					//deleting a directory
					del_dir(argv[j]);
					chdir(src_p);
					remove(argv[j]);
					
				}else{
					//deleting a file
					if(remove(argv[j])!=0){
						perror("remove()");
					}
				}				
			}
		}
		
	}
	
return 0;
}