#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash-node.h"

HashNode* HashNode_create(void* data) {
    HashNode* n = malloc(sizeof(HashNode));

    n->data = data;
    n->next = NULL;
    n->prev = NULL;

    return n;
}

void HashNode_append(HashNode* n1, HashNode* n2) {
    if (n1->next != NULL) {
        printf("Error: node already has next item");
        exit(1);
    }

    n1->next = n2;
    n2->prev = n1;
}

void* HashNode_destroy(HashNode* n) {
    void* data = n->data;
    free(n);
    return data;
}

void* HashNode_remove(HashNode* n) {
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

    return HashNode_destroy(n);
}
