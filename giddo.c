//Be Name Khoda
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<dirent.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include"init.h"
#include"global_config.h"
#include"reg_config.h"
#include"add.h"
#include"commits.h"
#include"shortcut.h"
#include"replace_shortcut.h"
#include"get_name_shortcut.h"
#include"remove_shortcut.h"
#include"log.h"
#include"reset.h"
#include"branch.h"
#include"checkout.h"
#include"tag.h"
#include"hook.h"
#include"grep.h"
#include"revert.h"
#include"check_if_global_config_exists.h"
#include"check_if_init_directories_exists.h"
#define mxn 1024

int valid_global_user_name_config(int argc, char *argv[]) {
    if(argc != 5) return 0;
    if(strcmp(argv[2], "--global")) return 0;
    if(strcmp(argv[3], "user.name")) return 0;
    return 1;
}
int valid_global_email_config(int argc, char *argv[]) {
    if(argc != 5) return 0;
    if(strcmp(argv[2], "--global")) return 0;
    if(strcmp(argv[3], "user.email")) return 0;
    return 1;
}
int valid_user_name_config(int argc, char *argv[]) {
    if(argc != 4) return 0;
    if(strcmp(argv[2], "user.name")) return 0;
    return 1;
}
int valid_email_config(int argc, char *argv[]) {
    if(argc != 4) return 0;
    if(strcmp(argv[2], "user.email")) return 0;
    return 1;
}

int main(int argc, char *argv[]) {
    if(argc < 2 || strcmp(argv[0], "./giddo")) {
        printf("invalid command!\n");
        return 1;
    }
    if(check_if_global_config_exists() == 1) {
        return 1;
    }
    if(check_if_global_config_exists() == 1) {
        return 1;
    }
    if(!strcmp(argv[1], "init")) {
        return init();
    }
    if(!strcmp(argv[1], "config")) {
        if(valid_global_user_name_config(argc, argv)) {
            return global_config(1, argv[4]);
        }
        if(valid_global_email_config(argc, argv)) {
            return global_config(2, argv[4]);
        }
        if(valid_user_name_config(argc, argv)) {
            return reg_config(1, argv[3]);
        }
        if(valid_email_config(argc, argv)) {
            return reg_config(2, argv[3]);
        }
    }
    if(!strcmp(argv[1], "add")) {
        if(argc < 3 || (!strcmp(argv[2], "-f") && argc < 4)) {
            printf("invalid command!\n");
            return 0;
        }
        else {
            if(!strcmp(argv[2], "-n")) {
                int q = 0;
                for(int i = 0; i < strlen(argv[3]); i++) {
                    q *= 10;
                    q += (*(argv[3] + i) - '0');
                }
                return add_n(q);
            }
            if(strcmp(argv[2], "-f")) {
                int q = 0;
                char cwd[mxn];
                getcwd(cwd, mxn);
                for(int i = 2; i < argc; i++) {
                    char *id_fucking_know = malloc(mxn * sizeof(char));
                    strcpy(id_fucking_know, argv[i]);
                    q = add(id_fucking_know);
                    if(chdir(cwd) != 0) {
                        fprintf(stderr, "couldn't change the directory to cwd in main!\n");
                        return 1;
                    }
                    if(q == 1) {
                        return 1;
                    }
                }
                return 0;
            }
            int q = 0;
            char cwd[mxn];
            getcwd(cwd, mxn);
            for(int i = 3; i < argc; i++) {
                char *id_fucking_know = malloc(mxn * sizeof(char));
                strcpy(id_fucking_know, argv[i]);
                q = add(id_fucking_know);
                if(chdir(cwd) != 0) {
                    fprintf(stderr, "couldn't change the directory to cwd in main!\n");
                    return 1;
                }
                if(q == 1) {
                    return 1;
                }
            }
            return 0;
        }
    }
    if(!strcmp(argv[1], "commit")) {
        if(argc != 4) {
            printf("invalid command!\n");
            return 0;
        }
        if(!strcmp(argv[2], "-m")) {
            if(strlen(argv[3]) > 72) {
                printf("long message!\n");
                return 0;
            }
            char *id_fucking_know = malloc(mxn * sizeof(char));
            strcpy(id_fucking_know, argv[3]);
            if(commits(id_fucking_know)) {
                fprintf(stderr, "unseccussful!\n");
                return 1;
            }
            return 0;
        } 
        if(!strcmp(argv[2], "-s")) {
            char *id_fucking_know = malloc(mxn * sizeof(char));
            strcpy(id_fucking_know, argv[3]);
            if(get_name_shortcut(id_fucking_know)) {
                fprintf(stderr, "Not such a name exist!\n");
                return 0;
            }
            if(commits(id_fucking_know)) {
                fprintf(stderr, "unseccussful!\n");
                return 1;
            }
            return 0;
        }
        printf("invalid command!\n");
        return 0;
    }
    if(!strcmp(argv[1], "set")) {
        if(argc != 6) {
            printf("invalid command!\n");
            return 0;
        }
        if(strcmp(argv[2], "-m")) {
            printf("invalid command!\n");
            return 0;
        }
        if(strcmp(argv[4], "-s")) {
            printf("invalid command!\n");
            return 0;
        }
        char *a, *b;
        a = calloc(mxn, sizeof(char)), b = calloc(mxn, sizeof(char));
        strcpy(a, argv[3]), strcpy(b, argv[5]);
        shortcut(a, b);
        return 0;
    }
    if(!strcmp(argv[1], "replace")) {
        if(argc != 6) {
            printf("invalid command!\n");
            return 0;
        }
        if(strcmp(argv[2], "-m")) {
            printf("invalid command!\n");
            return 0;
        }
        if(strcmp(argv[4], "-s")) {
            printf("invalid command!\n");
            return 0;
        }
        char *a, *b;
        a = calloc(mxn, sizeof(char)), b = calloc(mxn, sizeof(char));
        strcpy(a, argv[3]), strcpy(b, argv[5]);
        replace_shortcut(a, b);
        return 0;
    }
    if(!strcmp(argv[1], "remove")) {
        if(argc != 4) {
            printf("invalid command!\n");
            return 0;
        }
        if(strcmp(argv[2], "-s")) {
            printf("invalid command!\n");
            return 0;
        }
        char *id_fucking_know = malloc(mxn * sizeof(char));
        strcpy(id_fucking_know, argv[3]);
        return remove_shortcut(id_fucking_know);
    }
    if(!strcmp(argv[1], "log")) {
        if(argc == 2) {
            return log_n(mxn);
        }
        if(argc != 4) {
            printf("invalid command!\n");
            return 0;
        }
        int h = 0, m = 0, s = 0; // 12:45:78
        h = (*(argv[3]) - '0') * 10 + (*(argv[3] + 1) - '0');
        m = (*(argv[3] + 3) - '0') * 10 + (*(argv[3] + 4) - '0');
        s = (*(argv[3] + 6) - '0') * 10 + (*(argv[3] + 7) - '0');
        if(!strcmp(argv[2], "-since")) { // bayad format time, hour minute second , bashe
            return log_time(h, m, s, 0);
        }
        if(!strcmp(argv[2], "-before")) { // bayad format time, hour minute second , bashe
            return log_time(h, m, s, 1);
        }
        if(!strcmp(argv[2], "-n")) {
            int q = 0;
            for(int i = 0; i < strlen(argv[3]); i++) {
                q *= 10;
                q += (*(argv[3] + i) - '0');
            }
            return log_n(q);
        }
        if(!strcmp(argv[2], "-branch")) {
            char *a = malloc(mxn * sizeof(char));
            strcpy(a, argv[3]);
            return log_branch(a);
        }
        if(!strcmp(argv[2], "-author")) {
            char *a = malloc(mxn * sizeof(char));
            strcpy(a, argv[3]);
            return log_author(a);
        }
        if(!strcmp(argv[2], "-search")) {
            char *a = malloc(mxn * sizeof(char));
            strcpy(a, argv[3]);
            return log_search(a);
        }
    }
    if(!strcmp(argv[1], "reset")) {
        if(argc == 2) {
            printf("invalid command!\n");
            return 0;
        }
        if(!strcmp(argv[2], "-undo") && argc != 3) {
            printf("invalid command!\n");
            return 0;
        }
        if(!strcmp(argv[2], "-undo")) {
            return reset_undo();
        }
        if(!strcmp(argv[2], "-f")) {
            int idkkkkkk = 0;
            for(int i = 3; i < argc; i++) {
                char *a = malloc(mxn * sizeof(char));
                strcpy(a, argv[i]);
                idkkkkkk += reset(a);
            }
            if(idkkkkkk) return 1;
            return 0;
        }
        int idkkk = 0;
        for(int i = 2; i < argc; i++) {
            char *a = malloc(mxn * sizeof(char));
            strcpy(a, argv[i]);
            idkkk += reset(a);
        }
        if(idkkk) return 1;
        return 0;
    }
    if(!strcmp(argv[1], "branch")) {
        if(argc == 2) {
            return print_branches();
        }
        if(argc != 3) {
            printf("invalid command!\n");
            return 0;
        }
        char *a = malloc(mxn * sizeof(char));
        strcpy(a, argv[2]);
        return add_branch(a);
    }
    if(!strcmp(argv[1], "checkout")) {
        if(argc != 3) {
            printf("invalid command!\n");
            return 0;
        }
        char *a = malloc(mxn * sizeof(char));
        strcpy(a, argv[2]);
        if('0' <= *a && *a <= '9') {
            int q = 0;
            for(int i = 0; i < strlen(a); i++) {
                q *= 10;
                q += (*(a + i) - '0');
            }
            return submit_checkout(q);
        }
        if(!strcmp(argv[2], "HEAD")) {
            return checkout_head();
        }
        return checkout_branch(a);
    }
    if(argc > 3 && !strcmp(argv[1], "tag") && !strcmp(argv[2], "-a")) {
        char *a = malloc(mxn * sizeof(char));
        char *b = malloc(mxn * sizeof(char));
        char *c = malloc(mxn * sizeof(char));
        int q = 0;
        strcpy(a, argv[3]);
        if(argc == 4) {
            return add_tag(a, " ", -1, 0);
        }
        if(argc == 5) {
            return add_tag(a, " ", -1, 1);
        }
        if(argc == 6) {
            if(!strcmp(argv[4], "-m")) {
                strcpy(b, argv[5]);
                return add_tag(a, b, -1, 0);
            }
            if(!strcmp(argv[4], "-c")) {
                strcpy(b, argv[5]);
                for(int i = 0; i < strlen(b); i++) {
                    q *= 10;
                    q += (*(b + i) - '0');
                }
                return add_tag(a, " ", q, 0);
            }
            printf("invalid command!\n");
            return 0;
        }
        if(argc == 7) {
            if(!strcmp(argv[4], "-m")) {
                strcpy(b, argv[5]);
                return add_tag(a, b, -1, 1);
            }
            if(!strcmp(argv[4], "-c")) {
                strcpy(b, argv[5]);
                for(int i = 0; i < strlen(b); i++) {
                    q *= 10;
                    q += (*(b + i) - '0');
                }
                return add_tag(a, " ", q, 1);
            }
            printf("invalid command!\n");
            return 0;
        }
        if(argc == 8) {
            if(!strcmp(argv[4], "-m")) {
                strcpy(b, argv[5]);
                strcpy(c, argv[7]);
                for(int i = 0; i < strlen(c); i++) {
                    q *= 10;
                    q += (*(c + i) - '0');
                } 
                return add_tag(a, b, q, 0);
            }
            else {
                strcpy(b, argv[7]);
                strcpy(c, argv[5]);
                for(int i = 0; i < strlen(c); i++) {
                    q *= 10;
                    q += (*(c + i) - '0');
                } 
                return add_tag(a, b, q, 0);
            }
        }
        if(argc == 9) {
            if(!strcmp(argv[4], "-m")) {
                strcpy(b, argv[5]);
                strcpy(c, argv[7]);
                for(int i = 0; i < strlen(c); i++) {
                    q *= 10;
                    q += (*(c + i) - '0');
                } 
                return add_tag(a, b, q, 1);
            }
            else {
                strcpy(b, argv[7]);
                strcpy(c, argv[5]);
                for(int i = 0; i < strlen(c); i++) {
                    q *= 10;
                    q += (*(c + i) - '0');
                } 
                return add_tag(a, b, q, 1);
            }
        }
        printf("invalid command!\n");
        return 0;
    }
    if(argc == 2 && !strcmp(argv[1], "tag")) {
        return show_all();
    }
    if(argc == 4 && !strcmp(argv[1], "tag") && !strcmp(argv[2], "show")) {
        char *a = malloc(mxn * sizeof(char));
        strcpy(a, argv[3]);
        return tag_show(a);
    }
    if(!strcmp(argv[1], "pre-commit")) {
        char *a = malloc(mxn * sizeof(char));
        if(argc == 4) {
            if(!strcmp(argv[2], "hooks") && !strcmp(argv[3], "list")) {
                return show_hooks_list();
            }
            if(!strcmp(argv[2], "applied") && !strcmp(argv[3], "hooks")) {
                return show_applied_hooks();
            }
            printf("invalid command!\n");
            return 0;
        }
        if(argc == 5) {
            if(!strcmp(argv[2], "add") && !strcmp(argv[3], "hook")) {
                strcpy(a, argv[4]);
                return add_hook(a);
            }
            if(!strcmp(argv[2], "remove") && !strcmp(argv[3], "hook")) {
                strcpy(a, argv[4]);
                return remove_hook(a);
            }
            printf("invalid command!\n");
            return 0;
        }
    }
    if(!strcmp(argv[1], "grep")) {
        if(argc != 6 && argc != 7) {
            printf("invalid command!\n");
            return 0;
        }
        char *a = malloc(mxn * sizeof(char)), *b = malloc(mxn * sizeof(char));
        strcpy(a, argv[3]), strcpy(b, argv[5]);
        return grep(a, b, argc - 6);
    }
    if(!strcmp(argv[1], "revert")) {
        char *a = malloc(mxn * sizeof(char));
        if(argc == 3) {
            strcpy(a, argv[2]);
            int q = 0;
            for(int i = 0; i < strlen(a); i++) {
                q *= 10;
                q += (*(a + i) - '0');
            }
            return revert(q, "lalayi");
        }
        if(argc == 5 && !strcmp(argv[2], "-e")) {
            char *b = malloc(mxn * sizeof(char));
            strcpy(b, argv[3]);
            strcpy(a, argv[4]);
            int q = 0;
            for(int i = 0; i < strlen(a); i++) {
                q *= 10;
                q += (*(a + i) - '0');
            }
            return revert(q, b);
        } 
        printf("invalid command!\n");
    }
    printf("invalid command!\n");
    return 0;

}