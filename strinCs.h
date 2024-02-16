#include<stdlib.h>
#include<memory.h>
#include<stdio.h>
#include<string.h>
#include<limits.h>
#include<stdbool.h>
#include<ctype.h>

#ifndef EOS
    #define EOS '\0'
#endif

#ifndef UPPER_SHIFTING_OP
    #define UPPER_SHIFTING_OP 32
#endif

#ifndef INDEX_NOT_FOUND
    #define INDEX_NOT_FOUND -1
#endif

typedef enum OPERATION_STATUS {
    SUCCESS=0,
    FAIL=1
} OPERATION_STATUS;

typedef struct string {
    char* content;
    size_t capacity;
    size_t size;
} string;

string raw_to_string(const char* raw_str)
{
    size_t str_size = strnlen(raw_str, LONG_MAX);
    if (str_size == LONG_MAX)
    {
        fprintf(stderr, "The provided string has not the NUL char (\\0). Aborting");
        exit(EXIT_FAILURE);
    }
    string res;
    res.capacity=str_size;
    res.size=str_size+1;
    res.content=(char*) malloc(sizeof(char)*res.size);
    if (!res.content) {
        fprintf(stderr, "Cannot allocate resources");       
        exit(EXIT_FAILURE);
    }
    memcpy(res.content, raw_str, str_size);
    res.content[res.capacity]=EOS;
    return res;
}

void erase_string(string* str) {
    free(str->content);
}

OPERATION_STATUS string_to_raw(string* str, char* buff, const size_t chars_to_copy, const bool should_erase) {
    if (chars_to_copy > str->size) {
        return FAIL;
    }
    strncpy(buff, str->content, chars_to_copy);

    if (should_erase) {
        erase_string(str);
    }
    return SUCCESS;
}

void Uppercase(string* str) {
    size_t buff_size=str->size;
    char buff[buff_size];
    for(size_t i = 0; i < buff_size; i++) {
        if (!islower(str->content[i])) {
            buff[i] = str->content[i];
            continue;
        }
        
        buff[i] = toupper(str->content[i]);
    }
    strncpy(str->content, buff, buff_size);
}


void Lowercase(string* str) {
    size_t buff_size = str->size;
    char buff[buff_size];
    for (size_t i = 0; i < buff_size; ++i) {
        if (!isupper(str->content[i])) {
            buff[i] = str->content[i];
            continue;
        }
        buff[i] = tolower(str->content[i]);
    } 
    strncpy(str->content, buff, buff_size);
}

int FindIndex(const string* str, const char desired_el) {
    const size_t start = 0;
    const size_t end = str->size;
    
    for (size_t i = start; i < end; ++i) {
        if (str->content[i] == desired_el) {
            return i;
        }
    }
    return INDEX_NOT_FOUND;
}

//TODO:
// int RFindIndex(string* str, char desired_el) {
//     return -1;
// }