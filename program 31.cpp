
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define AES_BLOCK_SIZE_128 16
#define AES_BLOCK_SIZE_64  8

const uint8_t R_64  = 0x1B;
const uint8_t R_128 = 0x87;

void print_block(uint8_t *block, int size) {
    for (int i = 0; i < size; i++) {
        printf("%02x ", block[i]);
    }
    printf("\n");
}

void AES_encrypt(uint8_t *plaintext, uint8_t *key, uint8_t *ciphertext) {

    memcpy(ciphertext, plaintext, AES_BLOCK_SIZE_128);
}

void generate_subkeys(uint8_t *key, uint8_t *K1, uint8_t *K2, int block_size) {
    uint8_t L[AES_BLOCK_SIZE_128] = {0};
    uint8_t constant;

    if (block_size == AES_BLOCK_SIZE_64) {
        constant = R_64;
    } else if (block_size == AES_BLOCK_SIZE_128) {
        constant = R_128;
    } else {
        printf("Unsupported block size.\n");
        return;
    }

    uint8_t zero_block[AES_BLOCK_SIZE_128] = {0};
    AES_encrypt(zero_block, key, L);

    printf("L: ");
    print_block(L, block_size);

    int msb = (L[0] & 0x80) != 0;
    for (int i = 0; i < block_size; i++) {
        K1[i] = (L[i] << 1) | (i < block_size - 1 ? (L[i + 1] >> 7) : 0);
    }
    if (msb) {
        K1[block_size - 1] ^= constant;
    }

    printf("K1: ");
    print_block(K1, block_size);

    msb = (K1[0] & 0x80) != 0;
    for (int i = 0; i < block_size; i++) {
        K2[i] = (K1[i] << 1) | (i < block_size - 1 ? (K1[i + 1] >> 7) : 0);
    }
    if (msb) {
        K2[block_size - 1] ^= constant;
    }

    printf("K2: ");
    print_block(K2, block_size);
}

int main() {
    uint8_t key[AES_BLOCK_SIZE_128] = {0}; 
    uint8_t K1[AES_BLOCK_SIZE_128] = {0};
    uint8_t K2[AES_BLOCK_SIZE_128] = {0};

    printf("Generating subkeys for 128-bit block size:\n");
    generate_subkeys(key, K1, K2, AES_BLOCK_SIZE_128);

    return 0;
}
