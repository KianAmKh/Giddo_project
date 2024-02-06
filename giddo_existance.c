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

void giddo_existance(char *ans) {

    char *fault;
    fault = calloc(5, sizeof(char));
    strcpy(fault, "-1");
    char cwd[mxn], tmp[mxn];
    if(getcwd(cwd, mxn) == NULL) {
        fprintf(stderr, "didn't get the working directory's path!\n");
        strcpy(ans, fault);
        return;
    }
    strcpy(tmp, cwd);
    do {
        if(access(".giddo", F_OK) == 0) {
            if(chdir(cwd) != 0) {
                fprintf(stderr, "can't go to cwd!\n");
                strcpy(ans, fault);
                return;
            }
            strcpy(ans, tmp);
            return;
        }
        if(chdir("..") != 0) {
            fprintf(stderr, "can't go to parent!\n");
            strcpy(ans, fault);
            return;
        }
        if(getcwd(tmp, mxn) == NULL) {
            fprintf(stderr, "didn't get the working directory's path!\n");
            strcpy(ans, fault);
            return;
        } 
    } while(strcmp("/Users/kianwm", tmp) != 0);
    strcpy(ans, fault);
    return;
}