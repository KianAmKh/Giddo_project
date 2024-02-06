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
#include"clear_staging_area.h"
#define mxn 1024

int add_hook(char *name) {
    char cwd[mxn], tmp[mxn], hlp[mxn], hlp2[mxn], hlp3[mxn], giddo_path[mxn], staging_area_path[mxn], commits_path[mxn];
    char commits_id_path[mxn], branch_path[mxn], commit_n[mxn], command[mxn], command_2[mxn];
    int n, q;
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
    sprintf(command, "%s/.applied_hooks.txt", giddo_path);
    file = fopen(command, "r");
    if(file == NULL) {
        fprintf(stderr, "file can't be opened in hooks1!\n");
        return 1;
    }
    q = 0;
    while(fscanf(file, " %s", hlp) != EOF) {
        if(!strcmp(name, hlp)) q = 1;
    }
    fclose(file);
    if(!q) {
        file = fopen(command, "a");
        fprintf(file, "%s\n", name);
        fclose(file);
        return 0;
    } 
    else {
        printf("the hook has been already added!\n");
        return 0;
    }
}

int remove_hook(char *name) {
    char cwd[mxn], tmp[mxn], hlp[mxn], hlp2[mxn], hlp3[mxn], giddo_path[mxn], staging_area_path[mxn], commits_path[mxn];
    char commits_id_path[mxn], branch_path[mxn], commit_n[mxn], command[mxn], command_2[mxn];
    int n, q;
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
    sprintf(command, "%s/.applied_hooks.txt", giddo_path);
    file = fopen(command, "r");
    if(file == NULL) {
        fprintf(stderr, "file can't be opened in hooks1!\n");
        return 1;
    }
    q = 0;
    while(fscanf(file, " %s", hlp) != EOF) {
        if(!strcmp(name, hlp)) q = 1;
    }
    fclose(file);
    if(!q) {
        printf("the hook didn't exist!\n");
        return 0;
    } 
    else {
        char idk[15][mxn];
        file = fopen(command, "r");
        if(file == NULL) {
            fprintf(stderr, "file can't be opened in hooks1!\n");
            return 1;
        }
        q = 0;
        while(fscanf(file, " %s", hlp) != EOF) {
            strcpy(idk[q], hlp);
            q++;
        }
        fclose(file);
        file = fopen(command, "w");
        for(int i = 0; i < q; i++) {
            if(!strcmp(idk[i], name)) continue;
            fprintf(file, "%s\n", idk[i]);
        }
        fclose(file);
        return 0;
    }

}

int show_hooks_list() {
    char cwd[mxn], tmp[mxn], hlp[mxn], hlp2[mxn], hlp3[mxn], giddo_path[mxn], staging_area_path[mxn], commits_path[mxn];
    char commits_id_path[mxn], branch_path[mxn], commit_n[mxn], command[mxn], command_2[mxn];
    int n, q;
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
    sprintf(command, "%s/.hook_list.txt", giddo_path);
    FILE *file = fopen(command, "r");
    if(file == NULL) {
        fprintf(stderr, "file can't be opened in hooks1!\n");
        return 1;
    }
    while(fscanf(file, " %s\n", hlp) != EOF) {
        printf("%s\n", hlp);
    }
    fclose(file);
    return 0;
}

int show_applied_hooks() {
    char cwd[mxn], tmp[mxn], hlp[mxn], hlp2[mxn], hlp3[mxn], giddo_path[mxn], staging_area_path[mxn], commits_path[mxn];
    char commits_id_path[mxn], branch_path[mxn], commit_n[mxn], command[mxn], command_2[mxn];
    int n, q;
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
    sprintf(command, "%s/.applied_hooks.txt", giddo_path);
    file = fopen(command, "r");
    if(file == NULL) {
        fprintf(stderr, "file can't be opened in hooks1!\n");
        return 1;
    }
    while(fscanf(file, " %s", hlp) != EOF) {
        printf("%s\n", hlp);
    }
    fclose(file);
    return 0;
}