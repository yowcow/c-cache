#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "cache-hash.h"

void test_create_cache_hash() {
    printf("Testing %s...", __func__);

    cache_hash_t* h = create_cache_hash();

    assert(0 <= h->seed && h->seed < UINT32_MAX);

    for (uint32_t i = 0; i < CACHE_BUCKET_COUNT; i++) {
        assert(h->buckets[i]->size == 0);
        assert(h->buckets[i]->head == NULL);
        assert(h->buckets[i]->tail == NULL);

        destroy_cache_bucket(h->buckets[i]);
    }

    free(h);

    printf("Done\n");
}

void test_set_cache_hash() {
    printf("Testing %s...", __func__);

    cache_hash_t* h = create_cache_hash();

    // Overwrite seed for testing
    h->seed = 12345678;

    cache_node_t* n = set_cache_hash(h, "key1", "value1");

    uint32_t slot = cache_bucket_slot("key1", 4, h->seed);

    assert(strcmp(n->key, "key1") == 0);
    assert(strcmp(n->value, "value1") == 0);
    assert(h->buckets[slot]->size == 1);
    assert(strcmp(h->buckets[slot]->head->key, "key1") == 0);
    assert(strcmp(h->buckets[slot]->tail->key, "key1") == 0);

    destroy_cache_hash(h);

    printf("Done\n");
}

void test_get_cache_hash() {
    printf("Testing %s...", __func__);

    cache_hash_t* h = create_cache_hash();

    // Overwrite seed for testing
    h->seed = 12345678;

    set_cache_hash(h, "key1", "value1");
    set_cache_hash(h, "key2", "value2");
    set_cache_hash(h, "key3", "value3");
    set_cache_hash(h, "key4", "value4");
    set_cache_hash(h, "key5", "value5");

    for (uint32_t i = 1; i <= 5; i++) {
        char key[5];
        char val[7];
        sprintf(key, "key%d", i);
        sprintf(val, "value%d", i);

        cache_node_t* n = get_cache_hash(h, key);

        assert(strcmp(n->value, val) == 0);
    }

    destroy_cache_hash(h);

    printf("Done\n");
}

void test_delete_cache_hash() {
    printf("Testing %s...", __func__);

    cache_hash_t* h = create_cache_hash();

    set_cache_hash(h, "key1", "value4");

    assert(delete_cache_hash(h, "key1") == true);
    assert(delete_cache_hash(h, "key1") == false);

    cache_node_t* n = get_cache_hash(h, "key1");

    assert(n == NULL);

    destroy_cache_hash(h);

    printf("Done\n");
}

int main() {
    test_create_cache_hash();
    test_set_cache_hash();
    test_get_cache_hash();
    test_delete_cache_hash();
    return 0;
}
