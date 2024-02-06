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

void shortcut(char *message, char *name) {
    char tmp[mxn];
    giddo_existance(tmp);
    if(!strcmp(tmp, "-1")) {
        fprintf(stderr, "no repo up to root!\n");
        return;
    }
    char giddo_path[mxn], message_path[mxn], name_path[mxn], command[mxn];
    strcpy(giddo_path, tmp);
    strcat(giddo_path, "/.giddo");
    strcpy(message_path, giddo_path);
    strcpy(name_path, giddo_path);
    strcat(message_path, "/.shortcut_message.txt");
    strcat(name_path, "/.shortcut_name.txt");
    FILE *file, *file2;
    file = fopen(message_path, "a"), file2 = fopen(name_path, "a");
    if(file == NULL || file2 == NULL) {
        fprintf(stderr, "file couldn't be opened in shortcut!\n");
        return;
    }
    fprintf(file, "%s\n", message), fprintf(file2, "%s\n", name);
    fclose(file), fclose(file2);
    return;
} 