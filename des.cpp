#include <stdio.h>
#include <string.h>
#include <openssl/des.h>
#include <openssl/rand.h>

void handleErrors() {
    printf("An error occurred.\n");
    exit(1);
}

void encrypt_DES(unsigned char *plaintext, unsigned char *key, unsigned char *ciphertext) {
    DES_cblock keyBlock;
    DES_key_schedule schedule;

    // Copy the key into the DES_cblock structure
    memcpy(keyBlock, key, 8);
    
    // Generate the key schedule
    DES_set_key_unchecked(&keyBlock, &schedule);

    // Encrypt the message
    DES_cblock ivec = {0};  // Initialization vector set to 0
    DES_ncbc_encrypt(plaintext, ciphertext, strlen((const char *)plaintext), &schedule, &ivec, DES_ENCRYPT);
}

void decrypt_DES(unsigned char *ciphertext, unsigned char *key, unsigned char *decryptedText, int ciphertext_len) {
    DES_cblock keyBlock;
    DES_key_schedule schedule;

    // Copy the key into the DES_cblock structure
    memcpy(keyBlock, key, 8);
    
    // Generate the key schedule
    DES_set_key_unchecked(&keyBlock, &schedule);

    // Decrypt the message
    DES_cblock ivec = {0};  // Initialization vector set to 0
    DES_ncbc_encrypt(ciphertext, decryptedText, ciphertext_len, &schedule, &ivec, DES_DECRYPT);
}

int main() {
    // Message to be encrypted
    unsigned char plaintext[64];
    printf("Enter message to encrypt: ");
    fgets((char *)plaintext, sizeof(plaintext), stdin);
    
    // Remove newline character if present
    size_t len = strlen((char *)plaintext);
    if (plaintext[len - 1] == '\n') {
        plaintext[len - 1] = '\0';
    }

    unsigned char key[8];
    if (!RAND_bytes(key, sizeof(key))) {
        handleErrors();
    }

    printf("Generated DES key: ");
    for (int i = 0; i < 8; i++) {
        printf("%02X ", key[i]);
    }
    printf("\n");

    // Encrypt the plaintext
    unsigned char ciphertext[64] = {0};
    encrypt_DES(plaintext, key, ciphertext);
    
    printf("Encrypted message: ");
    for (int i = 0; i < len; i++) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");

    // Decrypt the ciphertext
    unsigned char decryptedText[64] = {0};
    decrypt_DES(ciphertext, key, decryptedText, len);

    printf("Decrypted message: %s\n", decryptedText);

    return 0;
}

