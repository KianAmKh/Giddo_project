//Be Name Khoda
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<dirent.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#define mxn 1024

int copy_dir(char *src_path, char *dst_path) {
    char command[mxn];
    sprintf(command, "cp -r %s %s", src_path, dst_path);
    if(system(command) != 0) {
        return 1;
    }
    return 0;
}