#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to encrypt the plaintext using the substitution cipher key
void encrypt(char plaintext[], char key[], char alphabet[]) {
    char ciphertext[100];
    int i, j;
    int len = strlen(plaintext);

    for (i = 0; i < len; i++) {
        // Ignore non-alphabetic characters
        if (isalpha(plaintext[i])) {
            char ch = tolower(plaintext[i]);
            for (j = 0; j < 26; j++) {
                if (alphabet[j] == ch) {
                    ciphertext[i] = key[j]; // Substitute letter from the key
                    break;
                }
            }
        } else {
            ciphertext[i] = plaintext[i]; // Keep non-alphabetic characters as is
        }
    }
    ciphertext[len] = '\0';
    printf("Encrypted text: %s\n", ciphertext);
}

// Function to decrypt the ciphertext using the substitution cipher key
void decrypt(char ciphertext[], char key[], char alphabet[]) {
    char decryptedtext[100];
    int i, j;
    int len = strlen(ciphertext);

    for (i = 0; i < len; i++) {
        // Ignore non-alphabetic characters
        if (isalpha(ciphertext[i])) {
            char ch = tolower(ciphertext[i]);
            for (j = 0; j < 26; j++) {
                if (key[j] == ch) {
                    decryptedtext[i] = alphabet[j]; // Reverse substitution
                    break;
                }
            }
        } else {
            decryptedtext[i] = ciphertext[i]; // Keep non-alphabetic characters as is
        }
    }
    decryptedtext[len] = '\0';
    printf("Decrypted text: %s\n", decryptedtext);
}

int main() {
    char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    char key[] = "qwertyuiopasdfghjklzxcvbnm"; // Substitution key

    char plaintext[100], ciphertext[100];
    
    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove newline character
    
    printf("Substitution key: %s\n", key);
    
    // Encryption
    encrypt(plaintext, key, alphabet);
    
    // Prompt for the ciphertext input (if manual decryption is needed)
    printf("\nNow enter the ciphertext for decryption: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; // Remove newline character
    
    // Decryption
    decrypt(ciphertext, key, alphabet);

    return 0;
}

