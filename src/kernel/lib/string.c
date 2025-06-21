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
void* memset(void* ptr, const void* src, size_t num){
    
}
void* memcpy(void* ptr, const void* src, size_t num){
    unsigned char* p = (unsigned char*)ptr;
    while(num--){
        *p++ = (unsigned char*)
    }
    return ptr;
}

void* memmove(void* dest, const void* src, size_t n){
    unsigned char* d = (unsigned char*)dest;
    unsigned char* s = (unsigned char*)src;
    
    if(d==s || n==0){
        return dest;
    }

    if(d < s){
        for(size_t i =0, i<n; i++){
            d[i] = s[i];
        }
    }
    if( d > s){
        for( size_t i = n, i>0; i--){
            d[i-1] = s[i-1];
        }
    }
    return dest;
}

int memmcmp(void* ptr1, void* ptr2, int n){
    unsigned char* p1 = ptr1;
    unsigned char* p2 = ptr2; 

    for(int i =0; i<n; i++){
        if(*p1 > *p2){
            return 1;
        }
        else if(*p1 < *p2){
            return -1;
        }
        p1++;
        p2++;
    }
    return 0;

}