#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

void createCipherMap(char *cipher, char *map) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        map[i] = cipher[i];
    }
}

char encryptChar(char ch, char *map) {
    if (isalpha(ch)) {
        char base = islower(ch) ? 'a' : 'A';
        return map[tolower(ch) - 'a'] + (isupper(ch) ? 'A' - 'a' : 0);
    }
    return ch; 
}

void encryptMessage(const char *message, char *cipher, char *encrypted) {
    char map[ALPHABET_SIZE];
    createCipherMap(cipher, map);
    
    for (int i = 0; message[i] != '\0'; i++) {
        encrypted[i] = encryptChar(message[i], map);
    }
    encrypted[strlen(message)] = '\0'; 
}

int main() {
    char cipher[ALPHABET_SIZE + 1];
    char message[256];
    char encrypted[256];

    strcpy(cipher, "qwertyuiopasdfghjklzxcvbnm"); 

    printf("Enter your message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = 0; 
    encryptMessage(message, cipher, encrypted);
    
    printf("Encrypted message: %s\n", encrypted);
    
    return 0;
}
