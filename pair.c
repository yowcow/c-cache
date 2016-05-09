#include <stdlib.h>
#include <string.h>
#include "pair.h"

Pair* Pair_create(char* key, char* val) {
    Pair* p = malloc(sizeof(Pair));

    p->key = malloc(sizeof(char) * (strlen(key) + 1));
    p->val = malloc(sizeof(char) * (strlen(val) + 1));

    strcpy(p->key, key);
    strcpy(p->val, val);

    return p;
}

void Pair_update(Pair* p, char* val) {
    free(p->val);
    p->val = malloc(sizeof(char) * (strlen(val) + 1));
    strcpy(p->val, val);
}

void Pair_destroy(Pair* p) {
    free(p->key);
    free(p->val);
    free(p);
}
