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

// Function to compute chi-squared statistic for a given frequency distribution
float chi_squared(const float *observed, const float *expected) {
    float chi_sq = 0.0;

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        float diff = observed[i] - expected[i];
        chi_sq += (diff * diff) / expected[i];
    }

    return chi_sq;
}

// Function to decrypt the ciphertext with a given key
void decrypt(const char *ciphertext, char *plaintext, int key) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            if (isupper(ciphertext[i])) {
                plaintext[i] = ((ciphertext[i] - 'A' - key + ALPHABET_SIZE) % ALPHABET_SIZE) + 'A';
            } else {
                plaintext[i] = ((ciphertext[i] - 'a' - key + ALPHABET_SIZE) % ALPHABET_SIZE) + 'a';
            }
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

// Structure to store possible plaintext and its chi-squared value
typedef struct {
    char plaintext[MAX_TEXT_SIZE];
    float chi_sq;
} PlaintextResult;

// Function to compare two PlaintextResult structures (for qsort)
int compare_results(const void *a, const void *b) {
    float diff = ((PlaintextResult *)a)->chi_sq - ((PlaintextResult *)b)->chi_sq;
    return (diff > 0) - (diff < 0);
}

int main() {
    char ciphertext[MAX_TEXT_SIZE];
    printf("Enter the ciphertext: ");
    fgets(ciphertext, MAX_TEXT_SIZE, stdin);
    ciphertext[strcspn(ciphertext, "\n")] = 0;  // Remove newline character

    int top_n = 10;
    printf("Enter the number of top possible plaintexts to output: ");
    scanf("%d", &top_n);

    PlaintextResult results[ALPHABET_SIZE];
    float ciphertext_frequencies[ALPHABET_SIZE];

    // Try all possible keys (0-25)
    for (int key = 0; key < ALPHABET_SIZE; key++) {
        decrypt(ciphertext, results[key].plaintext, key);
        count_frequencies(results[key].plaintext, ciphertext_frequencies);
        results[key].chi_sq = chi_squared(ciphertext_frequencies, english_frequencies);
    }

    // Sort results based on chi-squared values
    qsort(results, ALPHABET_SIZE, sizeof(PlaintextResult), compare_results);

    // Output the top N results
    for (int i = 0; i < top_n && i < ALPHABET_SIZE; i++) {
        printf("Top %d: Chi-squared = %f\nPlaintext: %s\n\n", i + 1, results[i].chi_sq, results[i].plaintext);
    }

    return 0;
}
 