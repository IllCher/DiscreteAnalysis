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

vector* v_create() {
    vector* v = (vector*)malloc(sizeof(vector));
    v->body = nullptr;
    v->size = 0;
    v->CAP = 1;
    return v;
}

void v_delete(vector* v) {
    free(v->body);
    free(v);
}

void v_set(vector* v, int i, kv val) {
    v->body[i] = val;
}

kv v_get(vector* v, int i) {
    return v->body[i];
}

int v_get_size(vector* v) {
    return v->size;
}

int v_get_CAP(vector* v) {
    return v->CAP;
}

void v_set_size(vector* v, int new_size) {
    v->size = new_size;
}
void v_set_CAP(vector* v, int new_size) {
    kv* reBody = (kv*)realloc(v->body, new_size * sizeof(kv));
    v->body = reBody;
}

/*int main() {
    vector* v = v_create();
    int x;
    while (std::cin >> x) {
        if (v_get_size(v) + 1 == v_get_CAP(v)) {
            v->CAP *= 2;
            v_set_CAP(v, v->CAP);
        }
        v_set(v, v_get_size(v), x);
        v_set_size(v, v_get_size(v) + 1);
    }
    std::cout << v_get_CAP(v) << ' ' << v_get_size(v);
}*/
