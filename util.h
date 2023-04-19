#ifndef __UTIL__
#define __UTIL__

#define MAX_ARRAY 1024
#define MAX_STRING 1024
#define MAX_INST 12

int pre_processing(char* buf, char* dst);
int bintoi(int** binary, char* inst, int len);
void itobin(int value, char* res);
int is_num(char* data);

int str_strip(char* buf, char del);

#endif