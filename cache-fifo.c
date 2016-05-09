#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "cache-fifo.h"
#include "hash.h"
#include "hash-node.h"

CacheFIFO* CacheFIFO_create(uint32_t capacity) {
    CacheFIFO* c = malloc(sizeof(CacheFIFO));

    c->capacity = capacity;
    c->hash = Hash_create();
    c->head = NULL;
    c->tail = NULL;

    return c;
}

void CacheFIFO_destroy(CacheFIFO* c) {
    Hash_destroy(c->hash);
    free(c);
}

bool CacheFIFO_put(CacheFIFO* c, char* key, char* val) {
    Hash_set(c->hash, key, val);
    return true;
}

char* CacheFIFO_get(CacheFIFO* c, char* key) {
    HashNode* n = Hash_get(c->hash, key);
    return n != NULL ? n->val : NULL;
}

bool CacheFIFO_del(CacheFIFO* c, char* key) {
    return Hash_delete(c->hash, key);
}
