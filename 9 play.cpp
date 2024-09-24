#include <stdio.h>
#include <string.h>
#include <ctype.h>

char matrix[5][5] = {
    {'M', 'F', 'H', 'I', 'K'},
    {'U', 'N', 'O', 'P', 'Q'},
    {'Z', 'V', 'W', 'X', 'Y'},
    {'E', 'L', 'A', 'R', 'G'},
    {'D', 'S', 'T', 'B', 'C'}
};

void preprocessMessage(char *message) {
    int len = strlen(message);
    int j = 0;
    for (int i = 0; i < len; i++) {
        if (isalpha(message[i])) {
            message[j++] = toupper(message[i]);
        }
    }
    message[j] = '\0';
}

void findPosition(char letter, int *row, int *col) {
    if (letter == 'J') letter = 'I';  
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == letter) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to encrypt using the Playfair cipher
void encryptMessage(char *message) {
    int len = strlen(message);
    
    // If the message length is odd, append 'X' at the end
    if (len % 2 != 0) {
        message[len++] = 'X';
        message[len] = '\0';
    }

    for (int i = 0; i < len; i += 2) {
        char letter1 = message[i];
        char letter2 = message[i + 1];
        
        int row1, col1, row2, col2;
        findPosition(letter1, &row1, &col1);
        findPosition(letter2, &row2, &col2);

        // Case 1: Same row
        if (row1 == row2) {
            message[i] = matrix[row1][(col1 + 1) % 5];
            message[i + 1] = matrix[row2][(col2 + 1) % 5];
        }
        // Case 2: Same column
        else if (col1 == col2) {
            message[i] = matrix[(row1 + 1) % 5][col1];
            message[i + 1] = matrix[(row2 + 1) % 5][col2];
        }
        // Case 3: Rectangle case
        else {
            message[i] = matrix[row1][col2];
            message[i + 1] = matrix[row2][col1];
        }
    }
}

int main() {
    char message[] = "Must see you over Cadogan West. Coming at once.";

    // Preprocess the message
    preprocessMessage(message);
    printf("Processed message: %s\n", message);

    // Encrypt the message using Playfair cipher
    encryptMessage(message);

    // Output the encrypted message
    printf("Encrypted message: %s\n", message);

    return 0;
}

