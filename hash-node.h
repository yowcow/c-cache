#ifndef HASH_NODE_H_
#define HASH_NODE_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _hash_node {
    char* key;
    char* val;
    struct _hash_node* next;
    struct _hash_node* prev;
} HashNode;

HashNode* HashNode_create(char* key, char* val);

void HashNode_append(HashNode* n1, HashNode* n2);

void HashNode_update(HashNode* n, char* val);

void HashNode_destroy(HashNode* n);

void HashNode_remove(HashNode* n);

// For testing purpose...
void HashNode_get_keys(HashNode* n, char** keys);

// For testing purpose...
void HashNode_get_keys_reverse(HashNode* n, char** keys);

#ifdef __cplusplus
}
#endif

#endif
