#include "stdio.h"

unsigned jhash (void *key, int len) {
    unsigned char *p = key;
    unsigned h = 8388617;

    for (int i = 0; i < len; i++)
    {
        h = ( (h << 1 | h >> 30) & 0x7fffffff ) ^ p[i];
    }
    return h;
}

int main() {
    char *key = "jhash";
    printf("%u\n", jhash(key, 5));
}
