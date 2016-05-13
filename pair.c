#include <stdlib.h>
#include <string.h>
#include "pair.h"

Pair* Pair_create(const char* key, const char* val) {
    Pair* p = malloc(sizeof(Pair));

    p->key = strdup(key);
    p->val = strdup(val);
    p->destroy = Pair_destroy;
    p->update  = Pair_update;

    return p;
}

void Pair_update(Pair* p, const char* val) {
    free((char*) p->val);
    p->val = strdup(val);
}

void Pair_destroy(Pair* p) {
    free((char*) p->key);
    free((char*) p->val);
    free(p);
}
