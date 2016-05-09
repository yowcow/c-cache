#ifndef PAIR_H_
#define PAIR_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _pair {
    char* key;
    char* val;
} Pair;

Pair* Pair_create(char* key, char* val);

void Pair_update(Pair* p, char* val);

void Pair_destroy(Pair* p);

#ifdef __cplusplus
}
#endif

#endif
