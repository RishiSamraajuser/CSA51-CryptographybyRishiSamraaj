#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
void encrypt(char plaintext[], char key[], char ciphertext[]) {
    int i, j = 0;
    int textLen = strlen(plaintext);
    int keyLen = strlen(key);

    for (i = 0; i < textLen; i++) {
        if (isalpha(plaintext[i])) { 
            char offset = isupper(plaintext[i]) ? 'A' : 'a';
            ciphertext[i] = ((plaintext[i] - offset) + (tolower(key[j % keyLen]) - 'a')) % 26 + offset;
            j++;
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[textLen] = '\0';
}
void decrypt(char ciphertext[], char key[], char decryptedtext[]) {
    int i, j = 0;
    int textLen = strlen(ciphertext);
    int keyLen = strlen(key);

    for (i = 0; i < textLen; i++) {
        if (isalpha(ciphertext[i])) {
            char offset = isupper(ciphertext[i]) ? 'A' : 'a';
            decryptedtext[i] = ((ciphertext[i] - offset) - (tolower(key[j % keyLen]) - 'a') + 26) % 26 + offset;
            j++;
        } else {
            decryptedtext[i] = ciphertext[i];
        }
    }
    decryptedtext[textLen] = '\0';
}
int main() {
    char plaintext[100], key[100], ciphertext[100], decryptedtext[100];
    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';
    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';
    encrypt(plaintext, key, ciphertext);
    printf("Encrypted text: %s\n", ciphertext);
    decrypt(ciphertext, key, decryptedtext);
    printf("Decrypted text: %s\n", decryptedtext);
    return 0;
}

