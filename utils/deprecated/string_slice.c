// Known issue: begin pointer might dangle
#ifndef STRING_SLICE_H
#define STRING_SLICE_H

#include <stdio.h>
#include <stddef.h>
#include <limits.h>
#endif

typedef struct String_Slice String_Slice;
size_t cstring_len(char *cstring);
String_Slice string_slice_init(char *ptr, size_t len);
String_Slice string_slice_from_cstring(char *cstring);
int string_slice_compare_cstring(String_Slice *str, char *cstr);
int string_slice_compare(String_Slice *s1, String_Slice *s2);

#if defined(STRING_SLICE_IMPLEMENTATION) || defined(STRING_SLICE_EXAMPLE)
struct String_Slice {
    char *begin;
    size_t len;
};
#define string_slice_print(str) do {\
    if((str)->len <= INT_MAX) printf("%.*s", (int)(str)->len, (str)->begin);\
    if((str)->len > INT_MAX) fprintf(stderr, "String slice is too big!\n");\
} while(0)

size_t cstring_len(char *cstring){
    size_t result = 0;
    while(cstring[result] != '\0') result++;
    return result;
}

String_Slice string_slice_init(char *ptr, size_t len){
    return (String_Slice){
        .begin = ptr,
        .len = len
    };
}

String_Slice string_slice_from_cstring(char *cstring){
    return (String_Slice){
        .begin = cstring,
        .len = cstring_len(cstring)
    };
}

int string_slice_compare(String_Slice *s1, String_Slice *s2){
    size_t len = 0, index = 0, result = 0;
    if(s1->len < s2->len) len = s2->len;
    if(s1->len >= s2->len) len = s1->len;
    while(index < len){
        if(s1->begin[index] != s2->begin[index]) result++;
        index++;
    }
    return result;
}

int string_slice_compare_cstring(String_Slice *str, char *cstr){
    size_t len = 0, index = 0, result = 0;
    if(str->len < cstring_len(cstr)) len = cstring_len(cstr) ;
    if(str->len >= cstring_len(cstr)) len = str->len;
    while(index < len){
        if(str->begin[index] != cstr[index]) result++;
        index++;
    }
    return result;
}
#endif

#ifdef STRING_SLICE_EXAMPLE
int main(void){
    String_Slice str1 = string_slice_from_cstring("Hello");
    String_Slice str2 = string_slice_from_cstring("Hi");
    printf("Difference of: ");
    string_slice_print(&str1);
    printf(" and ");
    string_slice_print(&str2);
    printf(" is: %d\n", string_slice_compare(&str1, &str2));

    return 0;
}
#endif
