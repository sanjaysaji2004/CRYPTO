#include <stdio.h>
#include <string.h>


void encrypt(char *plaintext, char *ciphertextAlphabet) {
    char ch;
    for (int i = 0; plaintext[i] != '\0'; ++i) {
        ch = plaintext[i];
        if (ch >= 'A' && ch <= 'Z') {
            
            ch = ch + 32;
        }
        if (ch >= 'a' && ch <= 'z') {
           
            plaintext[i] = ciphertextAlphabet[ch - 'a'];
        }
    }
}

int main() {
    char plaintext[100];
    char ciphertextAlphabet[27];

   
    printf("Enter a string to encrypt: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; 

    
    printf("Enter the ciphertext alphabet (26 letters): ");
    fgets(ciphertextAlphabet, sizeof(ciphertextAlphabet), stdin);
    ciphertextAlphabet[strcspn(ciphertextAlphabet, "\n")] = '\0'; 

   
    if (strlen(ciphertextAlphabet) != 26) {
        printf("Invalid ciphertext alphabet. It must contain 26 letters.\n");
        return 1;
    }

   
    encrypt(plaintext, ciphertextAlphabet);

    
    printf("Encrypted string: %s\n", plaintext);

    return 0;
}

