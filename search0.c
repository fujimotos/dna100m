#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

#define MAX(a,b) ((a) < (b) ? (b) : (a))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

int wagner_fischer(char *s1, int len1, char *s2, int len2)
{
    int i, j, m, M;
    int Mx, mx, dia, top, left;
    int buf[32];
    char *p1;

    if (len1 < len2)
        return wagner_fischer(s2, len2, s1, len1);
    if (len2 == 0)
        return len1;
    if (len2 == 1)
        return len1 - (memchr(s1, s2[0], len1) != NULL);
    if (len2 == 2) {
        p1 = memchr(s1, s2[0], len1 - 1);
        if (p1) {
            return len1 - (index(p1+1, s2[1]) != NULL) - 1;
        } else {
            return len1 - (index(s1+1, s2[1]) != NULL);
        }
    }

    Mx = (len2 - 1) / 2;
    mx = 1 - Mx - (len1 - len2);

    for (j = 0; j <= Mx; j++)
        buf[j] = j;

    for (i = 1; i <= len1; i++) {
        buf[0] = i - 1;

        m = mx > 1 ? mx : 1;
        M = Mx > len2 ? len2 : Mx;
        mx++;
        Mx++;

        dia = buf[m - 1];
        top = buf[m];

        if (s1[i - 1] != s2[m - 1])
            dia = (dia < top ? dia : top) + 1;

        buf[m] = dia;
        left = dia;
        dia = top;

        for (j = m + 1; j <= M; j++) {
            top = buf[j];

            if (s1[i - 1] != s2[j - 1])
                dia = MIN(MIN(dia, top), left) + 1;
            buf[j] = dia;
            left = dia;
            dia = top;
        }

        if (len2 == M)
            continue;

        if (s1[i - 1] != s2[M])
            dia = MIN(dia, left) + 1;
        buf[M + 1] = dia;
    }
    dia = buf[len2];
    return dia;
}

#define MAXDIST 8
#define LENGTH 20
#define QUERY "AACTGGCAGTGAAACCATAG"

int main(int argc, char **argv)
{
    int dist;
    char buf[LENGTH + 1];

    for (;;) {
        if (fread(buf, LENGTH + 1, 1, stdin) < 1) {
            if (feof(stdin)) {
                break;
            }
        }
        dist = wagner_fischer(buf, LENGTH, QUERY, LENGTH);
        if (dist <= MAXDIST) {
            printf("%i %.*s\n", dist, LENGTH, buf);
        }
    }
}
