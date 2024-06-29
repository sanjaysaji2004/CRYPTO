#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define MAX_TEXT_SIZE 1024

// English letter frequencies (in percentage)
const float english_frequencies[ALPHABET_SIZE] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153, 
    0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056, 
    2.758, 0.978, 2.360, 0.150, 1.974, 0.074
};

// Function to count frequencies of each letter in the ciphertext
void count_frequencies(const char *text, float *frequencies) {
    int count[ALPHABET_SIZE] = {0};
    int total = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            count[toupper(text[i]) - 'A']++;
            total++;
        }
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        frequencies[i] = (float)count[i] / total * 100;
    }
}

// Function to map frequencies and generate key
void generate_key(const float *ciphertext_frequencies, char *key) {
    int sorted_indices[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        sorted_indices[i] = i;
    }

    // Sort indices based on ciphertext frequencies
    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (ciphertext_frequencies[sorted_indices[i]] < ciphertext_frequencies[sorted_indices[j]]) {
                int temp = sorted_indices[i];
                sorted_indices[i] = sorted_indices[j];
                sorted_indices[j] = temp;
            }
        }
    }

    // Generate key by mapping most frequent letters
    const char *english_order = "ETAOINSHRDLCUMWFGYPBVKJXQZ";
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        key[sorted_indices[i]] = english_order[i];
    }
    key[ALPHABET_SIZE] = '\0';
}

// Function to decrypt the ciphertext with a given key
void decrypt(const char *ciphertext, char *plaintext, const char *key) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            if (isupper(ciphertext[i])) {
                plaintext[i] = key[ciphertext[i] - 'A'];
            } else {
                plaintext[i] = tolower(key[ciphertext[i] - 'a']);
            }
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

int main() {
    char ciphertext[MAX_TEXT_SIZE];
    printf("Enter the ciphertext: ");
    fgets(ciphertext, MAX_TEXT_SIZE, stdin);
    ciphertext[strcspn(ciphertext, "\n")] = 0;  // Remove newline character

    int top_n = 10;
    float ciphertext_frequencies[ALPHABET_SIZE];
    count_frequencies(ciphertext, ciphertext_frequencies);

    char key[ALPHABET_SIZE + 1];
    generate_key(ciphertext_frequencies, key);

    printf("Generated Key: %s\n", key);

    char plaintext[MAX_TEXT_SIZE];
    decrypt(ciphertext, plaintext, key);

    printf("Decrypted Text: %s\n", plaintext);

    return 0;
}
