//#define ARR_FACTORY_EXAMPLE

#ifndef ARR_FACTORY_H
#define ARR_FACTORY_H
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#endif

typedef struct Header Header;
void read_from_file(char **arrFactory, const char *path);

#if defined(ARR_FACTORY_IMPLEMENTATION) || defined(ARR_FACTORY_EXAMPLE)
#define ARR_INIT_CAP 64
struct Header {
    size_t capacity;
    size_t len;
    max_align_t padding[];
};

#define arr_push(arr, value) do {                                                   \
    if((arr) == NULL){                                                              \
        Header *ptr = malloc(sizeof(*arr) * ARR_INIT_CAP + sizeof(Header));         \
        ptr->len = 0;                                                               \
        ptr->capacity = ARR_INIT_CAP;                                               \
        arr = (void*)(ptr + 1);                                                     \
    }                                                                               \
                                                                                    \
    Header *header = (Header*)(arr) - 1;                                            \
    if(header->len >= header->capacity){                                            \
        header->capacity *= 2;                                                      \
        header = realloc(header, sizeof(*arr) * header->capacity + sizeof(Header)); \
        arr = (void*)(header + 1);                                                  \
    }                                                                               \
    (arr)[header->len++] = (value);                                                 \
} while (0)

#define arr_len(arr) ((Header*)(arr) - 1)->len

#define arr_free(arr) do { free((Header*)(arr) - 1 );} while (0)

void read_from_file(char **arrFactory, const char *path){
    FILE *fp = fopen(path, "rb");
    if(fp == NULL){
        fprintf(stderr, "Cannot read file! Path: %s\n", path);
        exit(-1);
    }

    int character = fgetc(fp);
    while(character != EOF){
        arr_push(*arrFactory, (char)character);
        character = fgetc(fp);
    }
    arr_push(*arrFactory, '\0');
    fclose(fp);
}

#endif

#ifdef ARR_FACTORY_EXAMPLE
int main(void){
    float *numbers = NULL;
    arr_push(numbers, 18);
    arr_push(numbers, 10);
    arr_push(numbers, 20);
    arr_push(numbers, 0);
    arr_push(numbers, 125);
    arr_push(numbers, 36);
    printf("Len: %zu\n", arr_len(numbers));

    for(size_t i = 0; i < arr_len(numbers); i++){
        printf("\tnumbers[%zu] = %f\n", i, numbers[i]);
    }

    arr_free(numbers);
}
#endif
