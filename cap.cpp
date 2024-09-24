#include <stdio.h>
#include <string.h>
#define MAX_PASSWORD_LENGTH 100
#define HASH_LENGTH 32 
void simple_hash(const char *password, unsigned char *hashed_password) {
    int i;
    unsigned int hash = 0;
    for (i = 0; password[i] != '\0'; i++) {
        hash = hash * 31 + password[i]; 
    }
    for (i = 0; i < HASH_LENGTH; i++) {
        hashed_password[i] = (hash >> (i * 8)) & 0xFF;
    }
}
void print_hex(const unsigned char *hashed_password) {
    for (int i = 0; i < HASH_LENGTH; i++) {
        printf("%02x", hashed_password[i]);
    }
    printf("\n");
}
int main() {
    char password[MAX_PASSWORD_LENGTH];
    unsigned char hashed_password[HASH_LENGTH];
    printf("Enter a password to hash: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = 0;
    simple_hash(password, hashed_password);
    printf("Hashed password: ");
    print_hex(hashed_password);

    return 0;
}

