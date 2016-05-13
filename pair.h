#ifndef PAIR_H_
#define PAIR_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _pair {
    char* key;
    char* val;
    void (*destroy)(struct _pair* p);
    void (*update)(struct _pair* p, const char* val);
} Pair;

Pair* Pair_create(const char* key, const char* val);

void Pair_update(Pair* p, const char* val);

void Pair_destroy(Pair* p);

#ifdef __cplusplus
}
#endif

#endif
