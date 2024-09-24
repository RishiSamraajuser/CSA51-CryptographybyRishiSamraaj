#include <stdio.h>


int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}

char decryptChar(char cipherChar, int aInv, int b) {
    if (cipherChar >= 'A' && cipherChar <= 'Z') {
        int x = cipherChar - 'A';
        int plainNum = (aInv * (x - b + 26)) % 26; 
        return 'A' + plainNum; 
    }
    return cipherChar; 
}

int main() {

    int a = 15, b = 23; 

    int aInv = modInverse(a, 26);
    if (aInv == -1) {
        printf("No modular inverse for a.\n");
        return -1;
    }

    char ciphertext[] = "B UZOUJ";
    printf("Ciphertext: %s\n", ciphertext);

    printf("Decrypted text: ");
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char decryptedChar = decryptChar(ciphertext[i], aInv, b);
        printf("%c", decryptedChar);
    }
    printf("\n");

    return 0;
}

