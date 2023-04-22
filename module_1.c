#include <stdio.h>
#include <stdlib.h>
#include "module_1.h"

extern int stack_memory[STACK_MAX];
extern int stack_pointer;
extern int mem[MEM_SIZE];
extern int data_register;

void load_num(int num){
    data_register = num;
}

void load_addr_value(int addr){
    data_register = mem[addr];
}

void store(int addr){
    mem[addr] = data_register;
}

void push_num(int num){
    stack_push(num);
}

void push(){
    stack_push(data_register);
}

void pop(){
    data_register = stack_pop();
}

void add(){
    stack_add(data_register);
}

void sub(){
    stack_sub(data_register);
}

void write(int addr){
    mem[addr] = stack_memory[stack_pointer];
}

void print(int addr){
    char result[MACHINE_BYTE];
    itobin(mem[addr], result);
    printf("result : %d, %s\n", mem[addr], result);
}

void instruction_exec(char* buf){
    char dst[MAX_STRING] = {'\0'};
    int line, idx = 0;
    int len = pre_processing(buf, dst);
    int* binary = (int*)malloc(len * sizeof(int));

    bintoi(&binary, dst, len);
 
    line = 0;
    stack_init();
    while(idx < len){
        switch(binary[idx]){
            case LOAD_N:
                load_num(binary[++idx]);
                break;
            case LOAD_A:
                load_addr_value(binary[++idx]);
                break;
            case STORE:
                store(binary[++idx]);
                break;
            case PUSH_N:
                push_num(binary[++idx]);
                break;
            case PUSH:
                push();
                break;
            case POP:
                pop();
                break;
            case ADD:
                add();
                break;
            case SUB:
                sub();
                break;
            case WRITE:
                write(binary[++idx]);
                break;
            case PRINT:
                print(binary[++idx]);
                break;
        }
        idx++;
    }

    free(binary);
}