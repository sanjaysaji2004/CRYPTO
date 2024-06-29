
#include <stdio.h>

int extended_gcd(int a, int b, int *x, int *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }

    int x1, y1;
    int gcd = extended_gcd(b % a, a, &x1, &y1);

    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcd;
}

int mod_inverse(int e, int phi) {
    int x, y;
    int gcd = extended_gcd(e, phi, &x, &y);

    if (gcd != 1) {
        return -1;
    } else {
        return (x % phi + phi) % phi;
    }
}

int main() {
    int e = 31;
    int n = 3599;

    int p = 59;
    int q = 61;

    int phi = (p - 1) * (q - 1); 

    int d = mod_inverse(e, phi);

    if (d == -1) {
        printf("Multiplicative inverse does not exist.\n");
    } else {
        printf("Public Key (e, n): (%d, %d)\n", e, n);
        printf("Private Key (d, n): (%d, %d)\n", d, n);
    }

    return 0;
}
