#ifndef __MODULE2__
#define __MODULE2__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mem.h"

#define HL_WRITE "WRITE"
#define HL_STORE "STORE"
#define HL_PRINT "PRINT"
#define HL_ADD   "ADD"
#define HL_SUB   "SUB"

void hl_write(char* data, char* res, char* filename, int line);
void hl_store(char* data, char* res, char* filename, int line);
void hl_print(char* data, char* res, char* filename, int line);
void hl_add(char* data, char* res, char* filename, int line);
void hl_sub(char* data, char* res, char* filename, int line);

void compile(char* buf, char* res, char* filename, int line);
void inst_load_num(char* value, char* res);
void inst_load_addr(char* var, char* res);
void inst_store(char* var, char* res);
void inst_push_n(char* value, char* res);
void inst_push(char* res);
void inst_pop(char* res);
void inst_add(char* res);
void inst_sub(char* res);
void inst_write(char* addr, char* res);
void inst_print(char* var, char* res);

#define INIT(addr,line) \
    for(int i = 0; i < (line); i++){ \
        (addr)[i] = malloc((4)); \
    }

#define VAR_MEM_CMP(var, mem) \
    if((var) == ('A')) strcpy((mem), ("0111")); \
    else if((var) == ('B')) strcpy((mem), ("0100")); \
    else if((var) == ('C')) strcpy((mem), ("0001"));

#define LOAD_DATA(param, res) \
    if(is_num(param)) inst_load_num((param), (res)); \
    else{CMem* mem = NULL; mem = search(param); inst_load_addr((mem->addr), (res));}

struct Argument_3{
    char var[5];
    char mem_addr[5];
    char value[5];
};

struct Argument_2{
    char var1[5];
    char var2[5];
};

struct Argument_1{
    char var1[5];
};

#endif