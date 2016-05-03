#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "cache-bucket.h"

void test_create_cache_bucket() {
    printf("Testing %s...", __func__);

    cache_bucket_t* b = create_cache_bucket();

    assert(b->size == 0);
    assert(b->head == NULL);
    assert(b->tail == NULL);

    free(b);

    printf("Done\n");
}

void test_append_node_to_cache_bucket() {
    printf("Testing %s...", __func__);

    cache_bucket_t* b = create_cache_bucket();

    {
        cache_node_t* n = append_node_to_cache_bucket(b, "key1", "value1");

        assert(b->size == 1);
        assert(strcmp(b->head->key, "key1") == 0);
        assert(strcmp(b->tail->key, "key1") == 0);
        assert(strcmp(n->key, b->tail->key) == 0);
    }

    {
        cache_node_t* n = append_node_to_cache_bucket(b, "key2", "value2");

        assert(b->size == 2);
        assert(strcmp(b->head->key, "key1") == 0);
        assert(strcmp(b->head->next->key, "key2") == 0);
        assert(strcmp(b->tail->key, "key2") == 0);
        assert(strcmp(b->tail->prev->key, "key1") == 0);
        assert(strcmp(n->key, b->tail->key) == 0);
    }

    {
        cache_node_t* n = append_node_to_cache_bucket(b, "key3", "value3");

        assert(b->size == 3);
        assert(strcmp(b->head->key, "key1") == 0);
        assert(strcmp(b->head->next->key, "key2") == 0);
        assert(strcmp(b->tail->key, "key3") == 0);
        assert(strcmp(b->tail->prev->key, "key2") == 0);
        assert(strcmp(n->key, b->tail->key) == 0);
    }

    {
        cache_node_t* n = append_node_to_cache_bucket(b, "key3", "value333");

        assert(b->size == 3);
        assert(strcmp(b->tail->key, "key3") == 0);
        assert(strcmp(b->tail->value, "value333") == 0); // Overwritten
        assert(strcmp(n->value, b->tail->value) == 0);
    }

    destroy_cache_bucket(b);

    printf("Done\n");
}

void test_find_node_in_cache_bucket() {
    printf("Testing %s...", __func__);

    cache_bucket_t* b = create_cache_bucket();

    {
        cache_node_t* n = find_node_in_cache_bucket(b, "hoge");

        assert(n == NULL);
    }

    append_node_to_cache_bucket(b, "key1", "value1");
    append_node_to_cache_bucket(b, "key2", "value2");
    append_node_to_cache_bucket(b, "key3", "value3");

    {
        cache_node_t* n = find_node_in_cache_bucket(b, "key3");

        assert(strcmp(n->key, "key3") == 0);
    }

    {
        cache_node_t* n = find_node_in_cache_bucket(b, "nonexisting");

        assert(n == NULL);
    }

    destroy_cache_bucket(b);

    printf("Done\n");
}

void test_remove_node_in_cache_bucket() {
    printf("Testing %s...", __func__);

    cache_bucket_t* b = create_cache_bucket();

    {
        assert(remove_node_in_cache_bucket(b, "hoge") == false);
    }

    // Form a list: n1 -> n2 -> n3 -> n4
    append_node_to_cache_bucket(b, "n1", "value1");
    append_node_to_cache_bucket(b, "n2", "value2");
    append_node_to_cache_bucket(b, "n3", "value3");
    append_node_to_cache_bucket(b, "n4", "value4");

    {
        // Make it: n1 -> n2 -> n4
        assert(remove_node_in_cache_bucket(b, "n3") == true);
        assert(b->size == 3);
        assert(strcmp(b->head->key, "n1") == 0);
        assert(strcmp(b->tail->key, "n4") == 0);
    }

    {
        // Make it: n1 -> n2
        assert(remove_node_in_cache_bucket(b, "n4") == true);
        assert(b->size == 2);
        assert(strcmp(b->head->key, "n1") == 0);
        assert(strcmp(b->tail->key, "n2") == 0);
    }

    {
        // Make it: n2
        assert(remove_node_in_cache_bucket(b, "n1") == true);
        assert(b->size == 1);
        assert(strcmp(b->head->key, "n2") == 0);
        assert(strcmp(b->tail->key, "n2") == 0);
    }

    {
        // Make it empty
        assert(remove_node_in_cache_bucket(b, "n2") == true);
        assert(b->size == 0);
        assert(b->head == NULL);
        assert(b->tail == NULL);
    }

    free(b);

    printf("Done\n");
}

void test_destroy_cache_bucket() {
    printf("Testing %s...", __func__);

    cache_bucket_t* b = create_cache_bucket();

    append_node_to_cache_bucket(b, "n1", "value1");
    append_node_to_cache_bucket(b, "n2", "value2");
    append_node_to_cache_bucket(b, "n3", "value3");
    append_node_to_cache_bucket(b, "n4", "value4");

    destroy_cache_bucket(b);

    printf("Done\n");
}

int main() {
    test_create_cache_bucket();
    test_append_node_to_cache_bucket();
    test_find_node_in_cache_bucket();
    test_remove_node_in_cache_bucket();
    test_destroy_cache_bucket();
    return 0;
}
