#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5


void generateKeyTable(char key[], char keyTable[SIZE][SIZE]);
void preprocessText(char str[], char processed[]);
void encryptPair(char keyTable[SIZE][SIZE], char a, char b, char *x, char *y);
void playfairEncrypt(char key[], char plaintext[], char ciphertext[]);

int main() {
    char key[100];
    char plaintext[100];
    char ciphertext[100];

  
    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; 

    
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; 

   
    playfairEncrypt(key, plaintext, ciphertext);

    
    printf("Encrypted text: %s\n", ciphertext);

    return 0;
}


void generateKeyTable(char key[], char keyTable[SIZE][SIZE]) {
    int map[26] = {0};
    int i, j, k;
    int keylen = strlen(key);

    
    for (i = 0; i < keylen; i++) {
        if (key[i] == 'j') key[i] = 'i'; 
        key[i] = tolower(key[i]);
        if (!map[key[i] - 'a'] && isalpha(key[i])) {
            map[key[i] - 'a'] = 1;
        }
    }

    
    i = 0; j = 0;
    for (k = 0; k < keylen; k++) {
        if (map[key[k] - 'a']) {
            keyTable[i][j++] = key[k];
            map[key[k] - 'a'] = 0;
            if (j == SIZE) {
                j = 0; i++;
            }
        }
    }

    
    for (k = 0; k < 26; k++) {
        if (k + 'a' == 'j') continue; // Skip 'j'
        if (!map[k]) {
            keyTable[i][j++] = k + 'a';
            if (j == SIZE) {
                j = 0; i++;
            }
        }
    }
}


void preprocessText(char str[], char processed[]) {
    int len = strlen(str);
    int i, j = 0;

    for (i = 0; i < len; i++) {
        if (isalpha(str[i])) {
            processed[j++] = tolower(str[i]);
        }
    }
    processed[j] = '\0';

    
    len = strlen(processed);
    for (i = 0; i < len; i += 2) {
        if (processed[i] == processed[i + 1]) {
            memmove(processed + i + 2, processed + i + 1, len - i);
            processed[i + 1] = 'x';
            len++;
        }
    }

    if (len % 2 != 0) {
        processed[len++] = 'x';
        processed[len] = '\0';
    }
}


void encryptPair(char keyTable[SIZE][SIZE], char a, char b, char *x, char *y) {
    int row1, col1, row2, col2;
    int i, j;


    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (keyTable[i][j] == a) {
                row1 = i;
                col1 = j;
            } else if (keyTable[i][j] == b) {
                row2 = i;
                col2 = j;
            }
        }
    }

    
    if (row1 == row2) {
        *x = keyTable[row1][(col1 + 1) % SIZE];
        *y = keyTable[row2][(col2 + 1) % SIZE];
    } else if (col1 == col2) {
        *x = keyTable[(row1 + 1) % SIZE][col1];
        *y = keyTable[(row2 + 1) % SIZE][col2];
    } else {
        *x = keyTable[row1][col2];
        *y = keyTable[row2][col1];
    }
}


void playfairEncrypt(char key[], char plaintext[], char ciphertext[]) {
    char keyTable[SIZE][SIZE];
    char processedText[200];
    int len, i, j;

   
    generateKeyTable(key, keyTable);

    
    preprocessText(plaintext, processedText);
    len = strlen(processedText);

    
    for (i = 0, j = 0; i < len; i += 2, j += 2) {
        encryptPair(keyTable, processedText[i], processedText[i + 1], &ciphertext[j], &ciphertext[j + 1]);
    }
    ciphertext[j] = '\0';
}

