#include "mem.h"


#define IS_MEM_EMPTY() ((head) == (NULL)) ? (0) : (1)

CMem* head = NULL;

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

/*** Stack Memory Util End ***/

/*** Memory Linked List Util Start ***/

/**
 * @brief Memory에서 "var"에 해당하는 변수가 있는 구조체 반환
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
 * @brief 모든 Memory Linked List 출력
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
 * @brief 현재 Memory Linked List의 개수 반환
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
    strncpy(new_node->var, var, 5);
    strncpy(new_node->addr, addr, 5);
    strncpy(new_node->value, value, 5);

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