//Be Name Khoda
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<dirent.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<libgen.h>
#include"giddo_existance.h"
#include"clear_staging_area.h"
#include"copy_file.h"
#define mxn 1024

int checkout(int commid_id) {
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
    sprintf(command, "rm -rf %s/copy", giddo_path);
    if(system(command) != 0) {
        fprintf(stderr, "can't remove copy!\n");
        return 1;
    }
    sprintf(command, "%s/copy", giddo_path);
    if(mkdir(command, 0777) != 0) {
        fprintf(stderr, "can't make copy directory!\n");
        return 1;
    }
    sprintf(command, "%s/.special.txt", giddo_path);
    FILE *file, *file_2;
    file = fopen(command, "w");
    fclose(file);
    q = commid_id;
    while(q != -1) {
        sprintf(commit_n, "%s/%d", commits_path, q);
        sprintf(staging_area_path, "%s/staging_area", commit_n);
        DIR *dir = opendir(staging_area_path);
        if(dir == NULL) {
            fprintf(stderr, "couldn't open the dir in checkout function!\n");
            return 1;
        } // "cp -rpn src dst"
        struct dirent *entry;
        while((entry = readdir(dir)) != NULL) {
            if(!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..") || !strcmp(entry->d_name, ".giddo") || !strcmp(entry->d_name, ".DS_Store")) continue;
            int fnd = 0;
            sprintf(command, "%s/%s/address.txt", staging_area_path, entry->d_name);
            file = fopen(command, "r");
            //printf("lkasjdf;alskjf\n");
            fscanf(file, " %s", hlp);
            fclose(file);
            //printf("lkasjdf;alskjf\n");
            sprintf(command, "%s/.special.txt", giddo_path);
            file = fopen(command, "r");
            while(fscanf(file, " %s", command) != EOF) {
                if(!strcmp(command, hlp)) fnd = 1;
            }
            fclose(file);
            if(fnd) continue;
            sprintf(command, "%s/.special.txt", giddo_path);
            file = fopen(command, "a");
            fprintf(file, "%s\n", hlp);
            fclose(file);
            sprintf(command, "%s/%s/file.txt", staging_area_path, entry->d_name);
            file = fopen(command, "r");
            sprintf(command_2, "%s/copy%s", giddo_path, hlp);
            strcpy(hlp2, command_2);
            strcpy(hlp2, dirname(hlp2));
            sprintf(hlp3, "mkdir -p %s", hlp2);
            if(system(hlp3) != 0) {
                fprintf(stderr, "couldn't make the directories!\n");
                return 1;
            }
            file_2 = fopen(command_2, "w");
            copy_file(file_2, file);
            fclose(file), fclose(file_2);
        }
        closedir(dir);
        sprintf(command, "%s/parent.txt", commit_n);
        file = fopen(command, "r");
        fscanf(file, " %d", &q);
        fclose(file);
    }
    return 0;
}

int submit_checkout(int commid_id) {

    //check if it's ok to commit
    if(checkout(commid_id)) return 1;
    char cwd[mxn], tmp[mxn], hlp[mxn], giddo_path[mxn], staging_area_path[mxn], commits_path[mxn];
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
    FILE *file, *file_2, *file_3;
    sprintf(command, "%s/.staging_area.txt", giddo_path);
    file = fopen(command, "r");
    if(fscanf(file, " %s", command) != EOF) {
        printf("Staging area is not empty!\n");
        return 0;
    }
    fclose(file);
    // struct dirent *entry;
    // int cnt = 0;
    // if(dir == NULL) {
    //     fprintf(stderr, "heab!\n");
    //     return 1;
    // }
    // while((entry = readdir(dir)) != NULL) {
    //     if(!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..") || !strcmp(entry->d_name, ".giddo") || !strcmp(entry->d_name, ".DS_Store")) continue;
    //     cnt++;
    // } if(cnt > 0) {
    //     printf("Staging area is not empty!\n");
    //     return 0;
    // } 
    ///////////
    sprintf(command, "%s/.special.txt", giddo_path);
    file = fopen(command, "r");
    while(fscanf(file, " %s", hlp) != EOF) {
        sprintf(command_2, "%s/copy%s", giddo_path, hlp);
        file_2 = fopen(command_2, "r");
        file_3 = fopen(hlp, "w");
        copy_file(file_3, file_2);
        fclose(file_2), fclose(file_3);
    }
    fclose(file);
    sprintf(command, "%s/.ccp.txt", giddo_path);
    file = fopen(command, "w");
    fprintf(file, "%d", commid_id);
    fclose(file);
    sprintf(command, "%s/staging_area", giddo_path);
    clear_staging_area(command, giddo_path);
    return 0;

}

int checkout_branch(char *branch_name) {
    char cwd[mxn], tmp[mxn], hlp[mxn], hlp2[mxn], hlp3[mxn], giddo_path[mxn], staging_area_path[mxn], commits_path[mxn];
    char commits_id_path[mxn], branch_path[mxn], commit_n[mxn], command[mxn], command_2[mxn];
    int n, q, w, ans = -1;
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
    file = fopen(commits_id_path, "r");
    fscanf(file, " %d", &q);
    fclose(file);
    for(int i = 0; i < q; i++) {
        sprintf(command, "%s/%d/is_head.txt", commits_path, i);
        sprintf(command_2, "%s/%d/branch_name.txt", commits_path, i);
        file = fopen(command, "r");
        file_2 = fopen(command_2, "r");
        if(file == NULL || file_2 == NULL) {
            fclose(file), fclose(file_2);
            fprintf(stderr, "Files couldn't be opened successfully!\n");
            return 1;
        }
        fscanf(file_2, " %s", hlp);
        if(!strcmp(hlp, branch_name)) {
            fscanf(file, " %d", &w);
            if(w) {
                ans = i;
                break;
            }
        }
    } 
    fclose(file), fclose(file_2);
    if(ans == -1) {
        printf("No branch with the given name found!\n");
        return 0;
    }
    return submit_checkout(ans);
}

int checkout_head() {
    char cwd[mxn], tmp[mxn], hlp[mxn], hlp2[mxn], hlp3[mxn], giddo_path[mxn], staging_area_path[mxn], commits_path[mxn];
    char commits_id_path[mxn], branch_path[mxn], commit_n[mxn], command[mxn], command_2[mxn], ccp[mxn];
    int n, q, w, ans = -1;
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
    strcpy(ccp, giddo_path);
    strcat(ccp, "/.ccp.txt");
    FILE *file, *file_2;
    file = fopen(ccp, "r");
    fscanf(file, " %d", &q);
    fclose(file);
    sprintf(command, "%s/%d/branch_name.txt", commits_path, q);
    file = fopen(command, "r");
    fscanf(file, " %s", hlp);
    fclose(file);
    if(clear_staging_area(staging_area_path, giddo_path)) return 1;
    return checkout_branch(hlp);
}