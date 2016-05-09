#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "hash-node.h"
#include "pair.h"

HashNode* HashNode_create(char* key, char* val) {
    HashNode* n = malloc(sizeof(HashNode));
    Pair* p = Pair_create(key, val);

    n->pair = p;
    n->next = NULL;
    n->prev = NULL;

    return n;
}

void HashNode_append(HashNode* n1, HashNode* n2) {
    if (n1->next != NULL) {
        printf("Error: key '%s' already have next item with key '%s'",
            n1->pair->key, n1->next->pair->key);
        exit(1);
    }

    n1->next = n2;
    n2->prev = n1;
}

void HashNode_update(HashNode* n, char* val) {
    Pair_update(n->pair, val);
}

void HashNode_destroy(HashNode* n) {
    Pair_destroy(n->pair);
    free(n);
}

void HashNode_remove(HashNode* n) {
    if (n->prev != NULL) {
        if (n->next != NULL) {
            n->prev->next = n->next;
        }
        else {
            n->prev->next = NULL;
        }
    }

    if (n->next != NULL) {
        if (n->prev != NULL) {
            n->next->prev = n->prev;
        }
        else {
            n->next->prev = NULL;
        }
    }

    HashNode_destroy(n);
}

// For testing purpose...
void HashNode_get_keys(HashNode* n, char** keys) {
    uint32_t i = 0;
    HashNode* tmp_n = n;

    do {
        *(keys + i++) = tmp_n->pair->key;
        tmp_n = tmp_n->next;
    } while (tmp_n != NULL);
}

// For testing purpose...
void HashNode_get_keys_reverse(HashNode* n, char** keys) {
    uint32_t i = 0;
    HashNode* tmp_n = n;

    do {
        *(keys + i++) = tmp_n->pair->key;
        tmp_n = tmp_n->prev;
    } while (tmp_n != NULL);
}
