//Be Name Khoda
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<dirent.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include"add_file.h"
#define mxn 1024

void DFS_add(char *giddo_path, char *staging_area_path, char *num_add_path, char *path) {
    DIR *dir = opendir(path);
    if(dir == NULL) return;
    char command[mxn];
    struct dirent *entry;
    FILE *f, *f2;
    while((entry = readdir(dir)) != NULL) {
        if(!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..") || !strcmp(entry->d_name, ".giddo") || !strcmp(entry->d_name, ".DS_Store")) continue;
        if(entry->d_type == DT_REG) {
            strcpy(command, path);
            strcat(command, "/");
            strcat(command, entry->d_name);
            add_file(giddo_path, staging_area_path, num_add_path, command);
        }
        else if(entry->d_type == DT_DIR) {
            strcpy(command, path);
            strcat(command, "/");
            strcat(command, entry->d_name);
            DFS_add(giddo_path, staging_area_path, num_add_path, command);
        }
    } closedir(dir);
    return;
}