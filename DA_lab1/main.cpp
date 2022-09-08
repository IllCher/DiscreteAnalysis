#include <iostream>
#include <ctype.h>
typedef struct {
    char value[65] = {0};
    char key[33] = {0};
} Tkv;
typedef struct {
    Tkv* body;
    int size;
    int cap;
} TKeyValueVector;
TKeyValueVector* TCreate() {
    TKeyValueVector* v = (TKeyValueVector*)malloc(sizeof(TKeyValueVector));
    v->body = nullptr;
    v->size = 0;
    v->cap = 1;
    return v;
}
void TDelete(TKeyValueVector* v) {
    free(v->body);
    free(v);
}
void TSet(TKeyValueVector* v, int i, Tkv val) {
    v->body[i] = val;
}
Tkv TGet(TKeyValueVector* v, int i) {
    return v->body[i];
}
int TGetSize(TKeyValueVector* v) {
    return v->size;
}
int TGetCap(TKeyValueVector* v) {
    return v->cap;
}
void TSetSize(TKeyValueVector* v, int new_size) {
    v->size = new_size;
}
void TSetCap(TKeyValueVector* v, int new_size) {
    Tkv* reBody = (Tkv*)realloc(v->body, new_size * sizeof(Tkv));
    v->body = reBody;
}
int CharToInteger(char a) {
    if (isdigit(a)) {
        return (a-'0');
    } else {
       return (a-'W');
    }
}
void CountSort(TKeyValueVector* v, int k) {
    const int NUMBER_OF_HEX_DIGITS = 16;
    int n = TGetSize(v);
    TKeyValueVector* output = TCreate();
    TSetCap(output, n+1);
    TSetSize(output, n);
    int c[NUMBER_OF_HEX_DIGITS] = {0};
    for (int i = 0; i < n; i++) {
        c[CharToInteger(TGet(v, i).key[k])]++;
    }
    for (int i = 1; i < NUMBER_OF_HEX_DIGITS; i++) {
        c[i] += c[i - 1];
    }
    for (int i = n-1; i >= 0; i--) {
        TSet(output,c[CharToInteger(TGet(v, i).key[k])]-1, TGet(v, i));
        c[CharToInteger(TGet(v, i).key[k])]--;
    }
    for (int i = 0; i < n; i++) {
        TSet(v, i, TGet(output, i));
    }
    TDelete(output);
}
void RadixSort(TKeyValueVector* arr, int k) {
    for (int i = k; i >= 0; i--) {
        CountSort(arr, i);
    }
}
int main() {
    int posForRadix = 31;
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    TKeyValueVector* v = TCreate();
    Tkv elem;
    while (std::cin >> elem.key >> elem.value) {
        if (TGetSize(v) + 1 == TGetCap(v)) {
            v->cap *= 2;
            TSetCap(v, v->cap);
        }
        int size = TGetSize(v);
        TSet(v, size, elem);
        TSetSize(v, size + 1);
    }
    RadixSort(v, posForRadix);
    int size = TGetSize(v);
    for (int i = 0; i < size; i++) {
        std::cout << TGet(v, i).key << '\t' << TGet(v, i).value << std::endl;
    }
    TDelete(v);
    return 0;
}