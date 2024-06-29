#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned long long mod_exp(unsigned long long base, unsigned long long exp, unsigned long long mod) {
    unsigned long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

int main() {
    unsigned long long q = 23; 
    unsigned long long a = 5;  

    unsigned long long x_A = 6; 
    unsigned long long A = mod_exp(a, x_A, q);

    unsigned long long x_B = 15; 
    unsigned long long B = mod_exp(a, x_B, q);

    printf("Alice sends: %llu\n", A);
    printf("Bob sends: %llu\n", B);

    unsigned long long K_A = mod_exp(B, x_A, q);
    printf("Alice's computed shared key: %llu\n", K_A);

    unsigned long long K_B = mod_exp(A, x_B, q);
    printf("Bob's computed shared key: %llu\n", K_B);

    if (K_A == K_B) {
        printf("Shared key successfully established: %llu\n", K_A);
    } else {
        printf("Error in establishing shared key.\n");
    }

    return 0;
}