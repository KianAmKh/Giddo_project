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

int reg_config(int type, char *str) {
    char cwd[mxn], tmp[mxn], hlp[mxn], hlp2[mxn];
    if(getcwd(cwd, mxn) == NULL) {
        fprintf(stderr, "couldn't get the working directory!\n");
        return 1;
    }
    DIR *dir = opendir(".giddo");
    if(dir == NULL) {
        fprintf(stderr, "couldn't open the directory!\n");
        return 1;
    }
    closedir(dir);
    if(chdir(".giddo") != 0) {
        fprintf(stderr, "couldn't change the directory!\n");
        return 1;
    }
    memset(hlp, '\0', mxn);
    memset(hlp2, '\0', mxn);
    strcpy(tmp, cwd);
    strcat(tmp, "/.giddo/.config.txt");
    FILE *file = fopen(tmp, "r");
    if(file == NULL) {
        fprintf(stderr, "file couldn't be opened!5\n");
        return 1;
    }
    int q = 0, w = 0;
    while(fscanf(file, "%c", &hlp[q]) != EOF) {
        q++;
    } 
    fclose(file);
    if(type == 1) {
        char *ptr = strstr(hlp, "username: ");
        strncpy(hlp2, hlp, (ptr - hlp + 10));
        strcat(hlp2, str);
        for(int i = (ptr - hlp + 10); hlp[i] != '\n'; i++) {
            w = i + 1;
        }
        for(int i = w; i < q; i++) {
            hlp2[strlen(hlp2)] = hlp[i];
        }
        file = fopen(tmp, "w");
        if(file == NULL) {
            fprintf(stderr, "file couldn't be opened!6\n");
            return 1;
        }
        for(int i = 0; i < strlen(hlp2); i++) {
            fprintf(file, "%c", hlp2[i]);
        } fclose(file);
    }
    if(type == 2) {
        char *ptr = strstr(hlp, "email: ");
        strncpy(hlp2, hlp, (ptr - hlp + 7));
        strcat(hlp2, str);
        for(int i = (ptr - hlp + 7); hlp[i] != '\n'; i++) {
            w = i + 1;
        }
        for(int i = w; i < q; i++) {
            hlp2[strlen(hlp2)] = hlp[i];
        }
        file = fopen(tmp, "w");
        if(file == NULL) {
            fprintf(stderr, "file couldn't be opened!7\n");
            return 1;
        }
        for(int i = 0; i < strlen(hlp2); i++) {
            fprintf(file, "%c", hlp2[i]);
        } fclose(file);
    }
    return 0;
}