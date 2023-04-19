#ifndef __MEM__
#define __MEM__

#define STACK_MAX 100
#define MEM_SIZE 0x10
#define MACHINE_BYTE 5

int stack_memory[STACK_MAX];
int stack_pointer;
int mem[MEM_SIZE];
int data_register;

void stack_init();
void stack_push(int data);
int stack_pop();
void stack_add(int value);
void stack_sub(int value);


/*********************************************************
 *  variable define of module2 is managed by Linked List *
 **********************************************************/
typedef struct Compile_Mem{
    char var[MACHINE_BYTE];
    char addr[MACHINE_BYTE];
    char value[MACHINE_BYTE];
    struct Compile_Mem* mem;
}CMem;


CMem* search(char* var);
void search_all();
void insert(char* var, char* addr, char* value);
int size();
void delete();
void clear_list();

#endif