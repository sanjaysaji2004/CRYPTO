#include <stdio.h>
#include <string.h>

#define SIZE 5

char keyTable[SIZE][SIZE] = {
    {'M', 'F', 'H', 'I', 'K'},
    {'U', 'N', 'O', 'P', 'Q'},
    {'Z', 'V', 'W', 'X', 'Y'},
    {'E', 'L', 'A', 'R', 'G'},
    {'D', 'S', 'T', 'B', 'C'}
};

void encrypt(char keyTable[SIZE][SIZE], char str[], char encrypted[]) {
    int length = strlen(str);
    for (int i = 0; i < length; i += 2) {
        int row1, col1, row2, col2;
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                if (keyTable[j][k] == str[i]) {
                    row1 = j;
                    col1 = k;
                }
                if (keyTable[j][k] == str[i + 1]) {
                    row2 = j;
                    col2 = k;
                }
            }
        }
        if (row1 == row2) {
            encrypted[i] = keyTable[row1][(col1 + 1) % SIZE];
            encrypted[i + 1] = keyTable[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) {
            encrypted[i] = keyTable[(row1 + 1) % SIZE][col1];
            encrypted[i + 1] = keyTable[(row2 + 1) % SIZE][col2];
        } else {
            encrypted[i] = keyTable[row1][col2];
            encrypted[i + 1] = keyTable[row2][col1];
        }
    }
    encrypted[length] = '\0';
}

int main() {
    char message[] = "Must see you over Cadogan West. Coming at once.";
    char prepared[strlen(message) * 2];
    char encrypted[strlen(prepared) + 1];

 
    strcpy(prepared, message);

    encrypt(keyTable, prepared, encrypted);
    printf("Encrypted Message: %s\n", encrypted);

    return 0;
}
