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

// Function to count frequencies of each letter in the text
void count_frequencies(const char *text, float *frequencies) {
    int count[ALPHABET_SIZE] = {0};
    int total = 0;

    for (const char *ptr = text; *ptr != '\0'; ptr++) {
        if (isalpha(*ptr)) {
            count[toupper(*ptr) - 'A']++;
            total++;
        }
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        frequencies[i] = (float)count[i] / total * 100;
    }
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

// Function to calculate fitness score using chi-squared statistic
float calculate_fitness(const float *observed, const float *expected) {
    float fitness = 0.0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        float diff = observed[i] - expected[i];
        fitness += (diff * diff) / expected[i];
    }
    return fitness;
}

int main() {
    char ciphertext[MAX_TEXT_SIZE];
    printf("Enter the ciphertext: ");
    fgets(ciphertext, MAX_TEXT_SIZE, stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';  // Remove newline character

    int top_n = 10;
    printf("Enter the number of top possible plaintexts to output: ");
    scanf("%d", &top_n);

    float ciphertext_frequencies[ALPHABET_SIZE];
    count_frequencies(ciphertext, ciphertext_frequencies);

    // Generate all possible mappings (permutations) of the alphabet
    char key[ALPHABET_SIZE + 1] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    float fitness_scores[ALPHABET_SIZE];

    // Calculate fitness scores for each permutation of the key
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        char plaintext[MAX_TEXT_SIZE];
        decrypt(ciphertext, plaintext, key);

        float plaintext_frequencies[ALPHABET_SIZE];
        count_frequencies(plaintext, plaintext_frequencies);

        fitness_scores[i] = calculate_fitness(plaintext_frequencies, english_frequencies);

        // Rotate key for next permutation
        char temp = key[0];
        memmove(key, key + 1, ALPHABET_SIZE - 1);
        key[ALPHABET_SIZE - 1] = temp;
    }

    // Output the top N results based on fitness score
    printf("\nTop %d possible plaintexts:\n", top_n);
    for (int i = 0; i < top_n && i < ALPHABET_SIZE; i++) {
        printf("%d. Fitness = %.2f\n   Plaintext: %s\n\n", i + 1, fitness_scores[i], ciphertext);
    }

    return 0;
}
