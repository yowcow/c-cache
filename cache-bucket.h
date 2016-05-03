#ifndef CACHE_BUCKET_H_
#define CACHE_BUCKET_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "cache-node.h"

typedef struct cache_bucket {
    uint32_t size;
    cache_node_t* head;
    cache_node_t* tail;
} cache_bucket_t;

cache_bucket_t* create_cache_bucket() {
    cache_bucket_t* b = malloc(sizeof(cache_bucket_t));

    b->size = 0;
    b->head = NULL;
    b->tail = NULL;

    return b;
}

cache_node_t* find_node_in_cache_bucket(cache_bucket_t* b, const char* key) {
    if (!b->size) {
        return NULL;
    }

    cache_node_t* tmp_n = b->head;
    do {
        if (strcmp(tmp_n->key, key) == 0) {
            return tmp_n;
        }
        tmp_n = tmp_n->next;
    } while(tmp_n != NULL);

    return NULL;
}

cache_node_t* append_node_to_cache_bucket(cache_bucket_t* b, const char* key, const char* value) {
    if (!b->size) {
        cache_node_t* n = create_cache_node(key, value);

        b->head = n;
        b->tail = n;
        b->size += 1;

        return n;
    }
    else {
        cache_node_t* dupe_n = find_node_in_cache_bucket(b, key);

        if (dupe_n != NULL) {
            dupe_n->value = value;

            return dupe_n;
        }
        else {
            cache_node_t* n = create_cache_node(key, value);

            append_cache_node(b->tail, n);
            b->tail = n;
            b->size += 1;

            return n;
        }
    }
}

bool remove_node_in_cache_bucket(cache_bucket_t* b, const char* key) {
    cache_node_t* n = find_node_in_cache_bucket(b, key);

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

    remove_cache_node(n);

    return true;
}

void destroy_cache_bucket(cache_bucket_t* b) {
    if (b->size) {
        cache_node_t* tmp_n = b->head;
        cache_node_t* nxt_n = NULL;

        do {
            nxt_n = tmp_n->next;
            destroy_cache_node(tmp_n);
            tmp_n = nxt_n;
        } while(tmp_n != NULL);
    }

    free(b);
}

#ifdef __cplusplus
}
#endif

#endif
