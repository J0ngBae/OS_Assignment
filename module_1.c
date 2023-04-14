#include "module_1.h"
#include "mem.h"

/*
void check(){
    printf("[+] Stack: ");
    for(int i = 0; i < 10; i++){
        printf("%d,", stack_memory[i]);
    }
    printf("\n");
    printf("[+] DR : %d\n", data_register);
    printf("[+] Memory_A : %d\n", mem[0].value);
    printf("[+] Memory_B : %d\n", mem[1].value);
    printf("[+] Memory_C : %d\n", mem[2].value);
}
*/

void stack_add(int value){
    stack_memory[stack_pointer] += value;
}

void stack_sub(int value){
    stack_memory[stack_pointer] -= value;
}

int load_num(int num){
    data_register = num;
}

int load_addr_value(int addr){
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

int pop(){
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
    char result[4];
    itobin(mem[addr], result);
    printf("결과 : %d, %s\n", mem[addr], result);
}

void instruction_exec(char* buf){
    char dst[MAX_STRING] = {};
    int line, idx = 0;
    int len = pre_processing(buf, dst);
    int* binary = (int*)malloc(len * sizeof(int));

    to_bin4(&binary, dst, len);
 
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