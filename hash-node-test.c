#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "hash-node.h"

void test_create_hash_node() {
    printf("Working on %s...", __func__);

    HashNode* n = HashNode_create("key", "value");

    assert(strcmp(n->pair->key, "key") == 0);
    assert(strcmp(n->pair->val, "value") == 0);

    HashNode_destroy(n);

    printf("OK\n");
}

void test_update_hash_node() {
    printf("Working on %s...", __func__);

    HashNode* n = HashNode_create("key", "value");

    HashNode_update(n, "value123");

    assert(strcmp(n->pair->val, "value123") == 0);

    HashNode_destroy(n);

    printf("OK\n");
}

void test_append_hash_node() {
    printf("Working on %s...", __func__);

    HashNode* n1 = HashNode_create("key1", "value1");
    HashNode* n2 = HashNode_create("key2", "value2");
    HashNode* n3 = HashNode_create("key3", "value3");

    HashNode_append(n1, n2);
    HashNode_append(n2, n3);

    assert(n1->prev == NULL);
    assert(strcmp(n1->next->pair->key, n2->pair->key) == 0);
    assert(strcmp(n2->prev->pair->key, n1->pair->key) == 0);
    assert(strcmp(n2->next->pair->key, n3->pair->key) == 0);
    assert(strcmp(n3->prev->pair->key, n2->pair->key) == 0);
    assert(n3->next == NULL);


    {
        char* keys[3];
        HashNode_get_keys(n1, keys);

        assert(strcmp(keys[0], "key1") == 0);
        assert(strcmp(keys[1], "key2") == 0);
        assert(strcmp(keys[2], "key3") == 0);
    }

    {
        char* keys[3];
        HashNode_get_keys_reverse(n3, keys);

        assert(strcmp(keys[2], "key1") == 0);
        assert(strcmp(keys[1], "key2") == 0);
        assert(strcmp(keys[0], "key3") == 0);
    }

    HashNode_destroy(n1);
    HashNode_destroy(n2);
    HashNode_destroy(n3);

    printf("OK\n");
}

void test_remove_hash_node() {
    printf("Working on %s...", __func__);

    HashNode* n1 = HashNode_create("key1", "value1");
    HashNode* n2 = HashNode_create("key2", "value2");
    HashNode* n3 = HashNode_create("key3", "value3");
    HashNode* n4 = HashNode_create("key4", "value4");

    // Form a list: n1 <-> n2 <-> n3 <-> n4
    HashNode_append(n1, n2);
    HashNode_append(n2, n3);
    HashNode_append(n3, n4);

    // Make it: n1 <-> n3 <-> n4
    HashNode_remove(n2);

    {
        char* keys[3];
        HashNode_get_keys(n1, keys);

        assert(strcmp(keys[0], "key1") == 0);
        assert(strcmp(keys[1], "key3") == 0);
        assert(strcmp(keys[2], "key4") == 0);
    }

    {
        char* keys[4];
        HashNode_get_keys_reverse(n4, keys);

        assert(strcmp(keys[0], "key4") == 0);
        assert(strcmp(keys[1], "key3") == 0);
        assert(strcmp(keys[2], "key1") == 0);
    }

    // Make it: n3 <-> n4
    HashNode_remove(n1);

    {
        char* keys[2];
        HashNode_get_keys(n3, keys);

        assert(strcmp(keys[0], "key3") == 0);
        assert(strcmp(keys[1], "key4") == 0);
    }

    {
        char* keys[2];
        HashNode_get_keys_reverse(n4, keys);

        assert(strcmp(keys[0], "key4") == 0);
        assert(strcmp(keys[1], "key3") == 0);
    }

    // Make it: n3
    HashNode_remove(n4);

    {
        char* keys[1];
        HashNode_get_keys(n3, keys);

        assert(strcmp(keys[0], "key3") == 0);
    }

    {
        char* keys[1];
        HashNode_get_keys_reverse(n3, keys);

        assert(strcmp(keys[0], "key3") == 0);
    }

    HashNode_remove(n3);

    printf("OK\n");
}

int main() {
    test_create_hash_node();
    test_update_hash_node();
    test_append_hash_node();
    test_remove_hash_node();
}
