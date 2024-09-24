#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#define SIZE 10
char matrix[SIZE][SIZE];
void remove_duplicates(char *str) {
    int index = 0;
    int len = strlen(str);
    int visited[26] = {0};
    for (int i = 0; i < len; i++) {
        if (!visited[tolower(str[i]) - 'a']) {
            str[index++] = str[i];
            visited[tolower(str[i]) - 'a'] = 1;
        }
    }
    str[index] = '\0';
}
void generate_key_matrix(char key[]) {
    char used[26] = {0};
    int row = 0, col = 0;
    remove_duplicates(key);
    for (int i = 0; key[i] != '\0'; i++) {
        if (key[i] == 'j') continue;
        if (!used[tolower(key[i]) - 'a']) {
            matrix[row][col++] = tolower(key[i]);
            used[tolower(key[i]) - 'a'] = 1;
            if (col == SIZE) {
                col = 0;
                row++;
            }
        }
    }
    for (char ch = 'a'; ch <= 'z'; ch++) {
        if (ch == 'j') continue;
        if (!used[ch - 'a']) {
            matrix[row][col++] = ch;
            used[ch - 'a'] = 1;
            if (col == SIZE) {
                col = 0;
                row++;
            }
        }
    }
}
void search_in_matrix(char ch, int *row, int *col) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}
void encrypt_pair(char *first, char *second) {
    int row1, col1, row2, col2;
    search_in_matrix(*first, &row1, &col1);
    search_in_matrix(*second, &row2, &col2);

    if (row1 == row2) {
        *first = matrix[row1][(col1 + 1) % SIZE];
        *second = matrix[row2][(col2 + 1) % SIZE];
    } else if (col1 == col2) {
        *first = matrix[(row1 + 1) % SIZE][col1];
        *second = matrix[(row2 + 1) % SIZE][col2];
    } else {
        // Form a rectangle and swap corners
        *first = matrix[row1][col2];
        *second = matrix[row2][col1];
    }
}
void decrypt_pair(char *first, char *second) {
    int row1, col1, row2, col2;
    search_in_matrix(*first, &row1, &col1);
    search_in_matrix(*second, &row2, &col2);
    if (row1 == row2) {
        *first = matrix[row1][(col1 - 1 + SIZE) % SIZE];
        *second = matrix[row2][(col2 - 1 + SIZE) % SIZE];
    } else if (col1 == col2) {
        *first = matrix[(row1 - 1 + SIZE) % SIZE][col1];
        *second = matrix[(row2 - 1 + SIZE) % SIZE][col2];
    } else {
        *first = matrix[row1][col2];
        *second = matrix[row2][col1];
    }
}
void preprocess_text(char *plaintext) {
    int len = strlen(plaintext);
    int index = 0;
    for (int i = 0; i < len; i++) {
        if (isalpha(plaintext[i])) {
            plaintext[index++] = tolower(plaintext[i]);
        }
    }
    plaintext[index] = '\0';
}
void encrypt_text(char *plaintext) {
    preprocess_text(plaintext);
    int len = strlen(plaintext);
    for (int i = 0; i < len; i += 2) {
        if (i + 1 == len || plaintext[i] == plaintext[i + 1]) {
            plaintext[i + 1] = 'x';
            len++;
        }
        encrypt_pair(&plaintext[i], &plaintext[i + 1]);
    }
}
void decrypt_text(char *ciphertext) {
    preprocess_text(ciphertext);
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i += 2) {
        decrypt_pair(&ciphertext[i], &ciphertext[i + 1]);
    }
}
int main() {
    char key[30], plaintext[100], ciphertext[100], enc[50], dec[50];
    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';
    generate_key_matrix(key);
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    for (int i = 0; plaintext[i] != '\0'; i++) {
        enc[i] = toupper(plaintext[i]);
    }
    for(int i= 0;ciphertext[i]!= '\0';i++)
    {
    	dec[i]= toupper(ciphertext[i]);
	}
    enc[strcspn(enc, "\n")] = '\0';
    strcpy(ciphertext, enc);
    encrypt_text(ciphertext);
    printf("Encrypted text: %s\n", ciphertext);
    decrypt_text(ciphertext);
    printf("Decrypted text: %s\n", ciphertext);
    return 0;
}

