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
#include"copy_file.h"
#include"giddo_existance.h"
#define mxn 1024

int add_branch(char *name) {
    char cwd[mxn], tmp[mxn], giddo_path[mxn], staging_area_path[mxn], commits_path[mxn];
    char commits_id_path[mxn], branch_path[mxn], commit_n[mxn], command[mxn], command_2[mxn];
    int n, cnt = 0;
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
    FILE *file = fopen(branch_path, "r"), *file_2;
    if(file == NULL) {
        fprintf(stderr, "branch_names couldn't be opened!\n");
        return 1;
    }
    while(fscanf(file, " %s", command) != EOF) {
        if(!strcmp(name, command)) {
            printf("The name already exists!\n");
            fclose(file);
            return 0;
        }
    } 
    fclose(file);
    file = fopen(commits_id_path, "r");
    if(file == NULL) {
        fprintf(stderr, "couldn't open the commits_id file!\n");
        return 1;
    }
    fscanf(file, " %d", &n);
    fclose(file);
    file = fopen(commits_id_path, "w");
    fprintf(file, "%d", n + 1);
    fclose(file);
    if(chdir(commits_path) != 0) {
        fprintf(stderr, "couldn't change the directory tp commits!\n");
        return 1;
    }
    sprintf(command, "%s/%d", commits_path, n);
    strcpy(commit_n, command);
    if(mkdir(command, 0777) != 0) {
        fprintf(stderr, "couldn't make the directory!\n");
        return 1;
    }
    // if(chdir(command) != 0) {
    //     fprintf(stderr, "couldn't change the directory tp commits!\n");
    //     return 1;
    // }
    strcat(command, "/staging_area");
    if(mkdir(command, 0777) != 0) {
        fprintf(stderr, "couldn't make the directory!\n");
        return 1;
    }
    ///////////
    strcpy(command, commit_n);
    strcat(command, "/commit_hash.txt");
    file = fopen(command, "w");
    if(file == NULL) {
        fprintf(stderr, "couldn't open the file(add_commit)!\n");
        return 1;
    }
    fprintf(file, "%d", n);
    fclose(file);
    ///////////
    strcpy(command, commit_n);
    strcat(command, "/time.txt");
    file = fopen(command, "w");
    if(file == NULL) {
        fprintf(stderr, "couldn't open the file(add_commit)!\n");
        return 1;
    }
    time_t raw_time;
    struct tm *info;
    time(&raw_time);
    info = localtime(&raw_time);
    fprintf(file, "%s", asctime(info));
    fclose(file);
    ///////////
    int hr = info->tm_hour, mn = info->tm_min, sc = info->tm_sec;
    int q = hr * 3600 + mn * 60 + sc;
    strcpy(command, commit_n);
    strcat(command, "/lin_time.txt");
    file = fopen(command, "w");
    if(file == NULL) {
        fprintf(stderr, "couldn't open the file(add_commit)!\n");
        return 1;
    }
    fprintf(file, "%d", q);
    fclose(file);
    ///////////
    strcpy(command, commit_n);
    strcat(command, "/num_files_commited.txt");
    file = fopen(command, "w");
    fprintf(file, "%d", 0);
    fclose(file);
    ///////////
    strcpy(command, commit_n);
    strcat(command, "/message.txt");
    file = fopen(command, "w");
    if(file == NULL) {
        fprintf(stderr, "couldn't open the file(add_commit)!\n");
        return 1;
    }
    fprintf(file, "No Message!");
    fclose(file);
    ///////////
    strcpy(command, commit_n);
    strcat(command, "/author_name_email.txt");
    strcpy(command_2, giddo_path);
    strcat(command_2, "/.config.txt");
    file_2 = fopen(command_2, "r");
    file = fopen(command, "w");
    if(file == NULL || file_2 == NULL) {
        fprintf(stderr, "couldn't open the file(add_commit)!\n");
        return 1;
    }
    copy_file(file, file_2);
    fclose(file), fclose(file_2);
    ///////////
    strcpy(command, commit_n);
    strcat(command, "/is_head.txt");
    file = fopen(command, "w");
    if(file == NULL) {
        fprintf(stderr, "couldn't open the file(add_commit)!\n");
        return 1;
    }
    fprintf(file, "%d", 1);
    fclose(file);
    ///////////
    strcpy(command, giddo_path);
    strcat(command, "/.ccp.txt");
    file = fopen(command, "r");
    if(file == NULL) {
        fprintf(stderr, "couldn't open the file(add_commit)!\n");
        return 1;
    }
    fscanf(file, " %d", &q);
    fclose(file);
    strcpy(command, commit_n);
    strcat(command, "/parent.txt");
    file = fopen(command, "w");
    if(file == NULL) {
        fprintf(stderr, "couldn't open the file(add_commit)!\n");
        return 1;
    }
    fprintf(file, "%d", q);
    fclose(file);
    ///////////
    strcpy(command, commit_n);
    strcat(command, "/branch_name.txt");
    file = fopen(command, "w");
    if(file == NULL) {
        fprintf(stderr, "couldn't open the file(add_commit)!\n");
        return 1;
    }
    fprintf(file, "%s", name);
    ///////////
    strcpy(command, giddo_path);
    strcat(command, "/.branch_names.txt");
    file = fopen(command, "a");
    fprintf(file, "%s\n", name);
    fclose(file);

    return 0;
}

int print_branches() {
    char cwd[mxn], tmp[mxn], giddo_path[mxn], staging_area_path[mxn], commits_path[mxn];
    char commits_id_path[mxn], branch_path[mxn], command[mxn];
    int n, cnt = 0;
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
    FILE *file = fopen(branch_path, "r");
    if(file == NULL) {
        fprintf(stderr, "branch_names couldn't be opened!\n");
        return 1;
    }
    while(fscanf(file, " %s", command) != EOF) {
        printf("%s\n", command);
    }
    fclose(file); 
    return 0;
}