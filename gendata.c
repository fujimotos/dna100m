#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

void randombytes(uint8_t *buf, int32_t len)
{
    int32_t i;
    for (i = 0; i < len; i++) {
        buf[i] = (uint8_t) (rand() & 0xff);
    }
}

char *randomdna20(void)
{
    static char dna[21];
    char nubase[4] = "ACGT";
    uint8_t buf[5];
    int i;

    randombytes(buf, 5);
    for (i = 0; i < 5; i++) {
        dna[i * 4] = nubase[buf[i] & 0x03];
        dna[i * 4 + 1] = nubase[(buf[i] >> 2) & 0x03];
        dna[i * 4 + 2] = nubase[(buf[i] >> 4) & 0x03];
        dna[i * 4 + 3] = nubase[(buf[i] >> 6) & 0x03];
    }
    dna[20] = '\0';
    return dna;
}

int main(int argc, char **argv)
{
    srand(time(NULL));
    while (1) {
        if (puts(randomdna20()) == EOF) {
            break;
        }
    }
}
