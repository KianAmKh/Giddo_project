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

int check_if_global_config_exists() {

    char cwd[mxn], tmp[mxn];
    if(getcwd(cwd, sizeof(cwd)) == NULL) {
        fprintf(stderr, "didn't get the working directory's path!\n");
        return 1;
    }
    bool flag = 0;
    struct dirent *entry;
    DIR *dir = opendir("/Users/kianwm");
    while((entry = readdir(dir)) != NULL) {
        if(entry->d_type == DT_DIR && !strcmp(entry->d_name, "global_data")) {
            flag = 1;
            break;
        }
    }
    closedir(dir);
    if(chdir("/Users/kianwm") != 0) {
        fprintf(stderr, "can't go to home directory!\n");
        return 1;
    }
    if(!flag) {
        if(mkdir("global_data", 0755) != 0) {
            fprintf(stderr, "can't make global_data directory!\n");
            return 1;
        }
    }
    if(chdir("global_data") != 0) {
        fprintf(stderr, "can't go to global_data directory!\n");
        return 1;
    }
    if(access("config.txt", F_OK) == 0) {
        if(chdir(cwd) != 0) {
            fprintf(stderr, "can't get back to cwd!\n");
            return 1;
        }
        return 0;
    }
    FILE *file = fopen("config.txt", "w");
    if(file == NULL) {
        fprintf(stderr, "can't make the global config.txt file!\n");
        return 1;
    }
    fprintf(file, "username: Default_Name\n");
    fprintf(file, "email: default_email@sharif.edu\n");
    fclose(file);
    if(chdir(cwd) != 0) {
        fprintf(stderr, "can't get back to cwd!\n");
        return 1;
    }
    return 0;
}