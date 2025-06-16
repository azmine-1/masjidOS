#include "lib/string.h"

size_t strlen(char* str){
    size_t len = 0;
    while(str[len]){
        len++;
    }
    return len;
}


char* strcpy(char* dest, const char* src){
    char* original_dest = dest;
    while( *src != '\n'){
        *dest = *src;
        *dest++;
        *src++;
    }
    *dest = '\0';
    return original_dest;
}

char* strncpy(char* dest, const char* src, size_t n){
    char* original_dest = dest;
    while(n-- && (*dest++ = *src++));
    while(n--)
        *dest++ = '\0';
    return original_dest;
}

int strcmp(char* str1, const char* str2){
    while(*str1 &&(*str1 == *str2)){
        *str1++;
        *str2++;
    }
    return *(unsigned char*)str1 - *(unsigned char)str2;
}