#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H

#ifdef OBJ_LOADER_EXAMPLE
#define DEBUG 1
#elif !defined(DEBUG)
#define DEBUG 0
#endif

#include "vects_and_mats.c"
#define COPPER_STRING_SLICER
#define COPPER_STRING_FACTORY
#include "copper_string.c"
#endif

typedef enum NumberMode {
    MODE_BINARY,
    MODE_OCTAL,
    MODE_DECIMAL,
    MODE_HEX,
} NumberMode;

typedef enum Command {
    COMMAND_NONE,
    COMMAND_V,
    COMMAND_F
} Command;

typedef enum ElementType {
    TYPE_ILLEGAL,
    TYPE_VERTEX,
    TYPE_FACE
} ElementType;

typedef struct Element Element;
typedef struct Elements Elements;

int to_digit_opt(char character, NumberMode mode);
float to_float(String_Slice *token);
unsigned int to_u32(String_Slice *token);
int to_i32(String_Slice *token);
Elements obj_parse_from_tokens_opt(String_Slices *tokens, int debug);
#define obj_parse_from_tokens(tokens) obj_parse_from_tokens_opt((tokens), DEBUG)
//For now, only the two commands supported: v and f
//Else, we just pass them as not implemented

#if defined(OBJ_LOADER_IMPLEMENTATION) || defined(OBJ_LOADER_EXAMPLE)
struct Element {
    ElementType type;
    union {
        Vec3f pos;
        Vec3i indice;
    };
};

struct Elements {
    Element *data;
    size_t count;
    size_t capacity;
};

int to_digit_opt(char character, NumberMode mode){
    int result = 0;
    switch(mode){
        case MODE_DECIMAL:
            if(character > '9' || character < '0'){
                fprintf(stderr, "Not a digit!: %c\n", character);
                exit(-1);
            }
            else {
                result = character - '0';
            }
            break;
        default:
            break;
    }
    return result;
}

float to_float(String_Slice *token){
    float result = 0, result_2 = 0;
    for(size_t i = 0; i < token->len; i++){
        if(token->begin[token->len - i - 1] == (char)'f') continue;
        if(token->begin[token->len - i - 1] == (char)'.') break;
        result = (float)result / 10 + (float)to_digit_opt(token->begin[token->len - i - 1], MODE_DECIMAL);
    }
    result = (float)result / 10;
    for(size_t i = 0; i < token->len; i++){
        if(token->begin[i] == (char)'-' && i == 0) continue;
        if(token->begin[i] == (char)'.') break;
        else {
            result_2 = result_2 * 10 + to_digit_opt(token->begin[i], MODE_DECIMAL);
        }
    }
    result += result_2;
    if(token->begin[0] == (char)'-') result *= -1;
    return result;
}

unsigned int to_u32(String_Slice *token){
    unsigned int result = 0;
    for(size_t i = 0; i < token->len; i++){
        result = result * 10 + to_digit_opt(token->begin[i], MODE_DECIMAL);
    }
    return result;
}

int to_i32(String_Slice *token){
    int result = 0;
    for(size_t i = 0; i < token->len; i++){
        if(token->begin[i] == (char)'-' && i == 0) continue;
        result = result * 10 + to_digit_opt(token->begin[i], MODE_DECIMAL);
    }
    if(token->begin[0] == (char)'-') result *= -1;
    return result;
}

Elements obj_parse_from_tokens_opt(String_Slices *tokens, int debug){
    int isDebug = 0;
    isDebug = (debug > isDebug) ? debug : isDebug;
    Elements result = {0};
    Element temp = {0};
    size_t sub_index = 0;
    Command command  = COMMAND_NONE;
    for(size_t i = 0; i < tokens->count; i++){
        switch(command){
            case COMMAND_NONE:
                if(command != COMMAND_V && string_slice_compare_cstring(&tokens->data[i], "v") == 0){
                    if(isDebug > 0) fprintf(stdout, "Switching to v command... (Element index: %zu)\n", result.count - 1);
                    command = COMMAND_V;
                }
                else if(command != COMMAND_F && string_slice_compare_cstring(&tokens->data[i], "f") == 0){
                    if(isDebug > 0) fprintf(stdout, "Switching to f command... (Element index: %zu)\n", result.count - 1);
                    command = COMMAND_F;
                }
                break;
            case COMMAND_V:
                if(isDebug > 0) fprintf(stdout, "\tcurrent float: %f\n", to_float(&tokens->data[i]));
                temp.pos[sub_index] = to_float(&tokens->data[i]);
                sub_index++;
                if(sub_index >= 3){
                    sub_index = 0;
                    temp.type = TYPE_VERTEX;
                    da_append(result, temp);
                    command = COMMAND_NONE;
                }
                break;
            case COMMAND_F:
                if(isDebug > 0) fprintf(stdout, "\tcurrent i32: %d\n", to_i32(&tokens->data[i]));
                temp.indice[sub_index] = to_i32(&tokens->data[i]);
                sub_index++;
                if(sub_index >= 3){
                    sub_index = 0;
                    temp.type = TYPE_FACE;
                    da_append(result, temp);
                    command = COMMAND_NONE;
                }
                break;
            default:
                fprintf(stdout, "\"");
                string_slice_print(&tokens->data[i]);
                fprintf(stdout, "\" is either invalid, or not implemented!\n");
                break;
        }
    }
    return result;
}
#endif

#ifdef OBJ_LOADER_EXAMPLE
int main(void){
    char *source = NULL;
    read_from_file(&source, "assets/cube.obj");
    char *delimiters = " \n";
    String_Slices tokens = {0};
    tokens = tokenize_cstring_with_delimiters(source, delimiters);
    obj_parse_from_tokens(&tokens);
    arr_free(source);
    return 0;
}
#endif
