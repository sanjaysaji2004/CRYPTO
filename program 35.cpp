#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ALPHABET_SIZE 26

// Function to generate a random key
void generate_key(int *key, size_t length) {
    for (size_t i = 0; i < length; i++) {
        key[i] = rand() % ALPHABET_SIZE;
    }
}

// Function to encrypt plaintext using the key
void encrypt(const char *plaintext, char *ciphertext, int *key, size_t length) {
    for (size_t i = 0; i < length; i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            ciphertext[i] = 'A' + (plaintext[i] - 'A' + key[i]) % ALPHABET_SIZE;
        } else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            ciphertext[i] = 'a' + (plaintext[i] - 'a' + key[i]) % ALPHABET_SIZE;
        } else {
            ciphertext[i] = plaintext[i]; // Non-alphabetic characters are not encrypted
        }
    }
    ciphertext[length] = '\0'; // Null-terminate the ciphertext
}

// Function to decrypt ciphertext using the key
void decrypt(const char *ciphertext, char *plaintext, int *key, size_t length) {
    for (size_t i = 0; i < length; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            plaintext[i] = 'A' + (ciphertext[i] - 'A' - key[i] + ALPHABET_SIZE) % ALPHABET_SIZE;
        } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            plaintext[i] = 'a' + (ciphertext[i] - 'a' - key[i] + ALPHABET_SIZE) % ALPHABET_SIZE;
        } else {
            plaintext[i] = ciphertext[i]; // Non-alphabetic characters are not decrypted
        }
    }
    plaintext[length] = '\0'; // Null-terminate the plaintext
}

int main() {
    srand((unsigned int) time(NULL));

    char plaintext[] = "HELLO VIGENERE CIPHER";
    size_t length = strlen(plaintext);

    int key[length];
    generate_key(key, length);

    char ciphertext[length + 1];
    encrypt(plaintext, ciphertext, key, length);

    char decrypted_text[length + 1];
    decrypt(ciphertext, decrypted_text, key, length);

    printf("Plaintext:  %s\n", plaintext);
    printf("Ciphertext: %s\n", ciphertext);
    printf("Decrypted:  %s\n", decrypted_text);

    printf("Key: ");
    for (size_t i = 0; i < length; i++) {
        printf("%d ", key[i]);
    }
    printf("\n");

    return 0;
}
