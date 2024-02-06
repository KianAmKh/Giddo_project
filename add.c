//Be Name Khoda
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<dirent.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include"giddo_existance.h"
#include"change_to_absolute.h"
#include"add_file.h"
#include"copy_file.h"
#include"DFS_add.h"
#include"show_state.h"
#define mxn 1024

int add(char *src) {

    char cwd[mxn], tmp[mxn], giddo_path[mxn], staging_area_path[mxn];
    char staging_area_1[mxn], staging_area_2[mxn], num_add_path[mxn], command[mxn];
    giddo_existance(tmp);
    if(!strcmp(tmp, "-1")) {
        fprintf(stderr, "no repo up to root!\n");
        return 1;
    }
    strcpy(cwd, tmp);
    strcpy(giddo_path, cwd);
    strcat(giddo_path, "/.giddo");
    strcpy(staging_area_path, giddo_path);
    strcat(staging_area_path, "/staging_area");
    strcpy(staging_area_1, giddo_path);
    strcat(staging_area_1, "/.staging_area.txt");
    strcpy(staging_area_2, giddo_path);
    strcat(staging_area_2, "/.staging_area_2.txt");
    strcpy(num_add_path, giddo_path);
    strcat(num_add_path, "/.num_add.txt");
    change_to_absolute(src);
    if(access(src, F_OK) != 0) {
        fprintf(stderr, "No such file or direcotory exists for src!\n");
        return 1;
    }
    FILE *file, *file_2;
    file = fopen(staging_area_2, "w"), file_2 = fopen(staging_area_1, "r");
    copy_file(file, file_2);
    DIR *dir = opendir(src);
    if(dir == NULL) {
        add_file(giddo_path, staging_area_path, num_add_path, src);
        return 0;
    }
    closedir(dir);
    DFS_add(giddo_path, staging_area_path, num_add_path, src);
    return 0;
}
int add_n(int num) {
    char cwd[mxn], tmp[mxn], giddo_path[mxn], staging_area_path[mxn];
    if(getcwd(cwd, mxn) == NULL) {
        fprintf(stderr, ":(\n");
        return 1;
    }
    giddo_existance(tmp);
    if(!strcmp(tmp, "-1")) {
        fprintf(stderr, "no repo up to root!\n");
        return 1;
    }
    strcpy(giddo_path, tmp);
    strcat(giddo_path, "/.giddo");
    strcpy(staging_area_path, giddo_path);
    strcat(staging_area_path, "/.staging_area.txt");
    show_state(staging_area_path, cwd, 0, num);
    return 0;
}