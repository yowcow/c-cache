#ifndef HASH_H_
#define HASH_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include "hash-bucket.h"

#define HASH_BUCKET_COUNT 127

typedef struct _hash {
    uint32_t seed;
    HashBucket* buckets[HASH_BUCKET_COUNT];
} Hash;

Hash* Hash_create();

void Hash_destroy(Hash* h);

uint32_t Hash_find_bucket_slot(char* key, uint32_t len, uint32_t seed);

HashNode* Hash_set(Hash* h, char* key, char* val);

HashNode* Hash_get(Hash* h, char* key);

bool Hash_delete(Hash* h, char* key);

#ifdef __cplusplus
}
#endif

#endif
