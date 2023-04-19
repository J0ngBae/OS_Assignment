#ifndef __MEM__
#define __MEM__

#ifndef __linux__
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_MAX 100
#define MEM_SIZE 0x10

int stack_memory[STACK_MAX];
int stack_pointer;
int mem[MEM_SIZE];
int data_register;

void stack_init();
void stack_push(int data);
int stack_pop();


typedef struct Compile_Mem{
    char var[5];
    char addr[5];
    char value[5];
    struct Compile_Mem* mem;
}CMem;


CMem* search(char* var);
void search_all();
void insert(char* var, char* addr, char* value);
int size();
void delete();
void clear_list();

#endif