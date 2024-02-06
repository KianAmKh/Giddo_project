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
#define mxn 1024

int replace_shortcut(char *new_message, char *name) {
    char tmp[mxn];
    giddo_existance(tmp);
    if(!strcmp(tmp, "-1")) {
        fprintf(stderr, "no repo up to root!\n");
        return 1;
    }
    char giddo_path[mxn], message_path[mxn], name_path[mxn], command[mxn], hlp[mxn], idk[10][mxn];
    strcpy(giddo_path, tmp);
    strcat(giddo_path, "/.giddo");
    strcpy(message_path, giddo_path);
    strcpy(name_path, giddo_path);
    strcat(message_path, "/.shortcut_message.txt");
    strcat(name_path, "/.shortcut_name.txt");
    int cnt_line = 0, target_line = -1;
    FILE *file, *file2;
    file = fopen(message_path, "r"), file2 = fopen(name_path, "r");
    if(file == NULL || file2 == NULL) {
        fprintf(stderr, "file couldn't be opened in replace_shortcut!\n");
        return 1;
    }
    while(fscanf(file2, " %s", hlp) != EOF) {
        if(!strcmp(hlp, name)) {
            target_line = cnt_line;
        }
        fscanf(file, " %s", hlp);
        strcpy(idk[cnt_line], hlp);
        cnt_line++;
    }
    fclose(file), fclose(file2);
    if(target_line == -1) {
        fprintf(stderr, "name doesn't exist!\n");
        return 1;
    }
    file = fopen(message_path, "w");
    for(int i = 0; i < cnt_line; i++) {
        if(i == target_line) {
            fprintf(file, "%s\n", new_message);
        } else {
            fprintf(file, "%s\n", idk[i]);
        }
    }
    fclose(file);
    return 0;
}