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

int init() {

    char cwd[mxn], tmp[mxn], user_name[mxn], email[mxn];
    if(getcwd(cwd, sizeof(cwd)) == NULL) {
        fprintf(stderr, "didn't get the working directory's path!\n");
        return 1;
    }
    bool flag = 0;
    struct dirent *entry;
    do {
        DIR *dir = opendir(".");
        if(dir == NULL) {
            fprintf(stderr, "directory did not open!\n");
            return 1;
        }
        while((entry = readdir(dir)) != NULL) {
            if(entry->d_type == DT_DIR && !strcmp(entry->d_name, ".giddo")) {
                flag = 1;
                break;
            }
        } 
        closedir(dir);
        if(flag) break;
        if(getcwd(tmp, sizeof(tmp)) == NULL) {
            fprintf(stderr, "didn't get the working directory's path!\n");
            return 1;
        }
        if(strcmp(tmp, "/Users/kianwm")) {
            if(chdir("..") != 0) {
                fprintf(stderr, "can't go to parent!\n");
                return 1;
            }
        }
    } while(strcmp(tmp, "/Users/kianwm"));
    if(flag) {
        fprintf(stderr, "giddo already exists");
        return 1;
    }
    if(chdir(cwd) != 0) {
        fprintf(stderr, "can't get back to cwd!\n");
        return 1;
    }
    if(mkdir(".giddo", 0777) != 0) {
        fprintf(stderr, "can't make .giddo directory!\n");
        return 1;
    }
    if(chdir(".giddo") != 0) {
        fprintf(stderr, "can't go to .giddo!\n");
        return 1;
    }
    //creating files in .giddo
    //-------------------------
    //copy
    if(mkdir("copy", 0777) != 0) {
        fprintf(stderr, "can't make copy directory!\n");
        return 1;
    }
    //staging_area
    if(mkdir("staging_area", 0777) != 0) {
        fprintf(stderr, "can't make staging_area directory!\n");
        return 1;
    }
    //commits
    if(mkdir("commits", 0777) != 0) {
        fprintf(stderr, "can't make commits directory!\n");
        return 1;
    }
    FILE *file, *file_2;
    //commits_id.txt
    file = fopen(".commits_id.txt", "w");
    if(file == NULL) {
        fprintf(stderr, "can't make .commits_id.txt file!\n");
    }
    fprintf(file, "%d", 0);
    fclose(file);
    //////
    if(chdir("commits") != 0) {
        fprintf(stderr, "can't go to commits!\n");
        return 1;
    }
    /*file = fopen("commit_hash.txt", "w");
    if(file == NULL) {
        fprintf(stderr, "can't make commit_hash.txt file!\n");
        return 1;
    }
    fclose(file);
    file = fopen("time.txt", "w");
    if(file == NULL) {
        fprintf(stderr, "can't make time.txt file!\n");
        return 1;
    }
    fclose(file);
    file = fopen("lin_time.txt", "w");
    if(file == NULL) {
        fprintf(stderr, "can't make lin_time.txt file!\n");
        return 1;
    }
    fclose(file);
    file = fopen("message.txt", "w");
    if(file == NULL) {
        fprintf(stderr, "can't make message.txt file!\n");
        return 1;
    }
    fclose(file);
    file = fopen("autor_name_email.txt", "w");
    if(file == NULL) {
        fprintf(stderr, "can't make autor_name_email.txt file!\n");
        return 1;
    }
    fclose(file);
    file = fopen("num_files_commited.txt", "w");
    if(file == NULL) {
        fprintf(stderr, "can't make autor_name_email.txt file!\n");
        return 1;
    }*/
    if(chdir("..") != 0) {
        fprintf(stderr, "can't go back to .giddo!\n");
        return 1;
    }
    //.config.txt
    file = fopen(".config.txt", "w"), file_2 = fopen("/Users/kianwm/global_data/config.txt", "r");
    if(file == NULL || file_2 == NULL) {
        fprintf(stderr, "file couldn't be opened!\n");
        return 1;
    }
    fscanf(file_2, "username: %s\n email: %s", user_name, email);
    fprintf(file, "username: %s\nemail: %s\n", user_name, email);
    fclose(file), fclose(file_2);
    //.tracking_files.txt
    file = fopen(".tracking_files.txt", "w");
    if(file == NULL) {
        fprintf(stderr, "file couldn't be made!\n");
        return 1;
    }
    fclose(file);
    //.shortcut_name.txt
    file = fopen(".shortcut_name.txt", "w");
    if(file == NULL) {
        fprintf(stderr, "file couldn't be made!\n");
        return 1;
    }
    fclose(file);
    //.shortcut_message.txt
    file = fopen(".shortcut_message.txt", "w");
    if(file == NULL) {
        fprintf(stderr, "file couldn't be made!\n");
        return 1;
    }
    fclose(file);
    //.num_add.txt
    file = fopen(".num_add.txt", "w");
    if(file == NULL) {
        fprintf(stderr, "file couldn't be made!\n");
        return 1;
    }
    fprintf(file, "%d", 0);
    fclose(file);
    //.staging_area.txt
    file = fopen(".staging_area.txt", "w");
    if(file == NULL) {
        fprintf(stderr, "file couldn't be made!\n");
        return 1;
    }
    fclose(file);
    //.staging_area_2.txt
    file = fopen(".staging_area_2.txt", "w");
    if(file == NULL) {
        fprintf(stderr, "file couldn't be made!\n");
        return 1;
    }
    fclose(file);
    //.ccp.txt
    file = fopen(".ccp.txt", "w");
    if(file == NULL) {
        fprintf(stderr, "file couldn't be made!\n");
        return 1;
    }
    fprintf(file, "%d", -1);
    fclose(file);
    //.branch_names.txt
    file = fopen(".branch_names.txt", "w");
    if(file == NULL) {
        fprintf(stderr, "file couldn't be made!\n");
        return 1;
    }
    fprintf(file, "Master\n");
    fclose(file);
    //.special.txt
    file = fopen(".special.txt", "w");
    if(file == NULL) {
        fprintf(stderr, "file couldn't be made!\n");
        return 1;
    }
    fclose(file);
    //.tag_names.txt
    file = fopen(".tag_names.txt", "w");
    if(file == NULL) {
        fprintf(stderr, "file couldn't be made!\n");
        return 1;
    }
    fclose(file);
    //.hook_list.txt
    file = fopen(".hook_list.txt", "w");
    if(file == NULL) {
        fprintf(stderr, "file couldn't be made!\n");
        return 1;
    }
    fprintf(file, "todo-check\neof-blank-space\n");
    fclose(file);
    //.applied_hooks.txt
    file = fopen(".applied_hooks.txt", "w");
    if(file == NULL) {
        fprintf(stderr, "file couldn't be made!\n");
        return 1;
    }
    fclose(file);
    //-------------------------
    //adding the working directory to init_directories
    file = fopen("/Users/kianwm/global_data/init_directories.txt", "a");
    if(file == NULL) {
        fprintf(stderr, "file couldn't be opened!\n");
        return 1;
    }
    fprintf(file, "%s\n", cwd);
    fclose(file);
    
    //FILE *f1, *f2, *f3;
    //tracking files o log o inaro ezafe va write mikonam inja
    return 0;
}