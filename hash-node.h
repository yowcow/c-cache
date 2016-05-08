#ifndef HASH_NODE_H_
#define HASH_NODE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

typedef struct _hash_node {
    const char* key;
    const char* value;
    struct _hash_node* next;
    struct _hash_node* prev;
} HashNode;

HashNode* HashNode_create(const char* key, const char* value) {
    HashNode* n = malloc(sizeof(HashNode));

    n->key   = key;
    n->value = value;
    n->next  = NULL;
    n->prev  = NULL;

    return n;
}

void HashNode_append(HashNode* n1, HashNode* n2) {
    if (n1->next != NULL) {
        printf("Error: key '%s' already have next item with key '%s'",
            n1->key, n1->next->key);
        exit(1);
    }

    n1->next = n2;
    n2->prev = n1;
}

void HashNode_destroy(HashNode* n) {
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
void HashNode_get_keys(HashNode* n, const char** keys) {
    uint32_t i = 0;
    HashNode* tmp_n = n;

    do {
        *(keys + i++) = tmp_n->key;
        tmp_n = tmp_n->next;
    } while (tmp_n != NULL);
}

// For testing purpose...
void HashNode_get_keys_reverse(HashNode* n, const char** keys) {
    uint32_t i = 0;
    HashNode* tmp_n = n;

    do {
        *(keys + i++) = tmp_n->key;
        tmp_n = tmp_n->prev;
    } while (tmp_n != NULL);
}

#ifdef __cplusplus
}
#endif

#endif
