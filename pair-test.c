#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "pair.h"

void test_pair_create() {
    printf("Testing %s...", __func__);

    Pair* p = Pair_create("key1", "val1");

    assert(strcmp(p->key, "key1") == 0);
    assert(strcmp(p->val, "val1") == 0);

    Pair_destroy(p);

    printf("Done\n");
}

void test_pair_update() {
    printf("Testing %s...", __func__);

    Pair* p = Pair_create("key1", "val1");

    p->update(p, "val12345");

    assert(strcmp(p->val, "val12345") == 0);

    Pair_destroy(p);

    printf("Done\n");
}

void test_pair_destroy() {
    printf("Testing %s...", __func__);

    Pair* p = Pair_create("key1", "val1");

    p->destroy(p);

    printf("Done\n");
}

int main() {
    test_pair_create();
    test_pair_update();
    test_pair_destroy();
    return 0;
}
