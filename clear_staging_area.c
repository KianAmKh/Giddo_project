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

int clear_staging_area(char *st_path, char *giddo_path) {
    DIR *dir = opendir(st_path);
    if(dir == NULL) {
        fprintf(stderr, "error to open the st_path directory!\n");
        return 1;
    }
    char komaaaaaaaak[mxn];
    strcpy(komaaaaaaaak, giddo_path);
    strcat(komaaaaaaaak, "/.staging_area.txt");
    FILE *file = fopen(komaaaaaaaak, "w");
    fclose(file);
    strcpy(komaaaaaaaak, giddo_path);
    strcat(komaaaaaaaak, "/.staging_area_2.txt");
    file = fopen(komaaaaaaaak, "w");
    fclose(file);
    struct dirent *entry;
    while((entry = readdir(dir)) != NULL) {
        if(!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..") || !strcmp(entry->d_name, ".giddo") || !strcmp(entry->d_name, ".DS_Store")) continue;
        char command[mxn], hlp[mxn];
        strcpy(hlp, st_path);
        strcat(hlp, "/");
        strcat(hlp, entry->d_name);
        sprintf(command, "rm -rf %s", hlp);
        if(system(command) != 0) {
            return 1;
        }

    }
    return 0;
}