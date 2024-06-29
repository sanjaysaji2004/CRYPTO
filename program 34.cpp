#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Example block size (64 bits for demonstration)
#define BLOCK_SIZE 8

void xor_block(uint8_t *out, const uint8_t *a, const uint8_t *b, size_t len) {
    for (size_t i = 0; i < len; i++) {
        out[i] = a[i] ^ b[i];
    }
}

// Padding function (1 bit followed by 0 bits)
void pad(uint8_t *block, size_t len) {
    memset(block + len, 0, BLOCK_SIZE - len);
    block[len] = 0x80;
}

void ecb_encrypt(uint8_t *plaintext, uint8_t *ciphertext, size_t len, uint8_t *key) {
    uint8_t block[BLOCK_SIZE];
    for (size_t i = 0; i < len; i += BLOCK_SIZE) {
        xor_block(block, plaintext + i, key, BLOCK_SIZE); // Simulating block cipher encryption
        memcpy(ciphertext + i, block, BLOCK_SIZE);
    }
}

void cbc_encrypt(uint8_t *plaintext, uint8_t *ciphertext, size_t len, uint8_t *key, uint8_t *iv) {
    uint8_t block[BLOCK_SIZE], prev_block[BLOCK_SIZE];
    memcpy(prev_block, iv, BLOCK_SIZE);
    for (size_t i = 0; i < len; i += BLOCK_SIZE) {
        xor_block(block, plaintext + i, prev_block, BLOCK_SIZE);
        xor_block(block, block, key, BLOCK_SIZE); // Simulating block cipher encryption
        memcpy(ciphertext + i, block, BLOCK_SIZE);
        memcpy(prev_block, block, BLOCK_SIZE);
    }
}

void cfb_encrypt(uint8_t *plaintext, uint8_t *ciphertext, size_t len, uint8_t *key, uint8_t *iv) {
    uint8_t block[BLOCK_SIZE];
    memcpy(block, iv, BLOCK_SIZE);
    for (size_t i = 0; i < len; i += BLOCK_SIZE) {
        xor_block(block, block, key, BLOCK_SIZE); // Simulating block cipher encryption
        xor_block(ciphertext + i, plaintext + i, block, BLOCK_SIZE);
        memcpy(block, ciphertext + i, BLOCK_SIZE);
    }
}

int main() {
    uint8_t key[BLOCK_SIZE] = {0x13, 0x34, 0x57, 0x79, 0x9B, 0xBC, 0xDF, 0xF1};
    uint8_t iv[BLOCK_SIZE] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF};

    uint8_t plaintext[2 * BLOCK_SIZE] = "HELLO DES";
    uint8_t padded_plaintext[2 * BLOCK_SIZE];
    memcpy(padded_plaintext, plaintext, 2 * BLOCK_SIZE);
    pad(padded_plaintext, 9); // Padding the message

    uint8_t ciphertext_ecb[2 * BLOCK_SIZE];
    uint8_t ciphertext_cbc[2 * BLOCK_SIZE];
    uint8_t ciphertext_cfb[2 * BLOCK_SIZE];

    ecb_encrypt(padded_plaintext, ciphertext_ecb, 2 * BLOCK_SIZE, key);
    cbc_encrypt(padded_plaintext, ciphertext_cbc, 2 * BLOCK_SIZE, key, iv);
    cfb_encrypt(padded_plaintext, ciphertext_cfb, 2 * BLOCK_SIZE, key, iv);

    printf("Plaintext:  %s\n", padded_plaintext);
    printf("ECB Ciphertext: ");
    for (size_t i = 0; i < 2 * BLOCK_SIZE; i++) {
        printf("%02X", ciphertext_ecb[i]);
    }
    printf("\n");

    printf("CBC Ciphertext: ");
    for (size_t i = 0; i < 2 * BLOCK_SIZE; i++) {
        printf("%02X", ciphertext_cbc[i]);
    }
    printf("\n");

    printf("CFB Ciphertext: ");
    for (size_t i = 0; i < 2 * BLOCK_SIZE; i++) {
        printf("%02X", ciphertext_cfb[i]);
    }
    printf("\n");

    return 0;
}
