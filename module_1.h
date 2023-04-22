#ifndef __MODULE1__
#define __MODULE1__

#include "util.h"
#include "mem.h"

#define LOAD_N 0x0
#define LOAD_A 0x1
#define STORE  0x2
#define PUSH_N 0x3
#define PUSH   0x4
#define POP    0x5
#define ADD    0x6
#define SUB    0x7

#define WRITE  0x8
#define PRINT  0x9

void load_num(int num);
void load_addr_value(int addr);
void store(int addr);
void push_num(int num);
void push();
void pop();
void add();
void sub();
void write(int addr);
void print(int addr);
void check();
void instruction_exec(char* buf);

#endif