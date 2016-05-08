#ifndef HASH_H_
#define HASH_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "hash-bucket.h"
#include "murmurhash.h"

#define HASH_BUCKET_COUNT 127

typedef struct _hash {
    uint32_t seed;
    HashBucket* buckets[HASH_BUCKET_COUNT];
} Hash;

Hash* Hash_create() {
    Hash* h = malloc(sizeof(Hash));

    h->seed = (uint32_t)(rand() * UINT32_MAX);

    for (uint32_t i = 0; i < HASH_BUCKET_COUNT; i++) {
        HashBucket* b = HashBucket_create();
        h->buckets[i] = b;
    }

    return h;
}

void Hash_destroy(Hash* h) {
    for (uint32_t i = 0; i < HASH_BUCKET_COUNT; i++) {
        HashBucket_destroy(h->buckets[i]);
    }

    free(h);
}

uint32_t Hash_find_bucket_slot(char* key, uint32_t len, uint32_t seed) {
    return murmurhash(key, len, seed) % HASH_BUCKET_COUNT;
}

HashNode* Hash_set(Hash* h, char* key, char* val) {
    uint32_t len = strlen(key);
    uint32_t slot = Hash_find_bucket_slot(key, len, h->seed);

    return HashBucket_append_node(h->buckets[slot], key, val);
}

HashNode* Hash_get(Hash* h, char* key) {
    uint32_t len = strlen(key);
    uint32_t slot = Hash_find_bucket_slot(key, len, h->seed);

    return HashBucket_find_node(h->buckets[slot], key);
}

bool Hash_delete(Hash* h, char* key) {
    uint32_t len = strlen(key);
    uint32_t slot = Hash_find_bucket_slot(key, len, h->seed);

    return HashBucket_remove_node(h->buckets[slot], key);
}

#ifdef __cplusplus
}
#endif

#endif
