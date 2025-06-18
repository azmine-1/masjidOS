#include "stdlib.h"
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
    return *(unsigned char*)str1 - *(unsigned char*)str2;
}


strncmp(char* str1, const char* str2, size_t n){
    while(n-- && *str1 && (*str1==*str2)){
        *str1++;
        *str2++;
    }
    return *(unsigned char*)str1 - *(unsigned char*)str2;
}

char* strcat(char* dest, const char* src){
    char* original_dest = dest;
    while(*dest){
        dest++;
    }
    while((*dest++ = *src++));
    return original_dest;
}

void* memset(void* ptr, int value, size_t num){
    unsigned char* p = (unsigned char*)ptr;
    while(num--){
        *p++ = (unsigned char)value;
    }
    return ptr;
}

void* memcpy(void* dest, void* src, size_t num){
    unsigned char* d = (unsigned char*)dest;
    const unsigned char* s = (unsigned char*)src;
    while(num--){
        *d++ = *s++;
    }
    return dest;
}

void* memmove(void* dest, void* src, size_t num){
    unsigned char* d = (unsigned char*)dest;
    const unsigned char* s =(unsigned char*)src;

    if(d < s){
        while(num--){
            *d++ = *s++;
        }
    } else if(d > s){
        d += num - 1;
        s += num -1; 
        while(num--){
            *d-- = *s--;
        
        }
    }
    return dest;
    
}


int memcmp(const void* ptr1, const void* ptr2, size_t num){
    const unsigned char* p1 = (const unsigned char*)ptr1;
    const unsigned char* p2 = (const unsigned char*)ptr2;

    while(num--){
        if(*p1 != *p2){
            return *p1 - *p2;
        }
        p1++;
        p2++;
    }
    return 0;

}