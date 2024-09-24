#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BLOCK_SIZE 8

// Example S-box (simplified version)
const int S_BOX[4][16] = {
    {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
    {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
    {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
    {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
};

// Function to perform a simple substitution using the S-box
unsigned char substitute(unsigned char input) {
    int row = (input & 0xC0) >> 6;  // First 2 bits
    int col = input & 0x3F;         // Last 6 bits
    return S_BOX[row][col];
}

// Function to XOR two blocks of text
void xor_blocks(unsigned char *block1, unsigned char *block2, unsigned char *result) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        result[i] = block1[i] ^ block2[i];
    }
}

// Simplified encryption function (Feistel Structure)
void encrypt_block(unsigned char *plaintext, unsigned char *key, unsigned char *ciphertext) {
    unsigned char left[BLOCK_SIZE / 2], right[BLOCK_SIZE / 2], new_right[BLOCK_SIZE / 2];
    
    // Split into left and right halves
    memcpy(left, plaintext, BLOCK_SIZE / 2);
    memcpy(right, plaintext + BLOCK_SIZE / 2, BLOCK_SIZE / 2);
    
    // Example: simple round of XOR and substitution
    xor_blocks(right, key, new_right); // Right half XOR key
    for (int i = 0; i < BLOCK_SIZE / 2; i++) {
        new_right[i] = substitute(new_right[i]);  // Apply substitution using S-box
    }
    
    // XOR with left half and swap
    xor_blocks(left, new_right, ciphertext + BLOCK_SIZE / 2); // Right half becomes new left
    memcpy(ciphertext, right, BLOCK_SIZE / 2);  // Left becomes new right
}

// Simplified decryption function (inverse Feistel)
void decrypt_block(unsigned char *ciphertext, unsigned char *key, unsigned char *plaintext) {
    unsigned char left[BLOCK_SIZE / 2], right[BLOCK_SIZE / 2], new_left[BLOCK_SIZE / 2];
    
    // Split into left and right halves
    memcpy(right, ciphertext, BLOCK_SIZE / 2);
    memcpy(left, ciphertext + BLOCK_SIZE / 2, BLOCK_SIZE / 2);
    
    // Reverse the encryption process
    xor_blocks(left, key, new_left);  // Left half XOR key
    for (int i = 0; i < BLOCK_SIZE / 2; i++) {
        new_left[i] = substitute(new_left[i]);  // Apply substitution using S-box
    }
    
    // XOR with right half and swap
    xor_blocks(right, new_left, plaintext + BLOCK_SIZE / 2); // Left half becomes new right
    memcpy(plaintext, left, BLOCK_SIZE / 2);  // Right becomes new left
}

int main() {
    unsigned char plaintext[BLOCK_SIZE], ciphertext[BLOCK_SIZE], decryptedtext[BLOCK_SIZE];
    unsigned char key[BLOCK_SIZE];

    // Input plain text
    printf("Enter a 8-character plaintext: ");
    fgets((char *)plaintext, BLOCK_SIZE + 1, stdin);

    // Input key (8 characters)
    printf("Enter a 8-character key: ");
    fgets((char *)key, BLOCK_SIZE + 1, stdin);

    // Encryption
    encrypt_block(plaintext, key, ciphertext);
    printf("Encrypted Ciphertext: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");

    // Decryption
    decrypt_block(ciphertext, key, decryptedtext);
    printf("Decrypted Plaintext: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%c", decryptedtext[i]);
    }
    printf("\n");

    return 0;
}

