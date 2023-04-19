#ifndef __linux__
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "module_1.h"
#include "module_2.h"
#include "mem.h"

void exec_module(char* filename);
void compile_module(char* filename, char* objfile);

int main(int argc, char* argv[]){
    
    if(argc != 3){
        printf("[+] Usage ./main <file.pl> <file.bi>\n");
        exit(0);
    }
    compile_module(argv[1], argv[2]);
    exec_module(argv[2]);

}

void compile_module(char* filename, char* objfile){
    FILE *fd = NULL;
    char buf[0x100] = { "\0" };
    char result[MAX_STRING] = { "\0" };
    char* ptr = NULL;
    int line = 1;
    
    fd = fopen(filename, "r");
    if(fd == NULL){
        printf("File Open Error...\n");
        exit(0);
    }

    while(fgets(buf, 0x100, fd) != NULL){
        compile(buf, result, filename, line);
        memset(buf, 0x00, 0x100);
        line++;
    }
    clear_list();

    fclose(fd);

    fd = fopen(objfile, "w");
    if(fd == NULL){
        printf("File Open Error...\n");
        exit(0);
    }

    fwrite(result, sizeof(char), MAX_STRING, fd);
    fclose(fd);

}

void exec_module(char* filename){
    /* File Read */
    FILE *fd = fopen(filename, "r");
    char buf[MAX_STRING] = "";
    
    char* ptr = NULL;

    if(fd == NULL){
        printf("File Open Error...\n");
        exit(0);
    }

    fread(buf, sizeof(char), MAX_STRING, fd);
    instruction_exec(buf);

    fclose(fd);
}