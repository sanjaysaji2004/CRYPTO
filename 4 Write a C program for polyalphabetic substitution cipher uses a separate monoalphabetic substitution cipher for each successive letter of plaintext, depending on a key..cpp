#include <stdio.h>
#include <string.h>
#include <ctype.h>


void polyalphabeticEncrypt(char *plaintext, char *key, char *ciphertext) {
    int keylen = strlen(key);
    int textlen = strlen(plaintext);
    int i, j = 0;

    for (i = 0; i < textlen; ++i) {
        char ch = plaintext[i];
        char k = key[j % keylen];
        int shift = tolower(k) - 'a';

        if (isalpha(ch)) {
            char base = islower(ch) ? 'a' : 'A';
            ciphertext[i] = (ch - base + shift) % 26 + base;
            j++;
        } else {
            ciphertext[i] = ch; 
        }
    }
    ciphertext[i] = '\0';
}

int main() {
    char plaintext[100];
    char key[100];
    char ciphertext[100];

    
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; 

    
    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; 

    
    polyalphabeticEncrypt(plaintext, key, ciphertext);

    
    printf("Encrypted text: %s\n", ciphertext);

    return 0;
}

