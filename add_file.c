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
#define mxn 1024

int add_file(char* giddo_path, char* staging_area_path, char* num_add_path, char* src) {
    int n;
    char command[mxn], command_file[mxn];
    strcpy(command, giddo_path);
    strcat(command, "/.staging_area.txt");
    FILE *f, *f2;
    f = fopen(command, "r");
    while(fscanf(f, " %s", command) != EOF) {
        if(!strcmp(command, src)) {
            fclose(f);
            return 0;
        }
    }
    fclose(f);
    f = fopen(num_add_path, "r");
    if(f == NULL) {
        fprintf(stderr, "couldn't open the file!\n");
        return 1;
    }
    fscanf(f, " %d", &n);
    fclose(f);
    f = fopen(num_add_path, "w");
    if(f == NULL) {
        fprintf(stderr, "couldn't open the file!\n");
        return 1;
    }
    fprintf(f, "%d", n + 1);
    fclose(f);
    sprintf(command, "%s/%d", staging_area_path, n);
    if(mkdir(command, 0777) != 0) {
        fprintf(stderr, "couldn't make the directory!\n");
        return 1;
    }
    strcpy(command_file, command);
    strcat(command_file, "/address.txt");
    f = fopen(command_file, "w");
    if(f == NULL) {
        fprintf(stderr, "couldn't open the command file!\n");
        return 1;
    }
    fprintf(f, "%s", src);
    fclose(f);
    strcpy(command_file, command);
    strcat(command_file, "/file.txt");
    f = fopen(src, "r");
    f2 = fopen(command_file, "w");
    if(f == NULL || f2 == NULL) {
        fprintf(stderr, "couldn't open the file.txt or src file!\n");
        return 1;
    }
    copy_file(f2, f);
    fclose(f), fclose(f2);
    //
    strcpy(command, giddo_path);
    strcat(command, "/.staging_area.txt");
    f = fopen(command, "a");
    if(f == NULL) {
        fprintf(stderr, "couldn't open the tracking file!\n");
        return 1;
    }
    fprintf(f, "%s\n", src);
    fclose(f);
    //
    strcpy(command, giddo_path);
    strcat(command, "/.tracking_files.txt");
    f = fopen(command, "r");
    if(f == NULL) {
        fprintf(stderr, "couldn't open the tracking file!\n");
        return 1;
    }
    while(fscanf(f, " %s", command) != EOF) {
        if(!strcmp(src, command)) {
            fclose(f);
            return 0;
        }
    }
    fclose(f);
    strcpy(command, giddo_path);
    strcat(command, "/.tracking_files.txt");
    f = fopen(command, "a");
    fprintf(f, "%s\n", src);
    fclose(f);
    return 0;
}