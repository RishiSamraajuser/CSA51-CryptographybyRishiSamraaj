#include <stdio.h>
#include <string.h>

// Function to encrypt the text using Rail Fence Cipher
void encryptRailFence(char *plaintext, int key, char *ciphertext) {
    int len = strlen(plaintext);
    int k = 0;

    // Create an empty 2D matrix (rails x length of text)
    char rail[key][len];

    // Initialize the rail matrix with a placeholder (say '*')
    for (int i = 0; i < key; i++)
        for (int j = 0; j < len; j++)
            rail[i][j] = '*';

    // Fill the rail matrix in a zigzag manner
    int row = 0;
    int direction_down = 1; // Initially moving downwards in the matrix

    for (int i = 0; i < len; i++) {
        rail[row][i] = plaintext[i];

        // Reverse the direction when we reach the top or bottom row
        if (row == key - 1)
            direction_down = 0;
        else if (row == 0)
            direction_down = 1;

        if (direction_down)
            row++;
        else
            row--;
    }

    // Read the matrix row by row to get the cipher text
    for (int i = 0; i < key; i++) {
        for (int j = 0; j < len; j++) {
            if (rail[i][j] != '*') {
                ciphertext[k++] = rail[i][j];
            }
        }
    }

    ciphertext[k] = '\0'; // Null-terminate the ciphertext string
}

// Function to decrypt the text using Rail Fence Cipher
void decryptRailFence(char *ciphertext, int key, char *plaintext) {
    int len = strlen(ciphertext);
    int k = 0;

    // Create an empty 2D matrix (rails x length of text)
    char rail[key][len];

    // Initialize the rail matrix with a placeholder (say '*')
    for (int i = 0; i < key; i++)
        for (int j = 0; j < len; j++)
            rail[i][j] = '*';

    // Mark the zigzag positions with placeholder
    int row = 0;
    int direction_down = 1;

    for (int i = 0; i < len; i++) {
        rail[row][i] = '?'; // Mark the places where characters will go

        if (row == key - 1)
            direction_down = 0;
        else if (row == 0)
            direction_down = 1;

        if (direction_down)
            row++;
        else
            row--;
    }

    // Place the ciphertext characters in the marked places
    for (int i = 0; i < key; i++) {
        for (int j = 0; j < len; j++) {
            if (rail[i][j] == '?') {
                rail[i][j] = ciphertext[k++];
            }
        }
    }

    // Read the zigzag pattern to extract the plain text
    row = 0;
    direction_down = 1;

    for (int i = 0; i < len; i++) {
        plaintext[i] = rail[row][i];

        if (row == key - 1)
            direction_down = 0;
        else if (row == 0)
            direction_down = 1;

        if (direction_down)
            row++;
        else
            row--;
    }

    plaintext[len] = '\0'; // Null-terminate the plaintext string
}

int main() {
    char plaintext[100], ciphertext[100], decryptedtext[100];
    int key;

    // Input the plain text and the key (number of rails)
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strlen(plaintext) - 1] = '\0'; // Remove newline character from input

    printf("Enter the number of rails (key): ");
    scanf("%d", &key);

    // Encryption
    encryptRailFence(plaintext, key, ciphertext);
    printf("\nEncrypted Ciphertext: %s\n", ciphertext);

    // Decryption
    decryptRailFence(ciphertext, key, decryptedtext);
    printf("Decrypted Plaintext: %s\n", decryptedtext);

    return 0;
}

