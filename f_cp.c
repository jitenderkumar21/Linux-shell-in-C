#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#define buf 1024

//program file to execute command "cp"
//function to copy a file to another file
int cp_file(char *src,char *dest){
	
	FILE *f1;
	FILE *f2;
	f1=fopen(src,"r");
	char *line;
	size_t len = 0;
	ssize_t input =0;
	int start=0;
	if(f1!=NULL){
		f2=fopen(dest,"w");
		//reading source file(f1) and writing line by line in destination file(f2)
		while((input = getline(&line,&len,f1)) !=-1){
			
			fputs(line,f2);
		}
	}
	else{
		printf("connot open file (%s)\n",src);
		return 0;
	}
	//closing the files
	fclose(f1);
	fclose(f2);
	return 0;
}

//function to copy a directory to another directory
int cp_dir(char *src,char *dest,char *name){
	DIR *dp;
	struct dirent *dirp;
	char *src_p;
	char *dest_p;
	char *d_name;
	struct stat std;
	src_p=malloc(buf);
	dest_p=malloc(buf);
	d_name=malloc(buf);
	strcpy(d_name,dest);
	strcat(d_name,"/");
	strcat(d_name,name);
	mkdir(d_name,0777);
	//open source directory
	if((dp = opendir(src))!=NULL){
		
		while((dirp=readdir(dp))!=NULL){
				stat(dirp->d_name,&std);
				//check for directory
				if(S_ISDIR(std.st_mode)){
					continue;
				}
				else{
				//coping a file to another
				strcpy(dest_p,d_name);
				strcat(dest_p,"/");
				strcat(dest_p,dirp->d_name);
				strcpy(src_p,src);
				strcat(src_p,"/");
				strcat(src_p,dirp->d_name);
				cp_file(src_p,dest_p);
				}
		}
		
	}else{
		printf("cannot open directory\n");
	}
	
return 0;
}

int f_cp(int argc,char *argv[]){
DIR *dp;
struct dirent *dirp;
struct stat sts;
struct stat std;
int start=0;
//eliminating invalid input 
if(argc<3){
	printf("cp error : less arguments\n");
	return 0;
}
else if(argc==3){
if(stat(argv[1],&sts)==0){
	//check for directory
	if(S_ISDIR(sts.st_mode)){
		printf(" cp cannot copy ad directory(%s) without -r flag\n",argv[2]);
	}
	else{
		char *file=malloc(strlen(argv[2])+1);
		strcpy(file,argv[2]);
		stat(argv[2],&std);
		if(S_ISDIR(std.st_mode)){
			strcat(file,"/");
			strcat(file,argv[1]);
			//to copy a file to another file
			cp_file(argv[1],file);
		}
		else{
			cp_file(argv[1],file);
		}
		
	}
}else{
		perror("cp");
		return 0;
		}
}
else{ //when argc>3
	char *dest=malloc(1024);
	//check if destination folder exists
	if(stat(argv[argc-1],&std)==0){
		if(strcmp(argv[1],"-r")==0){
			start=1;
		}
		
		if(S_ISDIR(std.st_mode)){
			for(int i=start+1;i<argc-1;i++){
				strcpy(dest,argv[argc-1]);
				strcat(dest,"/");
				strcat(dest,argv[i]);
				//check if file to be copied exists
				if(stat(argv[i],&sts)==0){
					if(S_ISDIR(sts.st_mode)){
						char *s_name=argv[i];
						cp_dir(argv[i],argv[argc-1],s_name);
					}
					else{
						//to copy a file to folder
						cp_file(argv[i],dest);
					}
					
				}else{
					printf("%s: File does not exists\n",argv[i]);
				}
			}
		}else{
			//perror("cp");
			printf("error here");
		}
	}else{
		//perror("cp");
		printf("error here");
	}
}
return 0;	
}