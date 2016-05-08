#ifndef HASH_BUCKET_H_
#define HASH_BUCKET_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include "hash-node.h"

typedef struct _hash_bucket {
    uint32_t size;
    HashNode* head;
    HashNode* tail;
} HashBucket;

HashBucket* HashBucket_create();

HashNode* HashBucket_find_node(HashBucket* b, char* key);

HashNode* HashBucket_append_node(HashBucket* b, char* key, char* val);

bool HashBucket_remove_node(HashBucket* b, char* key);

void HashBucket_destroy(HashBucket* b);

#ifdef __cplusplus
}
#endif

#endif
