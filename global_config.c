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

int global_config(int type, char *str) {
    char tmp[mxn], hlp[mxn], hlp2[mxn];
    FILE *file = fopen("/Users/kianwm/global_data/init_directories.txt", "r");
    if(file == NULL) {
        fprintf(stderr, "file couldn't be opened!1\n");
        return 1;
    }
    while(fscanf(file, " %s", tmp) != EOF) {
        memset(hlp, '\0', mxn);
        memset(hlp2, '\0', mxn);
        strcat(tmp, "/.giddo/.config.txt");
        FILE *file_2 = fopen(tmp, "r");
        if(file_2 == NULL) {
            fprintf(stderr, "file couldn't be opened!2\n");
            return 1;
        }
        int q = 0, w = 0;
        while(fscanf(file_2, "%c", &hlp[q]) != EOF) {
            q++;
        } 
        fclose(file_2);
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
            file_2 = fopen(tmp, "w");
            if(file_2 == NULL) {
                fprintf(stderr, "file couldn't be opened!3\n");
                return 1;
            }
            for(int i = 0; i < strlen(hlp2); i++) {
                fprintf(file_2, "%c", hlp2[i]);
            } fclose(file_2);
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
            file_2 = fopen(tmp, "w");
            if(file_2 == NULL) {
                fprintf(stderr, "file couldn't be opened!4\n");
                return 1;
            }
            for(int i = 0; i < strlen(hlp2); i++) {
                fprintf(file_2, "%c", hlp2[i]);
            } fclose(file_2);
        }
    }
    fclose(file);
    memset(hlp, '\0', mxn);
    memset(hlp2, '\0', mxn);
    file = fopen("/Users/kianwm/global_data/config.txt", "r");
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
        file = fopen("/Users/kianwm/global_data/config.txt", "w");
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
        file = fopen("/Users/kianwm/global_data/config.txt", "w");
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