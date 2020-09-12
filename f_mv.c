#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#define BUF 256

//program file to execute command "mv"

int work(int n, char *argv[], int i){
	char dest[BUF];
	strcpy(dest,argv[n-1]);
	strcat(dest,"/");
	strcat(dest,argv[i]);
	if(rename(argv[i],dest)==-1){
		perror("mv");
	}
} 

int f_mv(int argc,char *argv[]){
struct stat sts;
struct stat std;
//eliminating invalid input case
if(argc<3){
	fprintf(stderr,"usage error:\n");
	return 0;
}
else if(argc==3){
if(stat(argv[1],&sts)==0){
	if(S_ISDIR(sts.st_mode)){
		printf("mv cannot change path of a directory\n");
	}
	else{
		stat(argv[2],&std);
		//when destination file is a directory
		if(S_ISDIR(std.st_mode)){
			work(3,argv,1);	
		}
		else{
			// when src and dest both are regular files
			if(stat(argv[2],&std)==0){
				remove(argv[2]);	
			}
			if(rename(argv[1],argv[2])==-1){
				perror("mv");
			}	
		}
		
	}
}else{
		perror("mv");
		}
}
else{
	//moving multiple files to a directory
	char *dest=argv[argc-1];
	if(stat(dest,&std)==0){
		if(S_ISDIR(std.st_mode)){
			for(int i=1;i<argc-1;i++){
				stat(argv[i],&sts);
				//checking if file to be moved is directory
				if(S_ISDIR(sts.st_mode)){
					printf("mv cannot change path of a directory\n");
					continue;
				}
				work(argc,argv,i);
			}
		}else{
			perror("mv");	
			}
	}else{
		perror("mv");
		}

}
return 0;
}