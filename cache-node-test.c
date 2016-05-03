#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "cache-node.h"

void test_create_cache_node() {
    printf("Working on %s...", __func__);

    cache_node_t* n = create_cache_node("key", "value");

    assert(strcmp(n->key, "key") == 0);
    assert(strcmp(n->value, "value") == 0);

    free(n);

    printf("OK\n");
}

void test_append_cache_node() {
    printf("Working on %s...", __func__);

    cache_node_t* n1 = create_cache_node("key1", "value1");
    cache_node_t* n2 = create_cache_node("key2", "value2");
    cache_node_t* n3 = create_cache_node("key3", "value3");

    append_cache_node(n1, n2);
    append_cache_node(n2, n3);

    assert(n1->prev == NULL);
    assert(strcmp(n1->next->key, n2->key) == 0);
    assert(strcmp(n2->prev->key, n1->key) == 0);
    assert(strcmp(n2->next->key, n3->key) == 0);
    assert(strcmp(n3->prev->key, n2->key) == 0);
    assert(n3->next == NULL);


    {
        char* keys[3];
        get_cache_node_keys(n1, keys);

        assert(strcmp(keys[0], "key1") == 0);
        assert(strcmp(keys[1], "key2") == 0);
        assert(strcmp(keys[2], "key3") == 0);
    }

    {
        char* keys[3];
        get_cache_node_keys_reverse(n3, keys);

        assert(strcmp(keys[2], "key1") == 0);
        assert(strcmp(keys[1], "key2") == 0);
        assert(strcmp(keys[0], "key3") == 0);
    }

    free(n1);
    free(n2);
    free(n3);

    printf("OK\n");
}

void test_remove_cache_node() {
    printf("Working on %s...", __func__);

    cache_node_t* n1 = create_cache_node("key1", "value1");
    cache_node_t* n2 = create_cache_node("key2", "value2");
    cache_node_t* n3 = create_cache_node("key3", "value3");
    cache_node_t* n4 = create_cache_node("key4", "value4");

    // Form a list: n1 <-> n2 <-> n3 <-> n4
    append_cache_node(n1, n2);
    append_cache_node(n2, n3);
    append_cache_node(n3, n4);

    // Make it: n1 <-> n3 <-> n4
    remove_cache_node(n2);

    {
        char* keys[3];
        get_cache_node_keys(n1, keys);

        assert(strcmp(keys[0], "key1") == 0);
        assert(strcmp(keys[1], "key3") == 0);
        assert(strcmp(keys[2], "key4") == 0);
    }

    {
        char* keys[4];
        get_cache_node_keys_reverse(n4, keys);

        assert(strcmp(keys[0], "key4") == 0);
        assert(strcmp(keys[1], "key3") == 0);
        assert(strcmp(keys[2], "key1") == 0);
    }

    // Make it: n3 <-> n4
    remove_cache_node(n1);

    {
        char* keys[2];
        get_cache_node_keys(n3, keys);

        assert(strcmp(keys[0], "key3") == 0);
        assert(strcmp(keys[1], "key4") == 0);
    }

    {
        char* keys[2];
        get_cache_node_keys_reverse(n4, keys);

        assert(strcmp(keys[0], "key4") == 0);
        assert(strcmp(keys[1], "key3") == 0);
    }

    // Make it: n3
    remove_cache_node(n4);

    {
        char* keys[1];
        get_cache_node_keys(n3, keys);

        assert(strcmp(keys[0], "key3") == 0);
    }

    {
        char* keys[1];
        get_cache_node_keys_reverse(n3, keys);

        assert(strcmp(keys[0], "key3") == 0);
    }

    remove_cache_node(n3);

    printf("OK\n");
}

int main() {
    test_create_cache_node();
    test_append_cache_node();
    test_remove_cache_node();
}
