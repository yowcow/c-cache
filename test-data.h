#include <stdlib.h>
#include <string.h>

typedef struct _data {
    const char* name;
} Data;

Data* Data_create(const char* name) {
    Data* d = malloc(sizeof(Data));
    d->name = strdup(name);
    return d;
}

void Data_destroy(Data* d) {
    free((char*) d->name);
    free(d);
}
