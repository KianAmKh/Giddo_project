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

int check_if_init_directories_exists() {

    char cwd[mxn], tmp[mxn];
    if(getcwd(cwd, sizeof(cwd)) == NULL) {
        fprintf(stderr, "didn't get the working directory's path!\n");
        return 1;
    }
    if(chdir("/Users/kianwm/global_data") != 0) {
        fprintf(stderr, "can't go to global_data directory!\n");
        return 1;
    }
    if(access("init_directories.txt", F_OK) == 0) {
        if(chdir(cwd) != 0) {
            fprintf(stderr, "can't get back to cwd!\n");
            return 1;
        }
        return 0;
    }
    FILE *file = fopen("init_directories.txt", "w");
    if(file == NULL) {
        fprintf(stderr, "can't make the global init_directories.txt file!\n");
        return 1;
    }
    fclose(file);
    if(chdir(cwd) != 0) {
        fprintf(stderr, "can't get back to cwd!\n");
        return 1;
    }
    return 0;
}