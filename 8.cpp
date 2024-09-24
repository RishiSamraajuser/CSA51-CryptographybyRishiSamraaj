#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

void createMatrix(char *key, char matrix[SIZE][SIZE]) {
    int used[26] = {0}; // Track used letters
    int k = 0;
    
    // Add keyword letters to matrix
    for (int i = 0; key[i]; i++) {
        char c = toupper(key[i]);
        if (c >= 'A' && c <= 'Z' && !used[c - 'A']) {
            if (c == 'J') c = 'I'; // Treat I and J as the same
            used[c - 'A'] = 1;
            matrix[k / SIZE][k % SIZE] = c;
            k++;
        }
    }
    
    // Add remaining letters
    for (char c = 'A'; c <= 'Z'; c++) {
        if (!used[c - 'A'] && c != 'J') { // Exclude J
            matrix[k / SIZE][k % SIZE] = c;
            k++;
        }
    }
}

void decryptDigraph(char a, char b, char matrix[SIZE][SIZE], char *dec1, char *dec2) {
    int row1, col1, row2, col2;
    
    // Find positions of a and b
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == a) {
                row1 = i; col1 = j;
            }
            if (matrix[i][j] == b) {
                row2 = i; col2 = j;
            }
        }
    }

    // Decrypt based on their positions
    if (row1 == row2) { // Same row
        dec1[0] = matrix[row1][(col1 + SIZE - 1) % SIZE];
        dec2[0] = matrix[row2][(col2 + SIZE - 1) % SIZE];
    } else if (col1 == col2) { // Same column
        dec1[0] = matrix[(row1 + SIZE - 1) % SIZE][col1];
        dec2[0] = matrix[(row2 + SIZE - 1) % SIZE][col2];
    } else { // Rectangle
        dec1[0] = matrix[row1][col2];
        dec2[0] = matrix[row2][col1];
    }
}

void decrypt(char *ciphertext, char *key, char *plaintext) {
    char matrix[SIZE][SIZE];
    createMatrix(key, matrix);

    int len = strlen(ciphertext);
    int k = 0;
    
    for (int i = 0; i < len; i += 2) {
        char a = ciphertext[i];
        char b = (i + 1 < len) ? ciphertext[i + 1] : 'X'; // Padding with 'X'
        
        char dec1[2] = {0}, dec2[2] = {0};
        decryptDigraph(a, b, matrix, dec1, dec2);
        
        plaintext[k++] = dec1[0];
        plaintext[k++] = dec2[0];
    }
    plaintext[k] = '\0'; // Null-terminate the string
}

int main() {
    char key[100];
    char ciphertext[100];
    char plaintext[100];

    // Input the keyword
    printf("Enter the keyword: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = 0; // Remove newline character

    // Input the ciphertext
    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = 0; // Remove newline character

    // Decrypt the message
    decrypt(ciphertext, key, plaintext);
    
    // Output the decrypted plaintext
    printf("Decrypted Message: %s\n", plaintext);
    
    return 0;
}

