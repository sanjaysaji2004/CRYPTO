#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to calculate the modular inverse of a modulo m using the extended Euclidean algorithm
int mod_inverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0;

    return x1;
}

// Function to encrypt a plaintext letter using affine cipher
char affine_encrypt_char(char p, int a, int b) {
    if (isupper(p)) {
        return (char) (((a * (p - 'A') + b) % 26) + 'A');
    } else if (islower(p)) {
        return (char) (((a * (p - 'a') + b) % 26) + 'a');
    }
    return p;
}

// Function to decrypt a ciphertext letter using affine cipher
char affine_decrypt_char(char c, int a, int b) {
    int a_inv = mod_inverse(a, 26);
    if (isupper(c)) {
        return (char) (((a_inv * (c - 'A' - b + 26)) % 26) + 'A');
    } else if (islower(c)) {
        return (char) (((a_inv * (c - 'a' - b + 26)) % 26) + 'a');
    }
    return c;
}

// Function to encrypt plaintext using affine cipher
void affine_encrypt(char *plaintext, char *ciphertext, int a, int b) {
    size_t length = strlen(plaintext);
    for (size_t i = 0; i < length; i++) {
        ciphertext[i] = affine_encrypt_char(plaintext[i], a, b);
    }
    ciphertext[length] = '\0';
}

// Function to decrypt ciphertext using affine cipher
void affine_decrypt(char *ciphertext, char *plaintext, int a, int b) {
    size_t length = strlen(ciphertext);
    for (size_t i = 0; i < length; i++) {
        plaintext[i] = affine_decrypt_char(ciphertext[i], a, b);
    }
    plaintext[length] = '\0';
}

int main() {
    char plaintext[] = "HelloAffineCipher";
    char ciphertext[100];
    char decryptedtext[100];
    int a = 5; // a must be coprime with 26
    int b = 8;

    // Check if a is coprime with 26
    if (mod_inverse(a, 26) == 0) {
        printf("Error: a is not coprime with 26. Choose a different value for a.\n");
        return 1;
    }

    affine_encrypt(plaintext, ciphertext, a, b);
    affine_decrypt(ciphertext, decryptedtext, a, b);

    printf("Plaintext:  %s\n", plaintext);
    printf("Ciphertext: %s\n", ciphertext);
    printf("Decrypted:  %s\n", decryptedtext);

    return 0;
}
