#include <stdio.h>
#include <stdint.h>
#include <string.h>
int initial_permutation[64] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};
int final_permutation[64] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25
};
uint64_t generate_key(int round) {
    uint64_t key = 0x133457799BBCDFF1;
    return key;
}
uint32_t des_round(uint32_t half_block, uint64_t round_key) {
    // Simplified round function
    return half_block ^ round_key;
}

// DES encryption function
uint64_t des_encrypt(uint64_t plaintext, uint64_t key) {
    // Initial permutation
    uint64_t permuted_block = 0;
    for (int i = 0; i < 64; i++) {
        permuted_block <<= 1;
        permuted_block |= (plaintext >> (64 - initial_permutation[i])) & 0x01;
    }

    // Split block into two halves
    uint32_t left_half = (permuted_block >> 32) & 0xFFFFFFFF;
    uint32_t right_half = permuted_block & 0xFFFFFFFF;

    // 16 rounds of DES
    for (int round = 0; round < 16; round++) {
        uint64_t round_key = generate_key(round);
        uint32_t new_right_half = des_round(right_half, round_key);
        uint32_t temp = right_half;
        right_half = left_half ^ new_right_half;
        left_half = temp;
    }

    // Combine halves
    uint64_t combined_block = ((uint64_t)right_half << 32) | left_half;

    // Final permutation
    uint64_t ciphertext = 0;
    for (int i = 0; i < 64; i++) {
        ciphertext <<= 1;
        ciphertext |= (combined_block >> (64 - final_permutation[i])) & 0x01;
    }

    return ciphertext;
}

int main() {
    uint64_t plaintext = 0x0123456789ABCDEF;
    uint64_t key = 0x133457799BBCDFF1;

    uint64_t ciphertext = des_encrypt(plaintext, key);

    printf("Plaintext:  0x%016llX\n", plaintext);
    printf("Ciphertext: 0x%016llX\n", ciphertext);

    return 0;
}
