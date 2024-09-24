#include <stdio.h>
#include <string.h>
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
int mod_inverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; 
}
void encryptMessage(const char *msg, int a, int b, char *cipher) {
    int i;
    for (i = 0; msg[i] != '\0'; i++) {

        if (msg[i] != ' ') {

            cipher[i] = (char)((((a * (msg[i] - 'A')) + b) % 26) + 'A');
        } else {

            cipher[i] = msg[i];
        }
    }
    cipher[i] = '\0'; 
}
void decryptCipher(const char *cipher, int a, int b, char *msg) {
    int i, a_inv = mod_inverse(a, 26);

    if (a_inv == -1) {
        printf("Error: No multiplicative inverse for a = %d mod 26\n", a);
        return;
    }

    for (i = 0; cipher[i] != '\0'; i++) {
        if (cipher[i] != ' ') {

            msg[i] = (char)((((a_inv * ((cipher[i] - 'A') - b + 26)) % 26) + 'A'));
        } else {

            msg[i] = cipher[i];
        }
    }
    msg[i] = '\0'; 
}
int main(void) {
    char msg[100]; 
    char cipherText[100]; 
    char decryptedMsg[100]; 
    int a, b; 
    printf(" plaintext (uppercase letters only): ");
    fgets(msg, sizeof(msg), stdin);
    msg[strcspn(msg, "\n")] = 0; 
    printf("Enter value for a (must be coprime to 26): ");
    scanf("%d", &a);
    printf("B value : ");
    scanf("%d", &b);
    if (gcd(a, 26) != 1) {
        printf("Error: 'a' must be coprime to 26.\n");
        return 1;
    }
    encryptMessage(msg, a, b, cipherText);
    printf("Encrypted %s\n", cipherText);
    decryptCipher(cipherText, a, b, decryptedMsg);
    printf("Decrypted %s\n", decryptedMsg);
    return 0;
}
