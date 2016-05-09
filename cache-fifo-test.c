#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "cache-fifo.h"

void test_cache_create() {
    printf("Testing %s...", __func__);

    CacheFIFO* c = CacheFIFO_create(2);

    assert(c->capacity == 2);
    assert(c->head == NULL);
    assert(c->tail == NULL);

    CacheFIFO_destroy(c);

    printf("Done\n");
}

void test_cache_put() {
    printf("Testing %s...", __func__);

    CacheFIFO* c = CacheFIFO_create(2);

    CacheFIFO_put(c, "key1", "val1");
    CacheFIFO_put(c, "key2", "val2");
    CacheFIFO_put(c, "key3", "val3");

    CacheFIFO_destroy(c);

    printf("Done\n");
}

void test_cache_get() {
    printf("Testing %s...", __func__);

    CacheFIFO* c = CacheFIFO_create(2);

    CacheFIFO_put(c, "key1", "val1");
    CacheFIFO_put(c, "key2", "val2");
    CacheFIFO_put(c, "key3", "val3");

    assert(strcmp(CacheFIFO_get(c, "key3"), "val3") == 0);
    assert(strcmp(CacheFIFO_get(c, "key2"), "val2") == 0);

    //TODO: Not implemented
    //assert(CacheFIFO_get(c, "key1") == NULL);

    CacheFIFO_destroy(c);

    printf("Done\n");
}

void test_cache_del() {
    printf("Testing %s...", __func__);

    CacheFIFO* c = CacheFIFO_create(2);

    CacheFIFO_put(c, "key1", "val1");

    assert(CacheFIFO_del(c, "key1") == true);
    assert(CacheFIFO_del(c, "key1") == false);
    assert(CacheFIFO_get(c, "key1") == NULL);

    CacheFIFO_destroy(c);

    printf("Done\n");
}

int main() {
    test_cache_create();
    test_cache_put();
    test_cache_get();
    test_cache_del();
    return 0;
}
