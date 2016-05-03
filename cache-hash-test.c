#include <stdio.h>
#include "cache-hash.h"
#include "cache-node.h"

int main() {
    cache_node_t* n1 = create_cache_node("key1", "value1");
    cache_node_t* n2 = create_cache_node("key2", "value2");

    remove_cache_node(n1);
    remove_cache_node(n2);

    return 0;
}
