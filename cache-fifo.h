#ifndef CACHE_FIFO_H_
#define CACHE_FIFO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include "hash.h"
#include "hash-node.h"

typedef struct _cache_fifo {
    uint32_t capacity;
    Hash* hash;
    HashNode* head;
    HashNode* tail;
} CacheFIFO;

CacheFIFO* CacheFIFO_create(uint32_t capacity);

void CacheFIFO_destroy(CacheFIFO* c);

bool CacheFIFO_put(CacheFIFO* c, char* key, char* val);

char* CacheFIFO_get(CacheFIFO* c, char* key);

bool CacheFIFO_del(CacheFIFO* c, char* key);

#ifdef __cplusplus
}
#endif

#endif
