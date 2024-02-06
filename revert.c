//Be Name Khoda
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<dirent.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<time.h>
#include"add.h"
#include"commits.h"
#include"copy_file.h"
#include"checkout.h"
#include"clear_staging_area.h"
#include"giddo_existance.h"
#define mxn 1024

int revert(int commit_id, char *message) {
    char cwd[mxn], tmp[mxn], hlp[mxn], giddo_path[mxn], staging_area_path[mxn], commits_path[mxn];
    char commits_id_path[mxn], branch_path[mxn], commit_n[mxn], command[mxn], command_2[mxn];
    int n, q, cnt = 0;
    giddo_existance(tmp);
    if(!strcmp(tmp, "-1")) {
        fprintf(stderr, "no repo up to root!\n");
        return 1;
    }
    strcpy(cwd, tmp);
    strcpy(giddo_path, cwd);
    strcat(giddo_path, "/.giddo");
    strcpy(branch_path, giddo_path);
    strcat(branch_path, "/.branch_names.txt");
    strcpy(commits_id_path, giddo_path);
    strcat(commits_id_path, "/.commits_id.txt");
    strcpy(commits_path, giddo_path);
    strcat(commits_path, "/commits");
    strcpy(staging_area_path, giddo_path);
    strcat(staging_area_path, "/staging_area");
    FILE *file, *file_2;
    if(checkout(commit_id)) {
        fprintf(stderr, "Sadge!\n");
        return 1;
    }
    sprintf(command, "%s/.special.txt", giddo_path);
    clear_staging_area(staging_area_path, giddo_path);
    file = fopen(command, "r");
    while(fscanf(file, " %s", hlp) != EOF) {
        if(add(hlp)) return 1;
    }
    fclose(file);
    if(!strcmp(message, "lalayi")) {
        sprintf(command, "%s/%d/message.txt", commits_path, commit_id);
        file = fopen(command, "r");
        if(file == NULL) {
            fprintf(stderr, "file can't be opened in revert func!\n");
            return 1;
        }
        fscanf(file, " %s", message);
        fclose(file);
    }
    return commits(message);

}