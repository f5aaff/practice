#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define WORDLEN 12

// generate a random word of WORDLEN characters
int main() {

    unsigned seed;
    unsigned char seedbytes[4];
    char word[WORDLEN+1];
    word[WORDLEN]='\0';

    int fd = open("/dev/urandom", O_RDONLY);
    read(fd, seedbytes, 4);

    seed |= seedbytes[0];
    seed |= seedbytes[1] << 8;
    seed |= seedbytes[2] << 16;
    seed |= seedbytes[3] << 24;

    srandom(seed);

    int i = 0;

    while (i < WORDLEN) {
        unsigned char c = random();
        if (c <= 234) {
            word[i] = (c % 26)+65;
            i++;
        }
    }
    printf("%s\n", word);

    memset(word, WORDLEN, 0);

    return 0;
}
