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

void change_to_absolute(char *address) {
    if(*(address) != '/') {
        char kian[mxn];
        memset(kian, '\0', mxn);
        if(getcwd(kian, mxn) == NULL) {
            fprintf(stderr, "can't get cwd!\n");
            strcpy(address, "-1");
            return;
        }
        strcat(kian, "/");
        strcat(kian, address);
        memset(address, '\0', mxn);
        strcpy(address, kian);
    }
    return;
}