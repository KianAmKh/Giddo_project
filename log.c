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
#include"copy_file.h"
#include"copy_dir.h"
#define mxn 1024

int log_n(int k) {
    char cwd[mxn], tmp[mxn], giddo_path[mxn], commits_path[mxn];
    char command[mxn], hlp[mxn];
    int n, q;
    FILE *file, *file_2;
    giddo_existance(tmp);
    if(!strcmp(tmp, "-1")) {
        fprintf(stderr, "no repo up to root!\n");
        return 1;
    }
    strcpy(cwd, tmp);
    strcpy(giddo_path, cwd);
    strcat(giddo_path, "/.giddo");
    strcpy(commits_path, giddo_path);
    strcat(commits_path, "/commits");
    strcpy(command, giddo_path);
    strcat(command, "/.commits_id.txt");
    file = fopen(command, "r");
    if(file == NULL) {
        fprintf(stderr, "file can't be opened in log!\n");
        return 1;
    }
    fscanf(file, " %d", &n);
    n--;
    fclose(file);
    for(int i = n; (i > n - k) && (i > -1); i--) {
        printf("Commit ID : %d\n", i);
        sprintf(command, "%s/%d", commits_path, i);
        //
        sprintf(hlp, "%s/time.txt", command);
        file = fopen(hlp, "r");
        if(file == NULL) {
            fprintf(stderr, "file can't be opened in log!\n");
            return 1;
        }
        fgets(hlp, sizeof(hlp), file);
        printf("%s", hlp);
        fclose(file);
        //
        sprintf(hlp, "%s/message.txt", command);
        file = fopen(hlp, "r");
        if(file == NULL) {
            fprintf(stderr, "file can't be opened in log!\n");
            return 1;
        }
        fgets(hlp, sizeof(hlp), file);
        printf("message: %s\n", hlp);
        fclose(file);
        //
        sprintf(hlp, "%s/author_name_email.txt", command);
        file = fopen(hlp, "r");
        if(file == NULL) {
            fprintf(stderr, "file can't be opened in log!\n");
            return 1;
        }
        fgets(hlp, sizeof(hlp), file);
        printf("%s", hlp);
        fclose(file);
        //
        sprintf(hlp, "%s/branch_name.txt", command);
        file = fopen(hlp, "r");
        if(file == NULL) {
            fprintf(stderr, "file can't be opened in log!\n");
            return 1;
        }
        fscanf(file, " %s", hlp);
        printf("branch name : %s\n", hlp);
        fclose(file);
        //
        sprintf(hlp, "%s/num_files_commited.txt", command);
        file = fopen(hlp, "r");
        if(file == NULL) {
            fprintf(stderr, "file can't be opened in log!\n");
            return 1;
        }
        fscanf(file, " %d", &q);
        printf("number of commited files : %d\n", q);
        fclose(file);
    } return 0;

}
int log_branch(char *branch_name) {
    char cwd[mxn], tmp[mxn], giddo_path[mxn], commits_path[mxn], branch_path[mxn];
    char command[mxn], hlp[mxn];
    int n, q;
    FILE *file, *file_2;
    giddo_existance(tmp);
    if(!strcmp(tmp, "-1")) {
        fprintf(stderr, "no repo up to root!\n");
        return 1;
    }
    strcpy(cwd, tmp);
    strcpy(giddo_path, cwd);
    strcat(giddo_path, "/.giddo");
    strcpy(commits_path, giddo_path);
    strcat(commits_path, "/commits");
    strcpy(branch_path, giddo_path);
    strcat(branch_path, "/.branch_names.txt");
    strcpy(command, giddo_path);
    strcat(command, "/.commits_id.txt");
    file = fopen(command, "r");
    if(file == NULL) {
        fprintf(stderr, "file can't be opened in log_branch!\n");
        return 1;
    }
    fscanf(file, " %d", &n);
    n--;
    fclose(file);
    file = fopen(branch_path, "r");
    if(file == NULL) {
        fprintf(stderr, "file can't be opened in log_branch!\n");
        return 1;
    }
    bool boo = 0;
    while(fscanf(file, " %s", command) != EOF) {
        if(!strcmp(command, branch_name)) {
            boo = 1;
            break;
        }
    }
    if(!boo) {
        fprintf(stderr, "No branch with the given name!\n");
        return 1;
    }
    for(int i = n; i > -1; i--) {
        sprintf(command, "%s/%d", commits_path, i);
        sprintf(branch_path, "%s/branch_name.txt", command);
        file = fopen(branch_path, "r");
        if(file == NULL) {
            fprintf(stderr, "file can't be opened in log_branch!\n");
            return 1;
        }
        fscanf(file, " %s", hlp);
        fclose(file);
        if(strcmp(hlp, branch_name)) continue;
        printf("Commit ID : %d\n", i);
        //
        sprintf(hlp, "%s/time.txt", command);
        file = fopen(hlp, "r");
        if(file == NULL) {
            fprintf(stderr, "file can't be opened in log_branch!\n");
            return 1;
        }
        fgets(hlp, sizeof(hlp), file);
        printf("%s", hlp);
        fclose(file);
        //
        sprintf(hlp, "%s/message.txt", command);
        file = fopen(hlp, "r");
        if(file == NULL) {
            fprintf(stderr, "file can't be opened in log_branch!\n");
            return 1;
        }
        fgets(hlp, sizeof(hlp), file);
        printf("message: %s\n", hlp);
        fclose(file);
        //
        sprintf(hlp, "%s/author_name_email.txt", command);
        file = fopen(hlp, "r");
        if(file == NULL) {
            fprintf(stderr, "file can't be opened in log_branch!\n");
            return 1;
        }
        fgets(hlp, sizeof(hlp), file);
        printf("%s", hlp);
        fclose(file);
        //
        sprintf(hlp, "%s/branch_name.txt", command);
        file = fopen(hlp, "r");
        if(file == NULL) {
            fprintf(stderr, "file can't be opened in log_branch!\n");
            return 1;
        }
        fscanf(file, " %s", hlp);
        printf("branch name : %s\n", hlp);
        fclose(file);
        //
        sprintf(hlp, "%s/num_files_commited.txt", command);
        file = fopen(hlp, "r");
        if(file == NULL) {
            fprintf(stderr, "file can't be opened in log_branch!\n");
            return 1;
        }
        fscanf(file, " %d", &q);
        printf("number of commited files : %d\n", q);
        fclose(file);
    } return 0;

}
int log_author(char *author_name) {
    char cwd[mxn], tmp[mxn], giddo_path[mxn], commits_path[mxn], author_path[mxn];
    char command[mxn], hlp[mxn];
    int n, q;
    FILE *file, *file_2;
    giddo_existance(tmp);
    if(!strcmp(tmp, "-1")) {
        fprintf(stderr, "no repo up to root!\n");
        return 1;
    }
    strcpy(cwd, tmp);
    strcpy(giddo_path, cwd);
    strcat(giddo_path, "/.giddo");
    strcpy(commits_path, giddo_path);
    strcat(commits_path, "/commits");
    strcpy(command, giddo_path);
    strcat(command, "/.commits_id.txt");
    file = fopen(command, "r");
    if(file == NULL) {
        fprintf(stderr, "file can't be opened in log_auth1!\n");
        return 1;
    }
    fscanf(file, " %d", &n);
    n--;
    fclose(file);
    int cnt_voov = 0;
    for(int i = n; i > -1; i--) {
        sprintf(command, "%s/%d", commits_path, i);
        sprintf(author_path, "%s/author_name_email.txt", command);
        file = fopen(author_path, "r");
        if(file == NULL) {
            fprintf(stderr, "file can't be opened in log_auth2!\n");
            return 1;
        }
        fscanf(file, " %*s %s", hlp);
        fclose(file);
        if(strcmp(hlp, author_name)) continue;
        cnt_voov++;
        printf("Commit ID : %d\n", i);
        //
        sprintf(hlp, "%s/time.txt", command);
        file = fopen(hlp, "r");
        if(file == NULL) {
            fprintf(stderr, "file can't be opened in log_auth3!\n");
            return 1;
        }
        fgets(hlp, sizeof(hlp), file);
        printf("%s", hlp);
        fclose(file);
        //
        sprintf(hlp, "%s/message.txt", command);
        file = fopen(hlp, "r");
        if(file == NULL) {
            fprintf(stderr, "file can't be opened in log_auth4!\n");
            return 1;
        }
        fgets(hlp, sizeof(hlp), file);
        printf("message: %s\n", hlp);
        fclose(file);
        //
        sprintf(hlp, "%s/author_name_email.txt", command);
        file = fopen(hlp, "r");
        if(file == NULL) {
            fprintf(stderr, "file can't be opened in log_auth5!\n");
            return 1;
        }
        fgets(hlp, sizeof(hlp), file);
        printf("%s", hlp);
        fclose(file);
        //
        sprintf(hlp, "%s/branch_name.txt", command);
        file = fopen(hlp, "r");
        if(file == NULL) {
            fprintf(stderr, "file can't be opened in log_auth6!\n");
            return 1;
        }
        fscanf(file, " %s", hlp);
        printf("branch name : %s\n", hlp);
        fclose(file);
        //
        sprintf(hlp, "%s/num_files_commited.txt", command);
        file = fopen(hlp, "r");
        if(file == NULL) {
            fprintf(stderr, "file can't be opened in log_auth7!\n");
            return 1;
        }
        fscanf(file, " %d", &q);
        printf("number of commited files : %d\n", q);
        fclose(file);
    }
    if(!cnt_voov) {
        printf("There is no commit by this author!\n");
    } 
    return 0;

}
int log_time(int hr, int mn, int sc, int tp) { //tp = 0 (since), tp = 1 (before)
    char cwd[mxn], tmp[mxn], giddo_path[mxn], commits_path[mxn], lin_time_path[mxn];
    char command[mxn], hlp[mxn];
    int n, q = 3600 * hr + 60 * mn + sc, w;
    FILE *file, *file_2;
    giddo_existance(tmp);
    if(!strcmp(tmp, "-1")) {
        fprintf(stderr, "no repo up to root!\n");
        return 1;
    }
    strcpy(cwd, tmp);
    strcpy(giddo_path, cwd);
    strcat(giddo_path, "/.giddo");
    strcpy(commits_path, giddo_path);
    strcat(commits_path, "/commits");
    strcpy(command, giddo_path);
    strcat(command, "/.commits_id.txt");
    file = fopen(command, "r");
    if(file == NULL) {
        fprintf(stderr, "file can't be opened in log_time!\n");
        return 1;
    }
    fscanf(file, " %d", &n);
    n--;
    fclose(file);
    for(int i = n; i > -1; i--) {
        sprintf(command, "%s/%d", commits_path, i);
        sprintf(lin_time_path, "%s/lin_time.txt", command);
        file = fopen(lin_time_path, "r");
        if(file == NULL) {
            fprintf(stderr, "file can't be opened in log_time!\n");
            return 1;
        }
        fscanf(file, " %d", &w);
        fclose(file);
        if(w < q && tp == 0) continue;
        if(w > q && tp == 1) continue;
        printf("Commit ID : %d\n", i);
        //
        sprintf(hlp, "%s/time.txt", command);
        file = fopen(hlp, "r");
        if(file == NULL) {
            fprintf(stderr, "file can't be opened in log_time!\n");
            return 1;
        }
        fgets(hlp, sizeof(hlp), file);
        printf("%s", hlp);
        fclose(file);
        //
        sprintf(hlp, "%s/message.txt", command);
        file = fopen(hlp, "r");
        if(file == NULL) {
            fprintf(stderr, "file can't be opened in log_time!\n");
            return 1;
        }
        fgets(hlp, sizeof(hlp), file);
        printf("message: %s\n", hlp);
        fclose(file);
        //
        sprintf(hlp, "%s/author_name_email.txt", command);
        file = fopen(hlp, "r");
        if(file == NULL) {
            fprintf(stderr, "file can't be opened in log_time!\n");
            return 1;
        }
        fgets(hlp, sizeof(hlp), file);
        printf("%s", hlp);
        fclose(file);
        //
        sprintf(hlp, "%s/branch_name.txt", command);
        file = fopen(hlp, "r");
        if(file == NULL) {
            fprintf(stderr, "file can't be opened in log_time!\n");
            return 1;
        }
        fscanf(file, " %s", hlp);
        printf("branch name : %s\n", hlp);
        fclose(file);
        //
        sprintf(hlp, "%s/num_files_commited.txt", command);
        file = fopen(hlp, "r");
        if(file == NULL) {
            fprintf(stderr, "file can't be opened in log_time!\n");
            return 1;
        }
        int bruh;
        fscanf(file, " %d", &bruh);
        printf("number of commited files : %d\n", bruh);
        fclose(file);
    } return 0;

}
int log_search(char *word) {
    char cwd[mxn], tmp[mxn], giddo_path[mxn], commits_path[mxn], message_path[mxn];
    char command[mxn], hlp[mxn];
    int n, q;
    FILE *file, *file_2;
    giddo_existance(tmp);
    if(!strcmp(tmp, "-1")) {
        fprintf(stderr, "no repo up to root!\n");
        return 1;
    }
    strcpy(cwd, tmp);
    strcpy(giddo_path, cwd);
    strcat(giddo_path, "/.giddo");
    strcpy(commits_path, giddo_path);
    strcat(commits_path, "/commits");
    strcpy(command, giddo_path);
    strcat(command, "/.commits_id.txt");
    file = fopen(command, "r");
    if(file == NULL) {
        fprintf(stderr, "file can't be opened in log_search!\n");
        return 1;
    }
    fscanf(file, " %d", &n);
    n--;
    fclose(file);
    for(int i = n; i > -1; i--) {
        sprintf(command, "%s/%d", commits_path, i);
        sprintf(message_path, "%s/message.txt", command);
        file = fopen(message_path, "r");
        if(file == NULL) {
            fprintf(stderr, "file can't be opened in log_search!\n");
            return 1;
        }
        q = 0;
        while(fscanf(file, " %s", hlp) != EOF) {
            if(!strcmp(hlp, word)) {
                q = 1;
            }
        }
        fclose(file);
        if(!q) continue;
        printf("Commit ID : %d\n", i);
        //
        sprintf(hlp, "%s/time.txt", command);
        file = fopen(hlp, "r");
        if(file == NULL) {
            fprintf(stderr, "file can't be opened in log_search!\n");
            return 1;
        }
        fgets(hlp, sizeof(hlp), file);
        printf("%s", hlp);
        fclose(file);
        //
        sprintf(hlp, "%s/message.txt", command);
        file = fopen(hlp, "r");
        if(file == NULL) {
            fprintf(stderr, "file can't be opened in log_search!\n");
            return 1;
        }
        fgets(hlp, sizeof(hlp), file);
        printf("message: %s\n", hlp);
        fclose(file);
        //
        sprintf(hlp, "%s/author_name_email.txt", command);
        file = fopen(hlp, "r");
        if(file == NULL) {
            fprintf(stderr, "file can't be opened in log_search!\n");
            return 1;
        }
        fgets(hlp, sizeof(hlp), file);
        printf("%s", hlp);
        fclose(file);
        //
        sprintf(hlp, "%s/branch_name.txt", command);
        file = fopen(hlp, "r");
        if(file == NULL) {
            fprintf(stderr, "file can't be opened in log_search!\n");
            return 1;
        }
        fscanf(file, " %s", hlp);
        printf("branch name : %s\n", hlp);
        fclose(file);
        //
        sprintf(hlp, "%s/num_files_commited.txt", command);
        file = fopen(hlp, "r");
        if(file == NULL) {
            fprintf(stderr, "file can't be opened in log_search!\n");
            return 1;
        }
        fscanf(file, " %d", &q);
        printf("number of commited files : %d\n", q);
        fclose(file);
    } return 0;

}