#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

void test_Hash_create() {
    printf("Testing %s...", __func__);

    Hash* h = Hash_create();

    assert(0 <= h->seed && h->seed < UINT32_MAX);

    for (uint32_t i = 0; i < HASH_BUCKET_COUNT; i++) {
        assert(h->buckets[i]->size == 0);
        assert(h->buckets[i]->head == NULL);
        assert(h->buckets[i]->tail == NULL);
    }

   Hash_destroy(h);

    printf("Done\n");
}

void test_Hash_set() {
    printf("Testing %s...", __func__);

    Hash* h = Hash_create();

    // Overwrite seed for testing
    h->seed = 12345678;

    HashNode* n = Hash_set(h, "key1", "value1");

    uint32_t slot = Hash_find_bucket_slot("key1", 4, h->seed);

    assert(strcmp(n->key, "key1") == 0);
    assert(strcmp(n->val, "value1") == 0);
    assert(h->buckets[slot]->size == 1);
    assert(strcmp(h->buckets[slot]->head->key, "key1") == 0);
    assert(strcmp(h->buckets[slot]->tail->key, "key1") == 0);

    Hash_destroy(h);

    printf("Done\n");
}

void test_Hash_get() {
    printf("Testing %s...", __func__);

    Hash* h = Hash_create();

    // Overwrite seed for testing
    h->seed = 12345678;

    Hash_set(h, "key1", "value1");
    Hash_set(h, "key2", "value2");
    Hash_set(h, "key3", "value3");
    Hash_set(h, "key4", "value4");
    Hash_set(h, "key5", "value5");

    for (uint32_t i = 1; i <= 5; i++) {
        char key[5];
        char val[7];
        sprintf(key, "key%d", i);
        sprintf(val, "value%d", i);

        HashNode* n = Hash_get(h, key);

        assert(strcmp(n->val, val) == 0);
    }

    Hash_destroy(h);

    printf("Done\n");
}

void test_Hash_delete() {
    printf("Testing %s...", __func__);

    Hash* h = Hash_create();

    Hash_set(h, "key1", "value4");

    assert(Hash_delete(h, "key1") == true);
    assert(Hash_delete(h, "key1") == false);

    HashNode* n = Hash_get(h, "key1");

    assert(n == NULL);

    Hash_destroy(h);

    printf("Done\n");
}

int main() {
    test_Hash_create();
    test_Hash_set();
    test_Hash_get();
    test_Hash_delete();
    return 0;
}
