#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MATRIX_SIZE 2
#define ALPHABET_SIZE 26

// Function to find the multiplicative inverse of a number modulo 26
int mod_inverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}

// Function to calculate the determinant of a 2x2 matrix
int determinant(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) % ALPHABET_SIZE;
}

// Function to calculate the inverse of a 2x2 matrix modulo 26
void matrix_inverse(int matrix[MATRIX_SIZE][MATRIX_SIZE], int inverse[MATRIX_SIZE][MATRIX_SIZE]) {
    int det = determinant(matrix);
    int inv_det = mod_inverse(det, ALPHABET_SIZE);

    if (inv_det == -1) {
        printf("Matrix is not invertible\n");
        exit(1);
    }

    inverse[0][0] = (matrix[1][1] * inv_det) % ALPHABET_SIZE;
    inverse[0][1] = (-matrix[0][1] * inv_det) % ALPHABET_SIZE;
    inverse[1][0] = (-matrix[1][0] * inv_det) % ALPHABET_SIZE;
    inverse[1][1] = (matrix[0][0] * inv_det) % ALPHABET_SIZE;

    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (inverse[i][j] < 0) {
                inverse[i][j] += ALPHABET_SIZE;
            }
        }
    }
}

// Function to multiply two matrices
void matrix_multiply(int matrix1[MATRIX_SIZE][MATRIX_SIZE], int matrix2[MATRIX_SIZE], int result[MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        result[i] = 0;
        for (int j = 0; j < MATRIX_SIZE; j++) {
            result[i] += matrix1[i][j] * matrix2[j];
        }
        result[i] %= ALPHABET_SIZE;
    }
}

// Function to encrypt a block of plaintext using the Hill cipher
void hill_encrypt(int key[MATRIX_SIZE][MATRIX_SIZE], char *plaintext, char *ciphertext) {
    int block[MATRIX_SIZE];
    for (int i = 0; i < MATRIX_SIZE; i++) {
        block[i] = plaintext[i] - 'A';
    }

    int result[MATRIX_SIZE];
    matrix_multiply(key, block, result);

    for (int i = 0; i < MATRIX_SIZE; i++) {
        ciphertext[i] = result[i] + 'A';
    }
    ciphertext[MATRIX_SIZE] = '\0';
}

// Function to decrypt a block of ciphertext using the Hill cipher
void hill_decrypt(int key[MATRIX_SIZE][MATRIX_SIZE], char *ciphertext, char *plaintext) {
    int inverse_key[MATRIX_SIZE][MATRIX_SIZE];
    matrix_inverse(key, inverse_key);

    int block[MATRIX_SIZE];
    for (int i = 0; i < MATRIX_SIZE; i++) {
        block[i] = ciphertext[i] - 'A';
    }

    int result[MATRIX_SIZE];
    matrix_multiply(inverse_key, block, result);

    for (int i = 0; i < MATRIX_SIZE; i++) {
        plaintext[i] = result[i] + 'A';
    }
    plaintext[MATRIX_SIZE] = '\0';
}

// Function to solve the Hill cipher using a chosen plaintext attack
void solve_hill_cipher(int known_plaintext[MATRIX_SIZE][MATRIX_SIZE], int known_ciphertext[MATRIX_SIZE][MATRIX_SIZE], int key[MATRIX_SIZE][MATRIX_SIZE]) {
    int inverse_plaintext[MATRIX_SIZE][MATRIX_SIZE];
    matrix_inverse(known_plaintext, inverse_plaintext);
    matrix_multiply(inverse_plaintext, known_ciphertext[0], key[0]);
    matrix_multiply(inverse_plaintext, known_ciphertext[1], key[1]);
}

int main() {
    int key[MATRIX_SIZE][MATRIX_SIZE] = {{5, 8}, {17, 3}}; // Example key

    char plaintext[MATRIX_SIZE + 1] = "HI"; // Example plaintext
    char ciphertext[MATRIX_SIZE + 1];

    hill_encrypt(key, plaintext, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    char decryptedtext[MATRIX_SIZE + 1];
    hill_decrypt(key, ciphertext, decryptedtext);
    printf("Decrypted: %s\n", decryptedtext);

    // Known plaintext-ciphertext pairs for chosen plaintext attack
    int known_plaintext[MATRIX_SIZE][MATRIX_SIZE] = {{7, 8}, {8, 9}}; // 'HI' and 'IJ'
    int known_ciphertext[MATRIX_SIZE][MATRIX_SIZE] = {{4, 3}, {3, 12}}; // Corresponding ciphertexts

    int recovered_key[MATRIX_SIZE][MATRIX_SIZE];
    solve_hill_cipher(known_plaintext, known_ciphertext, recovered_key);

    printf("Recovered Key:\n");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%d ", recovered_key[i][j]);
        }
        printf("\n");
    }

    return 0;
}
