#ifndef _VECTOR_H_
#define _VECTOR_H_
#include <cstdint>
#include <iostream>

typedef struct {
    char value[65];
    char key[33] = {0};
} kv;

typedef struct {
    kv* body;
    int size;
    int CAP;
} vector;

vector* v_create();
void v_delete(vector* v);
void v_set(vector* v, int i, kv val);
kv v_get(vector* v, int i);
int v_get_size(vector* v);
int v_get_CAP(vector* v);
void v_set_size(vector* v, int new_size);
void v_set_CAP(vector* v, int new_size);
#endif
