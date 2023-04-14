#include "util.h"

int pre_processing(char* buf, char* dst){
    int len = 0;
    int cnt = 0;
    char* ptr = NULL;

    ptr = strtok(buf, " \n");

    while(ptr != NULL){
        strcat(dst, ptr);
        ptr = strtok(NULL, " \n");
    }

    len = strlen(dst);

    return (int)((len - cnt) / 4);
}

int to_bin4(int** binary, char* inst, int len){
    for(int i = 0; i < len; i++){
        (*binary)[i] = ((int)(inst[i * 4] - 0x30) << 3) | ((int)(inst[(i * 4 + 1)] - 0x30) << 2) | ((int)(inst[(i * 4) + 2] - 0x30) << 1) | ((int)(inst[(i * 4) + 3] - 0x30));
    }
    return 0;
}

void itobin(int value, char* res){
    char tmp;
    for(int i = 3; i >= 0; i--){
        res[i] = (char)((value & 0x1) + 0x30);
        value >>= 1;
    }
}

int is_num(char* data){
    if(*data == '0' || *data == '1'){
        return 1;
    }else{
        return 0;
    }
}

int str_strip(char* buf, char del){
    int len = strlen(buf);

    if(buf[len - 1] == del){
        buf[len - 1] = '\0';
    }


    return strlen(buf);
}