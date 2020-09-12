//this file contains function declarations of hard-coded command functions

#include "f_mkdir.c"
#include "f_cat.c"
#include "f_cd.c"
#include "f_mv.c"
#include "f_ls.c"
#include "f_grep.c"
#include "f_chmod.c"
#include "f_cp.c"
#include "f_rm.c"
#include "compile.c"


int f_mkdir(int argc,char *argv[]);
int f_cat(int argc,char *argv[]);
int f_cd(int argc,char *argv[]);
int f_mv(int argc,char *argv[]);
int f_ls(int argc,char *argv[]);
int f_chmod(int argc,char *argv[]);
int f_cp(int argc,char *argv[]);
int f_grep(int argc,char *argv[]);
int f_rm(int argc,char *argv[]);
int compile(int argc,char *argv[]);