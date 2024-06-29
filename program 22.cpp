#include <stdio.h>
#include <stdint.h>

const int IP[] = { 2, 6, 3, 1, 4, 8, 5, 7 };

const int FP[] = { 4, 1, 3, 5, 7, 2, 8, 6 };

const int EP[] = { 4, 1, 2, 3, 2, 3, 4, 1 };

const int P4[] = { 2, 4, 3, 1 };

const int IP_INV[] = { 4, 1, 3, 5, 7, 2, 8, 6 };

const int S[4][4][4] = {
    { { 1, 0, 3, 2 }, { 3, 2, 1, 0 }, { 0, 2, 1, 3 }, { 3, 1, 3, 2 } },
    { { 0, 1, 2, 3 }, { 2, 0, 1, 3 }, { 3, 0, 1, 0 }, { 2, 1, 0, 3 } },
    { { 1, 0, 3, 2 }, { 0, 3, 2, 1 }, { 3, 2, 1, 0 }, { 2, 1, 0, 3 } },
    { { 3, 1, 0, 2 }, { 0, 2, 1, 3 }, { 1, 3, 2, 0 }, { 2, 0, 3, 1 } }
};

uint8_t permute(uint8_t input, const int *table, int table_size) {
    uint8_t output = 0;
    for (int i = 0; i < table_size; ++i) {
        output <<= 1;
        output |= (input >> (8 - table[i])) & 1;
    }
    return output;
}

uint8_t f_function(uint8_t R, uint8_t K) {
    uint8_t expanded_R = permute(R, EP, 8);
    uint8_t temp = expanded_R ^ K;

    uint8_t left = (temp & 0xF0) >> 4; // left 4 bits
    uint8_t right = temp & 0x0F;       // right 4 bits

    uint8_t row1 = ((left & 0x08) >> 2) | (left & 0x01);
    uint8_t col1 = (left & 0x06) >> 1;

    uint8_t row2 = ((right & 0x08) >> 2) | (right & 0x01);
    uint8_t col2 = (right & 0x06) >> 1;

    uint8_t S_output1 = S[0][row1][col1];
    uint8_t S_output2 = S[1][row2][col2];

    uint8_t S_output = (S_output1 << 2) | S_output2;

    return permute(S_output, P4, 4);
}

uint8_t next_key(uint8_t key) {
    uint8_t shifted = (key << 1) | (key >> 3);
    return shifted & 0x0F;
}

uint8_t encrypt(uint8_t plaintext, uint8_t key, uint8_t *IV) {
    uint8_t cipherblock = *IV ^ plaintext;
    uint8_t L = (cipherblock & 0xF0) >> 4;
    uint8_t R = cipherblock & 0x0F;

    uint8_t f_result = f_function(R, key);
    uint8_t new_R = L ^ f_result;

    *IV = (R << 4) | new_R;

    return *IV;
}

uint8_t decrypt(uint8_t ciphertext, uint8_t key, uint8_t *IV) {
    uint8_t L = (*IV & 0xF0) >> 4;
    uint8_t R = *IV & 0x0F;

    uint8_t f_result = f_function(R, key);
    uint8_t new_R = L ^ f_result;

    uint8_t plaintext = (R << 4) | new_R;
    plaintext ^= ciphertext;

    *IV = (R << 4) | new_R;

    return plaintext;
}

int main() {
    uint8_t plaintext = 0b00000001; 
    uint8_t key = 0b011111101;      
    uint8_t IV = 0b10101010;        

    printf("Plaintext: %d\n", plaintext);

    uint8_t ciphertext = encrypt(plaintext, key, &IV);
    printf("Ciphertext: %d\n", ciphertext);

    uint8_t decrypted_plaintext = decrypt(ciphertext, key, &IV);
    printf("Decrypted Plaintext: %d\n", decrypted_plaintext);

    return 0;
}
