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

void show_state(char *staging_area_path, char *path, int depth, int num) {
    if(depth > num) return;
    DIR *dir = opendir(path);
    if(dir == NULL) return;
    char command[mxn], hlp[mxn];
    struct dirent *entry;
    FILE *file, *file_2;
    while((entry = readdir(dir)) != NULL) {
        if(!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..") || !strcmp(entry->d_name, ".giddo") || !strcmp(entry->d_name, ".DS_Store")) continue;
        if(entry->d_type == DT_REG) {
            file = fopen(staging_area_path, "r");
            strcpy(command, path);
            strcat(command, "/");
            strcat(command, entry->d_name);
            int q = 0;
            while(fscanf(file, " %s", hlp) != EOF) {
                if(!strcmp(hlp, command)) q = 1;
            }
            for(int i = 0; i < depth; i++) {
                printf("\t");
            }
            printf("%s : ", entry->d_name);
            if(q) {
                printf("Staged :)\n");
            } 
            else {
                printf("Unstaged :(\n");
            }
            fclose(file);
        }
        else if(entry->d_type == DT_DIR) {
            strcpy(command, path);
            strcat(command, "/");
            strcat(command, entry->d_name);
            for(int i = 0; i < depth; i++) {
                printf("\t");
            }
            printf("Directory %s -> \n", entry->d_name);
            show_state(staging_area_path, command, depth + 1, num);
        }
    } closedir(dir);
    return;
}