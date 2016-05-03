#ifndef CACHE_NODE_H_
#define CACHE_NODE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>

typedef struct cache_node {
    char* key;
    char* value;
    struct cache_node* next;
    struct cache_node* prev;
} cache_node_t;

cache_node_t* create_cache_node(char* key, char* value) {
    cache_node_t* n = malloc(sizeof(cache_node_t));

    n->key   = key;
    n->value = value;
    n->next  = NULL;
    n->prev  = NULL;

    return n;
}

void append_cache_node(cache_node_t* n1, cache_node_t* n2) {
    if (n1->next != NULL) {
        printf("Error: key '%s' already have next item with key '%s'",
            n1->key, n1->next->key);
        exit(1);
    }

    n1->next = n2;
    n2->prev = n1;
}

void remove_cache_node(cache_node_t* n) {
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

    free(n);
}

// For testing purpose...
void get_cache_node_keys(cache_node_t* n, char** keys) {
    uint32_t i = 0;
    cache_node_t* tmp_n = n;

    do {
        *(keys + i++) = tmp_n->key;
        tmp_n = tmp_n->next;
    } while (tmp_n != NULL);
}

// For testing purpose...
void get_cache_node_keys_reverse(cache_node_t* n, char** keys) {
    uint32_t i = 0;
    cache_node_t* tmp_n = n;

    do {
        *(keys + i++) = tmp_n->key;
        tmp_n = tmp_n->prev;
    } while (tmp_n != NULL);
}

#ifdef __cplusplus
}
#endif

#endif
