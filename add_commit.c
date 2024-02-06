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
#include"copy_dir.h"
#define mxn 1024
// num_files_commited.txt
// lin_time.txt
// time.txt
// autor_name_email.txt
// message.txt
// commit_hash.txt
// parent.txt
// branch_name.txt
// is_head.txt
int add_commit(char *giddo_path, char *commits, char *commits_id_path, char *message) {
    int n, par, q;
    char command[mxn], command_2[mxn], staging_area_path[mxn], commit_n[mxn];
    FILE *file = fopen(commits_id_path, "r"), *file_2;
    if(file == NULL) {
        fprintf(stderr, "couldn't open the commits_id file!\n");
        return 1;
    }
    fscanf(file, "%d", &n);
    fclose(file);
    file = fopen(commits_id_path, "w");
    fprintf(file, "%d", n + 1);
    fclose(file);
    if(chdir(commits) != 0) {
        fprintf(stderr, "couldn't change the directory tp commits!\n");
        return 1;
    }
    sprintf(command, "%s/%d", commits, n);
    strcpy(commit_n, command);
    if(mkdir(command, 0777) != 0) {
        fprintf(stderr, "couldn't make the directory!\n");
        return 1;
    }
    if(chdir(command) != 0) {
        fprintf(stderr, "couldn't change the directory tp commits!\n");
        return 1;
    }
    sprintf(staging_area_path, "%s/staging_area", giddo_path);
    if(copy_dir(staging_area_path, command)) {
        fprintf(stderr, "system cp -r didn't work successfully!\n");// -rT bood
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
    q = hr * 3600 + mn * 60 + sc;
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
    int cnt = 0;
    strcpy(command_2, giddo_path);
    strcat(command_2, "/staging_area");
    DIR *dir = opendir(command_2);
    struct dirent *entry;
    while((entry = readdir(dir)) != NULL) {
        cnt++;
    } cnt -= 2;
    fprintf(file, "%d", cnt);
    fclose(file);
    closedir(dir);
    ///////////
    strcpy(command, commit_n);
    strcat(command, "/message.txt");
    file = fopen(command, "w");
    if(file == NULL) {
        fprintf(stderr, "couldn't open the file(add_commit)!\n");
        return 1;
    }
    fprintf(file, "%s", message);
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
    fscanf(file, " %d", &par);
    fclose(file);
    file = fopen(command, "w");
    if(file == NULL) {
        fprintf(stderr, "couldn't open the file(add_commit)!\n");
        return 1;
    }
    fprintf(file, "%d", n);
    fclose(file);
    ///////////
    strcpy(command, commit_n);
    strcat(command, "/parent.txt");
    file = fopen(command, "w");
    if(file == NULL) {
        fprintf(stderr, "couldn't open the file(add_commit)!\n");
        return 1;
    }
    fprintf(file, "%d", par);
    fclose(file);
    ///////////
    strcpy(command, commit_n);
    strcat(command, "/branch_name.txt");
    file = fopen(command, "w");
    if(file == NULL) {
        fprintf(stderr, "couldn't open the file(add_commit)!\n");
        return 1;
    }
    if(n == 0) {
        fprintf(file, "Master\n");
        fclose(file);
    }
    else if(n > 0) {
        sprintf(command, "%s/%d", commits, par);
        strcat(command, "/branch_name.txt");
        file_2 = fopen(command, "r");
        if(file_2 == NULL) {
            fprintf(stderr, "couldn't open the file(add_commit)!\n");
            return 1;
        }
        copy_file(file, file_2);
        fclose(file), fclose(file_2);
    }
    ///////////
    strcpy(command, commit_n);
    strcat(command, "/tag.txt");
    file = fopen(command, "w");
    if(file == NULL) {
        fprintf(stderr, "couldn't open the file(add_commit)!\n");
        return 1;
    }
    fclose(file);
    ///////////
    if(n == 0) return 0;
    sprintf(command, "%s/%d", commits, par);
    strcat(command, "/is_head.txt");
    file = fopen(command, "w");
    fprintf(file, "%d", 0);
    fclose(file);
    ///////////
    return 0;

}