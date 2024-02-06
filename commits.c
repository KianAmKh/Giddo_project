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
#include"add_commit.h"
#include"clear_staging_area.h"
#define mxn 1024

int commits(char *message) {

    char cwd[mxn], tmp[mxn], giddo_path[mxn], staging_area_path[mxn], commits_path[mxn];
    char commits_id_path[mxn], command[mxn];
    int n, cnt = 0, q;
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
    strcpy(commits_id_path, giddo_path);
    strcat(commits_id_path, "/.commits_id.txt");
    strcpy(commits_path, giddo_path);
    strcat(commits_path, "/commits");
    sprintf(command, "%s/.ccp.txt", giddo_path);
    FILE *file = fopen(command, "r");
    fscanf(file, " %d", &q);
    fclose(file);
    if(q != -1) {
        sprintf(command, "%s/%d/is_head.txt", commits_path, q);
        file = fopen(command, "r");
        fscanf(file, " %d", &q);
        fclose(file);
        if(q == 0) {
            printf("You can't commit!\n");
            return 0;
        }
    }
    DIR *dir = opendir(staging_area_path);
    struct dirent *entry;
    while((entry = readdir(dir)) != NULL) {
        if(!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..") || !strcmp(entry->d_name, ".giddo") || !strcmp(entry->d_name, ".DS_Store")) {
            continue;
        }
        cnt++;
    }
    if(!cnt) {
        fprintf(stderr, "Staging area is empty!\n");
        return 1;
    }
    add_commit(giddo_path, commits_path, commits_id_path, message);
    if(clear_staging_area(staging_area_path, giddo_path)) {
        return 1;
    }
    return 0;

}