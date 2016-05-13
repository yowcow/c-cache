#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash-node.h"
#include "test-data.h"

const char** all_nodes(HashNode* n, const char* c[]) {
    uint32_t i;

    for (i = 0; n != NULL; i++) {
        Data* d = n->data;
        c[i] = d->name;
        n = n->next;
    }

    return c;
}

const char** all_nodes_reversed(HashNode* n, const char* c[]) {
    uint32_t i;

    for (i = 0; n != NULL; i++) {
        Data* d = n->data;
        c[i] = d->name;
        n = n->prev;
    }

    return c;
}

void test_create_hash_node() {
    printf("Working on %s...", __func__);

    HashNode* n = HashNode_create(Data_create("hogehoge"));

    {
        Data* d1 = n->data;

        assert(strcmp(d1->name, "hogehoge") == 0);
    }

    Data* d = HashNode_destroy(n);
    Data_destroy(d);

    printf("OK\n");
}

void test_append_hash_node() {
    printf("Working on %s...", __func__);

    HashNode* n1 = HashNode_create(Data_create("hoge1"));
    HashNode* n2 = HashNode_create(Data_create("hoge2"));
    HashNode* n3 = HashNode_create(Data_create("hoge3"));

    HashNode_append(n1, n2);
    HashNode_append(n2, n3);

    assert(n1->prev == NULL);

    {
        Data* d1 = n1->next->data;
        Data* d2 = n2->data;

        assert(strcmp(d1->name, d2->name) == 0);
    }
    {
        Data* d1 = n2->prev->data;
        Data* d2 = n1->data;

        assert(strcmp(d1->name, d2->name) == 0);
    }
    {
        Data* d1 = n2->next->data;
        Data* d2 = n3->data;

        assert(strcmp(d1->name, d2->name) == 0);
    }
    {
        Data* d1 = n3->prev->data;
        Data* d2 = n2->data;

        assert(strcmp(d1->name, d2->name) == 0);
    }

    assert(n3->next == NULL);

    Data* d1 = HashNode_destroy(n1);
    Data* d2 = HashNode_destroy(n2);
    Data* d3 = HashNode_destroy(n3);

    Data_destroy(d1);
    Data_destroy(d2);
    Data_destroy(d3);

    printf("OK\n");
}

void test_remove_hash_node() {
    printf("Working on %s...", __func__);

    HashNode* n1 = HashNode_create(Data_create("key1"));
    HashNode* n2 = HashNode_create(Data_create("key2"));
    HashNode* n3 = HashNode_create(Data_create("key3"));
    HashNode* n4 = HashNode_create(Data_create("key4"));

    // Form a list: n1 <-> n2 <-> n3 <-> n4
    HashNode_append(n1, n2);
    HashNode_append(n2, n3);
    HashNode_append(n3, n4);

    // Make it: n1 <-> n3 <-> n4
    Data_destroy(HashNode_remove(n2));

    {
        const char* data[3];
        all_nodes(n1, data);

        assert(strcmp(data[0], "key1") == 0);
        assert(strcmp(data[1], "key3") == 0);
        assert(strcmp(data[2], "key4") == 0);
    }

    {
        const char* data[3];
        all_nodes_reversed(n4, data);

        assert(strcmp(data[0], "key4") == 0);
        assert(strcmp(data[1], "key3") == 0);
        assert(strcmp(data[2], "key1") == 0);
    }

    // Make it: n3 <-> n4
    Data_destroy(HashNode_remove(n1));

    {
        const char* data[2];
        all_nodes(n3, data);

        assert(strcmp(data[0], "key3") == 0);
        assert(strcmp(data[1], "key4") == 0);
    }

    {
        const char* data[2];
        all_nodes_reversed(n4, data);

        assert(strcmp(data[0], "key4") == 0);
        assert(strcmp(data[1], "key3") == 0);
    }

    // Make it: n3
    Data_destroy(HashNode_remove(n4));

    {
        const char* data[1];
        all_nodes(n3, data);

        assert(strcmp(data[0], "key3") == 0);
    }

    {
        const char* data[1];
        all_nodes_reversed(n3, data);

        assert(strcmp(data[0], "key3") == 0);
    }

    Data_destroy(HashNode_remove(n3));

    printf("OK\n");
}

int main() {
    test_create_hash_node();
    test_append_hash_node();
    test_remove_hash_node();
}
