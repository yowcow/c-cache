#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "murmurhash.h"

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

uint32_t Hash_key_size(Hash* h) {
    uint32_t size = 0;
    uint32_t i;

    for (i = 0; i < HASH_BUCKET_COUNT; i++) {
        size += h->buckets[i]->size;
    }

    return size;
}

bool Hash_delete(Hash* h, char* key) {
    uint32_t len = strlen(key);
    uint32_t slot = Hash_find_bucket_slot(key, len, h->seed);

    return HashBucket_remove_node(h->buckets[slot], key);
}
