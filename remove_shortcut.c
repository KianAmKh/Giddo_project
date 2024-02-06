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

int remove_shortcut(char *name) {
    char tmp[mxn];
    giddo_existance(tmp);
    if(!strcmp(tmp, "-1")) {
        fprintf(stderr, "no repo up to root!\n");
        return 1;
    }
    char giddo_path[mxn], message_path[mxn], name_path[mxn], command[mxn], hlp[mxn];
    char idk[10][mxn], idk2[10][mxn];
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
        if(!strcmp(name, hlp)) {
            target_line = cnt_line;
        }
        strcpy(idk2[cnt_line], hlp);
        fscanf(file, " %s", hlp);
        strcpy(idk[cnt_line], hlp);
        strcpy(idk[cnt_line], hlp);
        cnt_line++;
    }
    fclose(file), fclose(file2);
    if(target_line == -1) {
        fprintf(stderr, "name doesn't exist!\n");
        return 1;
    }
    file = fopen(message_path, "w"), file2 = fopen(name_path, "w");
    for(int i = 0; i < cnt_line; i++) {
        if(i == target_line) {
            continue;
        } else {
            fprintf(file, "%s\n", idk[i]);
            fprintf(file2, "%s\n", idk2[i]);
        }
    }
    fclose(file), fclose(file2);
    return 0;
}