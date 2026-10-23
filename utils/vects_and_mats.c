#ifndef VECTS_MATS_H
#define VECTS_MATS_H

#include "copper_da.h"
#define CGLM_ALL_UNALIGNED
#include "../vendor/cglm/include/cglm/cglm.h"
#define DA_CAP 128
#define TRANSFORM_CAP (DA_CAP / 4)

typedef vec2 Vec2f;
typedef vec3 Vec3f;
typedef vec4 Vec4f;
typedef mat4 Mat4s;
typedef ivec2 Vec2i;
typedef ivec3 Vec3i;
typedef ivec4 Vec4i;

typedef struct Vec2iArray {
    Vec2i *data;
    size_t count;
    size_t capacity;
} Vec2iArray;

void vec2i_append(Vec2iArray *arr, Vec2i vec){
    if(arr->count >= arr->capacity){
        if(arr->capacity == 0) arr->capacity = DA_CAP;
        else arr->capacity *= 2;
        arr->data = realloc(arr->data, arr->capacity * sizeof(*arr->data));
    }
    glm_ivec2_copy(vec, arr->data[arr->count++]);
}

typedef struct Vec2fArray {
    Vec2f *data;
    size_t count;
    size_t capacity;
} Vec2fArray;

void vec2f_append(Vec2fArray *arr, Vec2f vec){
    if(arr->count >= arr->capacity){
        if(arr->capacity == 0) arr->capacity = DA_CAP;
        else arr->capacity *= 2;
        arr->data = realloc(arr->data, arr->capacity * sizeof(*arr->data));
    }
    glm_vec2_copy(vec, arr->data[arr->count++]);
}

typedef struct Vec3iArray {
    Vec3i *data;
    size_t count;
    size_t capacity;
} Vec3iArray;

void vec3i_append(Vec3iArray *arr, Vec3i vec){
    if(arr->count >= arr->capacity){
        if(arr->capacity == 0) arr->capacity = DA_CAP;
        else arr->capacity *= 2;
        arr->data = realloc(arr->data, arr->capacity * sizeof(*arr->data));
    }
    glm_ivec3_copy(vec, arr->data[arr->count++]);
}

typedef struct Vec3fArray {
    Vec3f *data;
    size_t count;
    size_t capacity;
} Vec3fArray;

void vec3f_append(Vec3fArray *arr, Vec3f vec){
    if(arr->count >= arr->capacity){
        if(arr->capacity == 0) arr->capacity = DA_CAP;
        else arr->capacity *= 2;
        arr->data = realloc(arr->data, arr->capacity * sizeof(*arr->data));
    }
    glm_vec3_copy(vec, arr->data[arr->count++]);
}

typedef struct Vec4iArray {
    Vec4i *data;
    size_t count;
    size_t capacity;
} Vec4iArray;

void vec4i_append(Vec4iArray *arr, Vec4i vec){
    if(arr->count >= arr->capacity){
        if(arr->capacity == 0) arr->capacity = DA_CAP;
        else arr->capacity *= 2;
        arr->data = realloc(arr->data, arr->capacity * sizeof(*arr->data));
    }
    glm_ivec4_copy(vec, arr->data[arr->count++]);
}

typedef struct Vec4fArray {
    Vec4f *data;
    size_t count;
    size_t capacity;
} Vec4fArray;

void vec4f_append(Vec4fArray *arr, Vec4f vec){
    if(arr->count >= arr->capacity){
        if(arr->capacity == 0) arr->capacity = DA_CAP;
        else arr->capacity *= 2;
        arr->data = realloc(arr->data, arr->capacity * sizeof(*arr->data));
    }
    glm_vec4_copy((vec), arr->data[arr->count++]);
}

typedef struct Mats4sArray {
    Mat4s *data;
    size_t count;
    size_t capacity;
} Mats4sArray;
typedef Mats4sArray Transformations;
typedef Transformations Transforms;
#define mat4s_append(arr, mat) do {                                             \
    if((arr).count >= (arr).capacity){                                          \
        if((arr).capacity == 0) (arr).capacity = TRANSFORM_CAP;                 \
        else (arr).capacity *= 2;                                               \
        (arr).data = realloc((arr).data, (arr).capacity * sizeof(*(arr).data)); \
    }                                                                           \
    glm_mat4_copy((mat), (arr).data[(arr).count++]);                            \
} while (0)
#endif //VECTS_MATS_H
