  #include <stdio.h>
#include <stdint.h>

#define ROUNDS 16

// Placeholder permutation tables and S-boxes
uint8_t IP[64], FP[64], E[48], P[32], S[8][64], PC1[56], PC2[48], SHIFTS[16];

void permute(uint8_t *in, uint8_t *out, uint8_t *table, int size) {
    for (int i = 0; i < size; i++) out[i] = in[table[i] - 1];
}

void key_schedule(uint8_t *key, uint8_t round_keys[ROUNDS][48]) {
    uint8_t C[28], D[28], CD[56];
    for (int i = 0; i < 28; i++) { C[i] = key[PC1[i] - 1]; D[i] = key[PC1[i + 28] - 1]; }
    for (int round = 0; round < ROUNDS; round++) {
        for (int i = 0; i < SHIFTS[round]; i++) {
            uint8_t tempC = C[0], tempD = D[0];
            for (int j = 0; j < 27; j++) { C[j] = C[j + 1]; D[j] = D[j + 1]; }
            C[27] = tempC; D[27] = tempD;
        }
        for (int i = 0; i < 28; i++) { CD[i] = C[i]; CD[i + 28] = D[i]; }
        for (int i = 0; i < 48; i++) round_keys[round][i] = CD[PC2[i] - 1];
    }
}

void des_round(uint8_t *left, uint8_t *right, uint8_t *round_key) {
    uint8_t expanded[48], substituted[32], permuted[32];
    permute(right, expanded, E, 48);
    for (int i = 0; i < 48; i++) expanded[i] ^= round_key[i];
    for (int i = 0; i < 8; i++) {
        int row = (expanded[i*6] << 1) | expanded[i*6 + 5];
        int col = (expanded[i*6 + 1] << 3) | (expanded[i*6 + 2] << 2) | (expanded[i*6 + 3] << 1) | expanded[i*6 + 4];
        uint8_t val = S[i][row * 16 + col];
        for (int j = 0; j < 4; j++) substituted[i*4 + j] = (val >> (3 - j)) & 1;
    }
    permute(substituted, permuted, P, 32);
    for (int i = 0; i < 32; i++) left[i] ^= permuted[i];
}

void des_decrypt(uint8_t *block, uint8_t *key) {
    uint8_t left[32], right[32], round_keys[ROUNDS][48];
    permute(block, block, IP, 64);
    for (int i = 0; i < 32; i++) { left[i] = block[i]; right[i] = block[i + 32]; }
    key_schedule(key, round_keys);
    for (int round = ROUNDS - 1; round >= 0; round--) {
        des_round(left, right, round_keys[round]);
        if (round > 0) for (int i = 0; i < 32; i++) { uint8_t temp = left[i]; left[i] = right[i]; right[i] = temp; }
    }
    for (int i = 0; i < 32; i++) { block[i] = right[i]; block[i + 32] = left[i]; }
    permute(block, block, FP, 64);
}

int main() {
    uint8_t block[64] = { /* 64-bit block to decrypt */ };
    uint8_t key[64] = { /* 64-bit key */ };
    des_decrypt(block, key);
    for (int i = 0; i < 64; i++) printf("%02x", block[i]);
    printf("\n");
    return 0;
}