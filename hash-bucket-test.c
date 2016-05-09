#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "hash-bucket.h"

void test_create_hash_bucket() {
    printf("Testing %s...", __func__);

    HashBucket* b = HashBucket_create();

    assert(b->size == 0);
    assert(b->head == NULL);
    assert(b->tail == NULL);

    HashBucket_destroy(b);

    printf("Done\n");
}

void test_append_node_to_hash_bucket() {
    printf("Testing %s...", __func__);

    HashBucket* b = HashBucket_create();

    {
        HashNode* n = HashBucket_append_node(b, "key1", "value1");

        assert(b->size == 1);
        assert(strcmp(b->head->pair->key, "key1") == 0);
        assert(strcmp(b->tail->pair->key, "key1") == 0);
        assert(strcmp(n->pair->key, b->tail->pair->key) == 0);
    }

    {
        HashNode* n = HashBucket_append_node(b, "key2", "value2");

        assert(b->size == 2);
        assert(strcmp(b->head->pair->key, "key1") == 0);
        assert(strcmp(b->head->next->pair->key, "key2") == 0);
        assert(strcmp(b->tail->pair->key, "key2") == 0);
        assert(strcmp(b->tail->prev->pair->key, "key1") == 0);
        assert(strcmp(n->pair->key, b->tail->pair->key) == 0);
    }

    {
        HashNode* n = HashBucket_append_node(b, "key3", "value3");

        assert(b->size == 3);
        assert(strcmp(b->head->pair->key, "key1") == 0);
        assert(strcmp(b->head->next->pair->key, "key2") == 0);
        assert(strcmp(b->tail->pair->key, "key3") == 0);
        assert(strcmp(b->tail->prev->pair->key, "key2") == 0);
        assert(strcmp(n->pair->key, b->tail->pair->key) == 0);
    }

    {
        HashNode* n = HashBucket_append_node(b, "key3", "value333");

        assert(b->size == 3);
        assert(strcmp(b->tail->pair->key, "key3") == 0);
        assert(strcmp(b->tail->pair->val, "value333") == 0); // Overwritten
        assert(strcmp(n->pair->val, b->tail->pair->val) == 0);
    }

    HashBucket_destroy(b);

    printf("Done\n");
}

void test_find_node_in_hash_bucket() {
    printf("Testing %s...", __func__);

    HashBucket* b = HashBucket_create();

    {
        HashNode* n = HashBucket_find_node(b, "hoge");

        assert(n == NULL);
    }

    HashBucket_append_node(b, "key1", "value1");
    HashBucket_append_node(b, "key2", "value2");
    HashBucket_append_node(b, "key3", "value3");

    {
        HashNode* n = HashBucket_find_node(b, "key3");

        assert(strcmp(n->pair->key, "key3") == 0);
    }

    {
        HashNode* n = HashBucket_find_node(b, "nonexisting");

        assert(n == NULL);
    }

    HashBucket_destroy(b);

    printf("Done\n");
}

void test_remove_node_in_hash_bucket() {
    printf("Testing %s...", __func__);

    HashBucket* b = HashBucket_create();

    {
        assert(HashBucket_remove_node(b, "hoge") == false);
    }

    // Form a list: n1 -> n2 -> n3 -> n4
    HashBucket_append_node(b, "n1", "value1");
    HashBucket_append_node(b, "n2", "value2");
    HashBucket_append_node(b, "n3", "value3");
    HashBucket_append_node(b, "n4", "value4");

    {
        // Make it: n1 -> n2 -> n4
        assert(HashBucket_remove_node(b, "n3") == true);
        assert(b->size == 3);
        assert(strcmp(b->head->pair->key, "n1") == 0);
        assert(strcmp(b->tail->pair->key, "n4") == 0);
    }

    {
        // Make it: n1 -> n2
        assert(HashBucket_remove_node(b, "n4") == true);
        assert(b->size == 2);
        assert(strcmp(b->head->pair->key, "n1") == 0);
        assert(strcmp(b->tail->pair->key, "n2") == 0);
    }

    {
        // Make it: n2
        assert(HashBucket_remove_node(b, "n1") == true);
        assert(b->size == 1);
        assert(strcmp(b->head->pair->key, "n2") == 0);
        assert(strcmp(b->tail->pair->key, "n2") == 0);
    }

    {
        // Make it empty
        assert(HashBucket_remove_node(b, "n2") == true);
        assert(b->size == 0);
        assert(b->head == NULL);
        assert(b->tail == NULL);
    }

    HashBucket_destroy(b);

    printf("Done\n");
}

void test_destroy_hash_bucket() {
    printf("Testing %s...", __func__);

    HashBucket* b = HashBucket_create();

    HashBucket_append_node(b, "n1", "value1");
    HashBucket_append_node(b, "n2", "value2");
    HashBucket_append_node(b, "n3", "value3");
    HashBucket_append_node(b, "n4", "value4");

    HashBucket_destroy(b);

    printf("Done\n");
}

int main() {
    test_create_hash_bucket();
    test_append_node_to_hash_bucket();
    test_find_node_in_hash_bucket();
    test_remove_node_in_hash_bucket();
    test_destroy_hash_bucket();
    return 0;
}
