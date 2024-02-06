//Be Name Khoda
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<dirent.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<time.h>
#include"copy_file.h"
#include"copy_dir.h"
#include"giddo_existance.h"
#define mxn 1024

int add_tag(char *name, char *message, int commit_id, int tp) {
    char cwd[mxn], tmp[mxn], hlp[mxn], hlp2[mxn], hlp3[mxn], giddo_path[mxn], staging_area_path[mxn], commits_path[mxn];
    char tag_path[mxn], commits_id_path[mxn], branch_path[mxn], commit_n[mxn], command[mxn], command_2[mxn];
    int n, q, w, wtf = 0, ans = -1;
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
    strcpy(tag_path, giddo_path);
    strcat(tag_path, "/.tag_names.txt");
    FILE *file, *file_2;
    if(commit_id == -1) {
        sprintf(command, "%s/.ccp.txt", giddo_path);
        file = fopen(command, "r");
        fscanf(file, " %d", &q);
        fclose(file);
        printf("%d\n", q);
        commit_id = q;
    }
    file = fopen(tag_path, "r");
    while(fscanf(file, " %s", command) != EOF) {
        if(!strcmp(command, name)) {
            if(!tp) {
                printf("the tag already exists!\n");
                fclose(file);
                return 0;
            }
            wtf = 1;
            break;
        }
    }
    fclose(file);
    file = fopen(commits_id_path, "r");
    fscanf(file, " %d", &q);
    fclose(file);
    if(wtf) { //tag age rooye in commit_id zakhire shode bashe, paak mishe va jadide neveshte mishe
        printf("%d\n", q);
        for(int i = 0; i < q; i++) {
            sprintf(command, "%s/%d/tag.txt", commits_path, i);
            printf("%s\n", command);
            file = fopen(command, "r");
            if(file == NULL) {
                fprintf(stderr, "file couldn't be opened!\n");
                return 1;
            }
            printf("%s-\n", command);
            if(fscanf(file, " %s", hlp) == EOF) {
                fclose(file);
                continue;
            }
            fclose(file);
            if(!strcmp(name, hlp)) {
                ans = i;
                break;
            }
        }
        if(ans == -1) {
            fprintf(stderr, "No commit with the given tag found!(expected to be found)\n");
            return 1;
        }
        sprintf(command, "%s/%d/tag.txt", commits_path, ans);
        file = fopen(command, "w");
        fclose(file);
        sprintf(command, "%s/%d/tag.txt", commits_path, commit_id);
        file = fopen(command, "w");
        //
        fprintf(file, "%s\n", name);
        sprintf(command, "%s/%d/commit_hash.txt", commits_path, commit_id);
        file_2 = fopen(command, "r");
        fscanf(file_2, " %d", &q);
        fclose(file_2);
        fprintf(file, "commit: %d\n", q);
        sprintf(command, "%s/.config.txt", giddo_path);
        file_2 = fopen(command, "r");
        fscanf(file_2, " %*s %s %*s %s", hlp, hlp2);
        fclose(file_2);
        fprintf(file, "Author: %s . <%s>\n", hlp, hlp2);
        time_t raw_time;
        struct tm *info;
        time(&raw_time);
        info = localtime(&raw_time);
        fprintf(file, "%s", asctime(info));
        fprintf(file, "message: %s\n", message);
        fclose(file);
        return 0;
    } //overwrite mishe bazam
    sprintf(command, "%s/.tag_names.txt", giddo_path);
    file = fopen(command, "a");
    fprintf(file, "%s\n", name);
    fclose(file);
    sprintf(command, "%s/%d/tag.txt", commits_path, commit_id);
    file = fopen(command, "w");
    //
    fprintf(file, "%s\n", name);
    sprintf(command, "%s/%d/commit_hash.txt", commits_path, commit_id);
    printf("%s\n", command);
    file_2 = fopen(command, "r");
    fscanf(file_2, " %d", &q);
    fclose(file_2);
    fprintf(file, "commit: %d\n", q);
    sprintf(command, "%s/.config.txt", giddo_path);
    file_2 = fopen(command, "r");
    fscanf(file_2, " %*s %s %*s %s", hlp, hlp2);
    fclose(file_2);
    fprintf(file, "Author: %s. <%s>\n", hlp, hlp2);
    time_t raw_time;
    struct tm *info;
    time(&raw_time);
    info = localtime(&raw_time);
    fprintf(file, "%s\n", asctime(info));
    fprintf(file, "message: %s\n", message);
    fclose(file);
    return 0;

}

int show_all() {
    char cwd[mxn], tmp[mxn], hlp[mxn], hlp2[mxn], hlp3[mxn], giddo_path[mxn], staging_area_path[mxn], commits_path[mxn];
    char tag_path[mxn], commits_id_path[mxn], branch_path[mxn], commit_n[mxn], command[mxn], command_2[mxn];
    int n, q, w, cnt = 0, wtf = 0, ans = -1;
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
    strcpy(tag_path, giddo_path);
    strcat(tag_path, "/.tag_names.txt");
    FILE *file, *file_2;
    char idk[30][mxn];
    file = fopen(tag_path, "r");
    if(file == NULL) {
        fprintf(stderr, "file can't be opened in ttag!\n");
        return 1;
    }
    while(fscanf(file, " %s", hlp) != EOF) {
        strcpy(idk[cnt], hlp);
        cnt++;
    }
    fclose(file);
    for(int i = 0; i < cnt; i++) {
        for(int j = i + 1; j < cnt; j++) {
            if(strcmp(idk[i], idk[j]) > 0) {
                strcpy(idk[29], idk[i]);
                strcpy(idk[i], idk[j]);
                strcpy(idk[j], idk[29]);
            }
        }
    }
    for(int i = 0; i < cnt; i++) {
        printf("%s\n", idk[i]);
    } return 0;

}// all hooks ali

int tag_show(char *name) {
    char cwd[mxn], tmp[mxn], hlp[mxn], hlp2[mxn], hlp3[mxn], giddo_path[mxn], staging_area_path[mxn], commits_path[mxn];
    char tag_path[mxn], commits_id_path[mxn], branch_path[mxn], commit_n[mxn], command[mxn], command_2[mxn];
    int n, q, w, cnt = 0, wtf = 0, ans = -1;
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
    strcpy(tag_path, giddo_path);
    strcat(tag_path, "/.tag_names.txt");
    FILE *file, *file_2;
    file = fopen(commits_id_path, "r");
    fscanf(file, " %d", &q);
    fclose(file);
    for(int i = 0; i < q; i++) {
        sprintf(command, "%s/%d/tag.txt", commits_path, i);
        file = fopen(command, "r");
        if(file == NULL) {
            fprintf(stderr, "file couldn't be opened!\n");
            return 1;
        }
        if(fscanf(file, " %s", hlp) != EOF) {
            if(!strcmp(hlp, name)) {
                printf("%s\n", hlp);
                while(fscanf(file, " %s", hlp) != EOF) {
                    printf("%s\n", hlp);
                }
                fclose(file);
                break;
            }
            fclose(file);
        }
        fclose(file);
    }
    return 0;
}