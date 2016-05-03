#ifndef CACHE_HASH_H_
#define CACHE_HASH_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define CACHE_HASH_BUCKET_COUNT 4

typedef struct cache_hash {
    uint32_t seed;
    cache_hash_bucket_t* buckets[CACHE_HASH_BUCKET_COUNT];
} cache_hash_t;

#ifdef __cplusplus
}
#endif

#endif
