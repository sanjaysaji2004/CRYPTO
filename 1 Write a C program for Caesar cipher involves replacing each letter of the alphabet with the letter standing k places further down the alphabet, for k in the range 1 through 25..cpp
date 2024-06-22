#include <stdio.h>
#include <string.h>


void encrypt(char *text, int shift) {
    char ch;
    for (int i = 0; text[i] != '\0'; ++i) {
        ch = text[i];
        if (ch >= 'A' && ch <= 'Z') {
            text[i] = (ch - 'A' + shift) % 26 + 'A';
        } else if (ch >= 'a' && ch <= 'z') {
            text[i] = (ch - 'a' + shift) % 26 + 'a';
        }
    }
}

int main() {
    char text[100];
    int shift;
    
   
    printf("Enter a string to encrypt: ");
    fgets(text, sizeof(text), stdin);
    
    
    text[strcspn(text, "\n")] = '\0';
    
    
    printf("Enter the shift value (1-25): ");
    scanf("%d", &shift);
    
    
    encrypt(text, shift);
    
    
    printf("Encrypted string: %s\n", text);
    
    return 0;
}

