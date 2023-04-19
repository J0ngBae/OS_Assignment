#ifndef __UTIL__
#define __UTIL__

#ifndef __linux__
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

#define MAX_ARRAY 1024
#define MAX_STRING 1024
#define MAX_INST 12

int pre_processing(char* buf, char* dst);
int to_bin4(int** binary, char* inst, int len);
void itobin(int value, char* res);
int is_num(char* data);

int str_strip(char* buf, char del);

#endif