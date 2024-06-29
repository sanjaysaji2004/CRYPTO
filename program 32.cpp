#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    long p, q, g, x, y;
} DSAParams;

void DSA_sign(DSAParams *params, long message, long *r, long *s) {
    long k = rand() % params->q;
    *r = (params->g ^ k % params->p) % params->q;
    *s = (k ^ -1 * (message + params->x * (*r))) % params->q;
}

void DSA_generate_params(DSAParams *params) {
    params->p = 23; 
    params->q = 11; 
    params->g = 5; 
    params->x = rand() % params->q; 
    params->y = (params->g ^ params->x) % params->p; 
}

int main() {
    srand(time(NULL));

    DSAParams params;
    DSA_generate_params(&params);

    long message = 12345;
    long r1, s1, r2, s2;

    DSA_sign(&params, message, &r1, &s1);
    printf("DSA Signature 1: r = %ld, s = %ld\n", r1, s1);

    DSA_sign(&params, message, &r2, &s2);
    printf("DSA Signature 2: r = %ld, s = %ld\n", r2, s2);

    return 0;
}
