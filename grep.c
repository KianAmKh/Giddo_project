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
#include"change_to_absolute.h"
#include"clear_staging_area.h"
#define mxn 1024

int grep(char *src, char *word, int tp) {
    char cwd[mxn], tmp[mxn], hlp[mxn], hlp2[mxn], hlp3[mxn], giddo_path[mxn], staging_area_path[mxn], commits_path[mxn];
    char commits_id_path[mxn], branch_path[mxn], commit_n[mxn], command[mxn], command_2[mxn];
    int n, q;
    giddo_existance(tmp);
    if(!strcmp(tmp, "-1")) {
        fprintf(stderr, "no repo up to root!\n");
        return 1;
    }
    strcpy(cwd, tmp);
    strcpy(giddo_path, cwd);
    strcat(giddo_path, "/.giddo");
    strcpy(branch_path, giddo_path);
    strcat(branch_path, "/.branch_names.txt");
    strcpy(commits_id_path, giddo_path);
    strcat(commits_id_path, "/.commits_id.txt");
    strcpy(commits_path, giddo_path);
    strcat(commits_path, "/commits");
    strcpy(staging_area_path, giddo_path);
    strcat(staging_area_path, "/staging_area");
    FILE *file, *file_2;
    change_to_absolute(src);
    file = fopen(src, "r");
    if(file == NULL) {
        fprintf(stderr, "can't find the file!\n");
        return 1;
    }
    int cnt = 0;
    while(fgets(hlp, mxn, file) != NULL) {
        cnt++;
        n = strlen(hlp), q = strlen(word);
        int st = -1;
        for(int i = 0; i <= n - q; i++) {
            int check = 1;
            for(int j = i; j < i + q; j++) {
                if(hlp[j] != word[j - i]) check = 0;
            }
            if(check) {
                st = i;
                break;
            }
        }
        if(st == -1) continue;
        if(tp) {
            printf("%d. ", cnt);
        }
        for(int i = 0; i < st; i++) {
            printf("%c", hlp[i]);
        }
        for(int i = st; i < st + q; i++) {
            printf("\e[33m%c\e[m", hlp[i]);
        }
        for(int i = st + q; i < n; i++) {
            printf("%c", hlp[i]);
        } printf("\n");
    }
    fclose(file);
    return 0;

}