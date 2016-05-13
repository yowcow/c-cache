#include <stdlib.h>
#include <string.h>
#include "pair.h"

Pair* Pair_create(char* key, char* val) {
    Pair* p = malloc(sizeof(Pair));

    p->key = strdup(key);
    p->val = strdup(val);

    return p;
}

void Pair_update(Pair* p, char* val) {
    free(p->val);
    p->val = strdup(val);
}

void Pair_destroy(Pair* p) {
    free(p->key);
    free(p->val);
    free(p);
}
