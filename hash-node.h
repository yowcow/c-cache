#ifndef HASH_NODE_H_
#define HASH_NODE_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _hash_node {
    void* data;
    struct _hash_node* next;
    struct _hash_node* prev;
} HashNode;

HashNode* HashNode_create(void* data);

void HashNode_append(HashNode* n1, HashNode* n2);

void* HashNode_destroy(HashNode* n);

void* HashNode_remove(HashNode* n);

#ifdef __cplusplus
}
#endif

#endif
