#ifndef __MODULE1__
#define __MODULE1__

#include <stdio.h>
#include "util.h"

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

int load_num(int num);
int load_addr_value(int addr);
void store(int addr);
void push_num(int num);
void push();
int pop();
void add();
void sub();
void write(int addr);
void print(int addr);
void stack_add(int value);
void stack_sub(int value);
void check();
void instruction_exec(char* buf);

#endif