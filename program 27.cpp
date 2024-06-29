#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

unsigned long long encrypt_char(char ch, unsigned long long e, unsigned long long n) {
    int m = ch - 'A'; 
    return mod_exp(m, e, n);
}

int main() {
    unsigned long long e = 65537; 
    unsigned long long n = 3233;  

    char message[] = "HELLO";
    int length = strlen(message);
    
    printf("Original message: %s\n", message);
    printf("Encrypted message: ");
    
    for (int i = 0; i < length; i++) {
        unsigned long long encrypted = encrypt_char(message[i], e, n);
        printf("%llu ", encrypted);
    }
    printf("\n");
    
    return 0;
}
