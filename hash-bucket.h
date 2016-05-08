#ifndef HASH_BUCKET_H_
#define HASH_BUCKET_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "hash-node.h"

typedef struct _hash_bucket {
    uint32_t size;
    HashNode* head;
    HashNode* tail;
} HashBucket;

HashBucket* HashBucket_create() {
    HashBucket* b = malloc(sizeof(HashBucket));

    b->size = 0;
    b->head = NULL;
    b->tail = NULL;

    return b;
}

HashNode* HashBucket_find_node(HashBucket* b, char* key) {
    if (!b->size) {
        return NULL;
    }

    HashNode* tmp_n = b->head;

    do {
        if (strcmp(tmp_n->key, key) == 0) {
            return tmp_n;
        }
        tmp_n = tmp_n->next;
    } while(tmp_n != NULL);

    return NULL;
}

HashNode* HashBucket_append_node(HashBucket* b, char* key, char* val) {
    if (!b->size) {
        HashNode* n = HashNode_create(key, val);

        b->head = n;
        b->tail = n;
        b->size += 1;

        return n;
    }
    else {
        HashNode* dupe_n = HashBucket_find_node(b, key);

        if (dupe_n != NULL) {
            HashNode_update(dupe_n, val);

            return dupe_n;
        }
        else {
            HashNode* n = HashNode_create(key, val);

            HashNode_append(b->tail, n);
            b->tail = n;
            b->size += 1;

            return n;
        }
    }
}

bool HashBucket_remove_node(HashBucket* b, char* key) {
    HashNode* n = HashBucket_find_node(b, key);

    if (n == NULL) {
        return false;
    }

    // Removing node is the head
    if (strcmp(n->key, b->head->key) == 0) {
        b->head = b->head->next;
    }

    // Removing node is the tail
    if (strcmp(n->key, b->tail->key) == 0) {
        b->tail = b->tail->prev;
    }

    b->size--;

    HashNode_remove(n);

    return true;
}

void HashBucket_destroy(HashBucket* b) {
    if (b->size) {
        HashNode* tmp_n = b->head;
        HashNode* nxt_n = NULL;

        do {
            nxt_n = tmp_n->next;
            HashNode_destroy(tmp_n);
            tmp_n = nxt_n;
        } while(tmp_n != NULL);
    }

    free(b);
}

#ifdef __cplusplus
}
#endif

#endif
