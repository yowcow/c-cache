#ifndef CACHE_HASH_H_
#define CACHE_HASH_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "cache-bucket.h"
#include "murmurhash.h"

#define CACHE_BUCKET_COUNT 127

typedef struct cache_hash {
    uint32_t seed;
    cache_bucket_t* buckets[CACHE_BUCKET_COUNT];
} cache_hash_t;

cache_hash_t* create_cache_hash() {
    cache_hash_t* h = malloc(sizeof(cache_hash_t));

    h->seed = (uint32_t)(rand() * UINT32_MAX);

    for (uint32_t i = 0; i < CACHE_BUCKET_COUNT; i++) {
        cache_bucket_t* b = create_cache_bucket();
        h->buckets[i] = b;
    }

    return h;
}

void destroy_cache_hash(cache_hash_t* h) {
    for (uint32_t i = 0; i < CACHE_BUCKET_COUNT; i++) {
        destroy_cache_bucket(h->buckets[i]);
    }

    free(h);
}

uint32_t cache_bucket_slot(const char* key, uint32_t len, uint32_t seed) {
    return murmurhash(key, len, seed) % CACHE_BUCKET_COUNT;
}

cache_node_t* set_cache_hash(cache_hash_t* h, const char* key, const char* value) {
    uint32_t len = strlen(key);
    uint32_t slot = cache_bucket_slot(key, len, h->seed);

    return append_node_to_cache_bucket(h->buckets[slot], key, value);
}

cache_node_t* get_cache_hash(cache_hash_t* h, const char* key) {
    uint32_t len = strlen(key);
    uint32_t slot = cache_bucket_slot(key, len, h->seed);

    return find_node_in_cache_bucket(h->buckets[slot], key);
}

bool delete_cache_hash(cache_hash_t* h, const char* key) {
    uint32_t len = strlen(key);
    uint32_t slot = cache_bucket_slot(key, len, h->seed);

    return remove_node_in_cache_bucket(h->buckets[slot], key);
}

#ifdef __cplusplus
}
#endif

#endif
