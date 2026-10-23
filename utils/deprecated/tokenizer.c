#ifndef TOKENIZER_H
#define TOKENIZER_H
    #if defined(TOKENIZER_IMPLEMENTATION) || defined(TOKENIZER_EXAMPLE)
#define ARR_FACTORY_IMPLEMENTATION
#define STRING_SLICE_IMPLEMENTATION
    #endif
#include "arr_factory.c"
#include "string_slice.c"
#endif

typedef String_Slice Token;
typedef struct Tokens Tokens;
Tokens tokenize_with_delimiters(char *buffer, char *delimiters); /* the buffer is an arr_factory, the delimiters are null-terminated */
Tokens tokenize_cstring_with_delimiters(char *buffer, char *delimiters); /* the buffer & delimiters are null-terminated */
Tokens tokenize_string_slice_with_delimiters(String_Slice *src, char *delimiters); /* the delimiters are null-terminated */

#if defined(TOKENIZER_IMPLEMENTATION) || defined(TOKENIZER_EXAMPLE)
struct Tokens {
    Token *data;
    size_t count;
    size_t capacity;
};
#define TOKENS_CAP 128
#define tokens_append(arr, str) do {                                            \
    if((arr).count >= (arr).capacity){                                          \
        if((arr).capacity == 0) (arr).capacity = TOKENS_CAP;                    \
        else (arr).capacity *= 2;                                               \
        (arr).data = realloc((arr).data, (arr).capacity * sizeof(*(arr).data)); \
    }                                                                           \
    (arr).data[(arr).count++] = (str);                                          \
} while (0)
#define tokens_free(arr) do {       \
    free((arr).data);               \
    (arr).count = 0;                \
    (arr).capacity = 0;             \
} while (0)
#define tokens_pop(arr) do { (arr).count--; } while (0)
#define tokens_pop_all(arr) do { (arr).count = 0; } while (0)

Tokens tokenize_with_delimiters(char *buffer, char *delimiters){
    Tokens result = {0};
    Token temp = {
        .begin = buffer,
        .len = 0
    };

    size_t offset = 0;
    size_t is_valid = 0;
    for(size_t i = 0; i < arr_len(buffer); i++){
        is_valid = 1;
        for(size_t j = 0; j < cstring_len(delimiters); j++){
            if (buffer[i] == delimiters[j]) is_valid = 0;
        }

        if(is_valid == 0){
            offset++;
        }

        if(is_valid == 1){
            if(offset > 0){
                tokens_append(result, temp);
                temp.begin = buffer + i;
                temp.len = 0;
                offset = 0;
            }
            temp.len++;
        }
    }
    
    return result;
} /* the buffer is an arr_factory, the delimiters are null-terminated */

Tokens tokenize_cstring_with_delimiters(char *buffer, char *delimiters){
    Tokens result = {0};
    Token temp = {
        .begin = buffer,
        .len = 0
    };

    size_t offset = 0;
    size_t is_valid = 0;
    for(size_t i = 0; i < cstring_len(buffer); i++){
        is_valid = 1;
        for(size_t j = 0; j < cstring_len(delimiters); j++){
            if (buffer[i] == delimiters[j]) is_valid = 0;
        }

        if(is_valid == 0){
            offset++;
        }

        if(is_valid == 1){
            if(offset > 0){
                tokens_append(result, temp);
                temp.begin = buffer + i;
                temp.len = 0;
                offset = 0;
            }
            temp.len++;
        }
    }
    tokens_append(result, temp);

    return result;
} /* the buffer & delimiters are null-terminated */

Tokens tokenize_string_slice_with_delimiters(String_Slice *src, char *delimiters){
    Tokens result = {0};
    Token temp = {
        .begin = src->begin,
        .len = 0
    };

    size_t offset = 0;
    size_t is_valid = 0;
    for(size_t i = 0; i < src->len; i++){
        is_valid = 1;
        for(size_t j = 0; j < cstring_len(delimiters); j++){
            if (src->begin[i] == delimiters[j]) is_valid = 0;
        }

        if(is_valid == 0){
            offset++;
        }

        if(is_valid == 1){
            if(offset > 0){
                tokens_append(result, temp);
                temp.begin = src->begin + i;
                temp.len = 0;
                offset = 0;
            }
            temp.len++;
        }
    }

    tokens_append(result, temp);
    return result;
} /* the delimiters are null-terminated */

#endif

#ifdef TOKENIZER_EXAMPLE
int main(void){
    Tokens tokens = {0};
    char *example_str = "This, may not be a long string, but still impressive.";
    
    char *delimiter = " ,\n";
    tokens = tokenize_cstring_with_delimiters(example_str, delimiter);
    printf("Tokens count: %zu\n", tokens.count);
    for(size_t i = 0; i < tokens.count; i++){
        string_slice_print(&tokens.data[i]);
        printf("\n");
    }
    
    tokens_free(tokens);
    return 0;
}
#endif
