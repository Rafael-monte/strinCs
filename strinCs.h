#include<stdlib.h>
#include<memory.h>
#include<stdio.h>
#include<string.h>
#include<limits.h>
#include<stdbool.h>

#ifndef EOS
    #define EOS '\0'
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
    res.capacity=str_size+1;
    res.content=(char*) malloc(sizeof(char)*res.capacity);
    if (!res.content) {
        fprintf(stderr, "Cannot allocate resources");       
        exit(EXIT_FAILURE);
    }
    memcpy(res.content, raw_str, str_size);
    res.content[res.capacity]=EOS;
    res.size=str_size;
    return res;
}

void erase_string(string* str) {
    free(str->content);
}

OPERATION_STATUS string_to_raw(string* str, char* buff, size_t chars_to_copy, bool should_erase) {
    if (chars_to_copy > str->size) {
        return FAIL;
    }
    strncpy(buff, str->content, chars_to_copy);

    if (should_erase) {
        erase_string(str);
    }
    return SUCCESS;
}