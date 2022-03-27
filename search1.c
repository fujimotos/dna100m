#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

int32_t myers1999(uint8_t *s1, int32_t len1, uint8_t *s2, int32_t len2)
{
    uint32_t Eq, Xv, Xh, Ph, Mh, Pv, Mv, Last;
    int32_t i;
    int32_t Score = len2;
    uint32_t Peq[256] = {0};

    for (i = 0; i < len2; i++)
        Peq[s2[i]] |= (uint32_t) 1 << i;

    Mv = 0;
    Pv = (uint32_t) -1;
    Last = (uint32_t) 1 << (len2 - 1);

    for (i = 0; i < len1; i++) {
        Eq = Peq[s1[i]];

        Xv = Eq | Mv;
        Xh = (((Eq & Pv) + Pv) ^ Pv) | Eq;

        Ph = Mv | ~ (Xh | Pv);
        Mh = Pv & Xh;

        if (Ph & Last) Score++;
        if (Mh & Last) Score--;

        Ph = (Ph << 1) | 1;
        Mh = (Mh << 1);

        Pv = Mh | ~ (Xv | Ph);
        Mv = Ph & Xv;
    }
    return Score;
}

#define MAXDIST 8
#define LENGTH 20
#define QUERY "AACTGGCAGTGAAACCATAG"

int main(int argc, char **argv)
{
    int dist;
    uint8_t buf[LENGTH + 1];
    uint8_t query[] = QUERY;

    for (;;) {
        if (fread(buf, LENGTH + 1, 1, stdin) < 1) {
            if (feof(stdin)) {
                break;
            }
        }
        dist = myers1999(buf, LENGTH, query, LENGTH);
        if (dist <= MAXDIST) {
            printf("%i %.*s\n", dist, LENGTH, buf);
        }
    }
}
