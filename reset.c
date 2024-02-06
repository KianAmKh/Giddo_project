//Be Name Khoda
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<dirent.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include"copy_file.h"
#include"giddo_existance.h"
#include"change_to_absolute.h"
#define mxn 1024

int reset(char *fdir_path) {
    char cwd[mxn], tmp[mxn], giddo_path[mxn], staging_area[mxn];
    char command[mxn], hlp[mxn], saved_paths[50][mxn];
    int idk[mxn];
    int n, q, cnt = 0;
    FILE *file, *file_2;
    giddo_existance(tmp);
    if(!strcmp(tmp, "-1")) {
        fprintf(stderr, "no repo up to root!\n");
        return 1;
    }
    strcpy(cwd, tmp);
    strcpy(giddo_path, cwd);
    strcat(giddo_path, "/.giddo");
    strcpy(staging_area, giddo_path);
    strcat(staging_area, "/.staging_area.txt");
    change_to_absolute(fdir_path);
    if(access(fdir_path, F_OK) != 0) {
        fprintf(stderr, "No such file or direcotory exists for the path!\n");
        return 1;
    }
    for(int i = 0; i < mxn; i++) idk[i] = 0;
    DIR *dir = opendir(fdir_path);
    if(dir == NULL) {
        file = fopen(staging_area, "r");
        if(file == NULL) {
            fprintf(stderr, "file couldn't be opened in reset1!\n");
            return 1;
        }
        while(fscanf(file, " %s", command) != EOF) {
            strcpy(saved_paths[cnt], command);
            if(strcmp(fdir_path, command)) idk[cnt] = 1;
            cnt++; 
        } fclose(file);
        file = fopen(staging_area, "w");
        for(int i = 0; i < cnt; i++) {
            if(idk[i]) {
                fprintf(file, "%s\n", saved_paths[i]);
            }
        } fclose(file);
        return 0;
    }
    closedir(dir);
    file = fopen(staging_area, "r");
    if(file == NULL) {
        fprintf(stderr, "file couldn't be opened in reset1!\n");
        return 1;
    } int randooooom = strlen(fdir_path);
    while(fscanf(file, " %s", command) != EOF) {
        strcpy(saved_paths[cnt], command);
        if(strncmp(fdir_path, command, randooooom)) idk[cnt] = 1;
        cnt++; 
    } fclose(file);
    file = fopen(staging_area, "w");
    for(int i = 0; i < cnt; i++) {
        if(idk[i]) {
            fprintf(file, "%s\n", saved_paths[i]);
        }
    } fclose(file);
    return 0;

}

int reset_undo() {
    char cwd[mxn], tmp[mxn], giddo_path[mxn], staging_area[mxn], staging_area_2[mxn];
    char command[mxn], hlp[mxn];
    int idk[mxn];
    int n, q;
    FILE *file, *file_2;
    giddo_existance(tmp);
    if(!strcmp(tmp, "-1")) {
        fprintf(stderr, "no repo up to root!\n");
        return 1;
    }
    strcpy(cwd, tmp);
    strcpy(giddo_path, cwd);
    strcat(giddo_path, "/.giddo");
    strcpy(staging_area, giddo_path);
    strcat(staging_area, "/.staging_area.txt"); 
    strcpy(staging_area_2, giddo_path);
    strcat(staging_area_2, "/.staging_area_2.txt"); 
    file = fopen(staging_area, "w"), file_2 = fopen(staging_area_2, "r");
    copy_file(file, file_2);
    return 0;
}