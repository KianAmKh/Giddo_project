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

void copy_file(FILE *p1, FILE *p2) {
    char ch;
    while(fscanf(p2, "%c", &ch) != EOF) {
        fprintf(p1, "%c", ch);
    } return;
}