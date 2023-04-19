#include "module_2.h"
#include "mem.h"
#include "util.h"

void validation_compile(char* data, char* del, int param_num, char* filename, int line, char* inst){
    int cnt = 0;
    int len = strlen(data);
    char* ptr = (char*)calloc(len, sizeof(char));

    if (ptr == NULL) {
        printf("Memory Allocation Error...\n");
        exit(0);
    }
    strncpy(ptr, data, len);
    //ptr[len - 1] = '\0';// ¹Ù²ïºÎºÐ

    ptr = strtok(ptr, del);
    while(ptr != NULL){
        ptr = strtok(NULL, del);
        cnt++;
    }
    
    if(cnt < param_num){
        printf("[!] %s:%d:error: too few parameters to instruction \'%s\'\n", filename, line, inst);
        exit(0);
    }
    else if(cnt > param_num){
        printf("[!] %s:%d:error: too many parameters to instruction \'%s\'\n", filename, line, inst);
        exit(0);
    }

    free(ptr);
}

void hl_write(char* data, char* res, char* filename, int line){
    char* ptr;
    struct Argument_3 write_struct = {"\0", "\0", "\0"};

    str_strip(data, '\n');
    validation_compile(data, ", ", 3, filename, line, HL_WRITE);

    ptr = strtok(data, ", ");
    strcpy(write_struct.var, ptr);

    ptr = strtok(NULL, ", ");
    strncpy(write_struct.mem_addr, ptr, 5);

    ptr = strtok(NULL, ", ");
    strncpy(write_struct.value, ptr, 5);

    insert(write_struct.var, write_struct.mem_addr, write_struct.value);

    inst_push_n(write_struct.value, res);
    inst_write(write_struct.mem_addr, res);
    inst_pop(res);

}

void hl_store(char* data, char* res, char* filename, int line){
    char* ptr = NULL;
    int len = 0;
    struct Argument_1 store_struct = { "\0" };

    str_strip(data, '\n');
    validation_compile(data, ", ", 1, filename, line, HL_STORE);

    len = str_strip(data, '\n');
    strncpy(store_struct.var1, data, len);
    
    inst_store(store_struct.var1, res);
}

void hl_print(char* data, char* res, char* filename, int line){
    char* ptr = NULL;
    struct Argument_1 print_struct = { "\0" };

    str_strip(data, '\n');
    validation_compile(data, ", ", 1, filename, line, HL_PRINT);

    strcpy(print_struct.var1, data);
    inst_print(print_struct.var1, res);
}

void hl_add(char* data, char* res, char* filename, int line){
    char* ptr = NULL;
    struct Argument_2 add_struct = { "\0", "\0" };
    int len = 0;

    str_strip(data, '\n');
    validation_compile(data, ", ", 2, filename, line, HL_ADD);

    ptr = strtok(data, ", ");
    len = str_strip(ptr, '\n');
    strncpy(add_struct.var1, ptr, len);

    LOAD_DATA(add_struct.var1, res);
    inst_push(res);

    ptr = strtok(NULL, ", ");
    len = str_strip(ptr, '\n');
    strncpy(add_struct.var2, ptr, len);

    LOAD_DATA(add_struct.var2, res);

    inst_add(res);
    inst_pop(res);
}

void hl_sub(char* data, char* res, char* filename, int line){
    char* ptr = NULL;
    int len = 0;
    struct Argument_2 sub_struct = { "\0", "\0" };

    str_strip(data, '\n');
    validation_compile(data, ", ", 2, filename, line, HL_SUB);

    ptr = strtok(data, ", ");
    len = str_strip(ptr, '\n');
    strncpy(sub_struct.var1, ptr, len);

    LOAD_DATA(sub_struct.var1, res);
    inst_push(res);

    ptr = strtok(NULL, ", ");
    len = str_strip(ptr, '\n');
    strncpy(sub_struct.var2, ptr, len);

    LOAD_DATA(sub_struct.var2, res);

    inst_sub(res);
    inst_pop(res);
}

/***********/

/**
 * @brief Convert Load [N] instruction
 * Instruction Number : 0 (0000)
 * 
 * @param value 
 * @param res 
 */
void inst_load_num(char* value, char* res){
    strcat(res, "0000 ");
    strcat(res, value);
    strcat(res, "\n");
}

/**
 * @brief Convert Load [Address] instruction
 * Instruction Number : 1 (0001)
 * 
 * @param var 
 * @param res 
 */
void inst_load_addr(char* var, char* res){
    strcat(res, "0001 ");
    strcat(res, var);
    strcat(res, "\n");
}

/**
 * @brief Convert Store [Address] instruction
 * Instruction Number : 2 (0010)
 * 
 * @param var 
 * @param res 
 */
void inst_store(char* var, char* res){
    CMem* memory = NULL;
    int len = strlen(var);
    memory = search(var);

    strcat(res, "0010 ");
    strcat(res, memory->addr);
    strcat(res, "\n");
}

/**
 * @brief Convert Push [N] instruction
 * Instruction Number : 3 (0011)
 * 
 * @param value 
 * @param res 
 */
void inst_push_n(char* value, char* res){
    strcat(res, "0011 ");
    strcat(res, value);
    strcat(res, "\n");
}

/**
 * @brief Convert Push instruction
 * Instruction Number : 4 (0100)
 * 
 * @param res 
 */
void inst_push(char* res){
    strcat(res, "0100 ");
    strcat(res, "\n");
}

/**
 * @brief Convert Pop instruction
 * Instruction Number : 5 (0101)
 * 
 * @param res 
 */
void inst_pop(char* res){
    strcat(res, "0101");
    strcat(res, "\n");
}

/**
 * @brief Convert "Add" instruction
 * Instruction Number : 6 (0110)
 * 
 * @param res 
 */
void inst_add(char* res){
    strcat(res, "0110");
    strcat(res, "\n");
}

/**
 * @brief Convert "Sub" instruction
 * Instruction Number : 7 (0111)
 * 
 * @param res 
 */
void inst_sub(char* res){
    strcat(res, "0111");
    strcat(res, "\n");
}

/**
 * @brief Convert "Write" instruction
 * Instruction Number : 8 (1000)
 * 
 * @param addr 
 * @param res 
 */
void inst_write(char* addr, char* res){
    strcat(res, "1000 ");
    strcat(res, addr);
    strcat(res, "\n");
}

/**
 * @brief Convert "Print" instruction
 * Instruction Number : 9 (1001)
 * 
 * @param var 
 * @param res 
 */
void inst_print(char* var, char* res){
    char mem[5] = {'\0'};
    CMem* memory = NULL;

    memory = search(var);

    strcat(res, "1001 ");
    strcat(res, memory->addr);
    strcat(res, "\n");
}

void compile(char* buf, char* res, char* filename, int line){
    char* ptr = buf;
    ptr = strtok(ptr, " ");
    if(!strcmp(HL_WRITE, ptr)){
        ptr = strtok(NULL, "\0");
        hl_write(ptr, res, filename, line);
    }
    else if(!strcmp(ptr, HL_STORE)){
        ptr = strtok(NULL, "\0");
        hl_store(ptr, res, filename, line);
    }
    else if(!strcmp(ptr, HL_PRINT)){
        ptr = strtok(NULL, "\0");
        hl_print(ptr, res, filename, line);
    }
    else if(!strcmp(ptr, HL_ADD)){
        ptr = strtok(NULL, "\0");
        hl_add(ptr, res, filename, line);
    }
    else if(!strcmp(ptr, HL_SUB)){
        ptr = strtok(NULL, "\0");
        hl_sub(ptr, res, filename, line);
    }else{
        printf("[!] %s:%d:error: \'%s\' is undefined instruction\n", filename, line, ptr);
        exit(0);
    }
}