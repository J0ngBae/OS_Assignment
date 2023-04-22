#ifndef __linux__
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mem.h"

#define IS_MEM_EMPTY() ((head) == (NULL)) ? (0) : (1)

CMem* head = NULL;
int stack_memory[STACK_MAX];
int stack_pointer;
int mem[MEM_SIZE];
int data_register;


/*** Stack Memory Util Start ***/
void stack_init(){
    stack_pointer = -1;
}

void stack_push(int data){
    if(stack_pointer >= STACK_MAX - 1){
        printf("stack overflow...");
        exit(0);
    }
    stack_memory[++stack_pointer] = data;
}

int stack_pop(){
    if(stack_pointer < 0){
        printf("stack underflow");
        exit(0);
    }
    return stack_memory[stack_pointer--];
}

void stack_add(int value){
    stack_memory[stack_pointer] += value;
}

void stack_sub(int value){
    stack_memory[stack_pointer] -= value;
}

/*** Stack Memory Util End ***/

/*** Memory Linked List Util Start ***/

/**
 * @brief Find the CMem object that corresponds to the variable
 * 
 * @param var 
 * @return CMem* 
 */
CMem* search(char* var){
    CMem* p;
    int len = strlen(var);
    for(p = head; p != NULL; p = p->mem){
        if(!strncmp(p->var, var, len)){
            return p;
        }
    }
    return NULL;
}

/**
 * @brief Find All CMem object
 * 
 */
void search_all(){
    CMem* p;
    for(p = head; p != NULL; p = p->mem){
        printf("[+] var -> %s\n", p->var);
        printf("[+] addr -> %s\n", p->addr);
        printf("[+] value -> %s\n", p->value);
    }
}

/**
 * @brief Current Linked List Size return
 * 
 * @return int 
 */
int size(){
    CMem* p;
    int count = 0;
    for(p = head; p != NULL; p = p->mem) count++;
    return count;
}

void insert_next(CMem* before, CMem* node){
    if(node != NULL){
        node->mem = before->mem;
        before->mem = node;
    }
}

void insert(char* var, char* addr, char* value){
    CMem* new_node;
    
    new_node = (CMem*)malloc(sizeof(CMem*));
    if (new_node == NULL) {
        printf("Memory Allocation Error...\n");
        free(new_node);
        exit(0);
    }
    strncpy(new_node->var, var, MACHINE_BYTE);
    strncpy(new_node->addr, addr, MACHINE_BYTE);
    strncpy(new_node->value, value, MACHINE_BYTE);

    new_node->mem = head;
    head = new_node;
}

void delete(){
    CMem *removed;

    if(IS_MEM_EMPTY()){
        removed = head;
        head = head->mem;
        free(removed);
    }
}

void clear_list(){
    while(IS_MEM_EMPTY()){
        delete();
    }
}

/*** Memory Linked List Util End ***/