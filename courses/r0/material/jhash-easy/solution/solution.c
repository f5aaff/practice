// gcc solution.c -o solution

#include <stdio.h>

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
/*
    Idea: modify the first byte (c2 has 0x00 instead of 0x01 in c1), and
    use the second byte to "correct" the difference in h cause by the
    different in the first byte.

    Here the first update of h (taking p[0]) will left-shift p[0], so
    the bit in 0x01 will be shifted left to 0x02. There'll thus be a
    difference in h's second bit, corrected by having a second byte 0x02
    instead of 0x00.
*/

    unsigned char c1[] = {0x01, 0x00};
    unsigned char c2[] = {0x00, 0x02};

    unsigned hash1 = jhash(c1, sizeof c1);
    unsigned hash2 = jhash(c2, sizeof c2);

    printf("%08x\n", hash1);
    printf("%08x\n", hash2);

    return 0;
}
