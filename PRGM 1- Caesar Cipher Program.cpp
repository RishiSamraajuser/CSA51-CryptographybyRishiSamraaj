#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
void encrypt_msg(char message[], int shift) {
    char ch;
    for(int i = 0; message[i] != '\0'; ++i) {
        ch = message[i];
        if(isupper(ch)) {
            ch = (ch + shift - 'A') % 26 + 'A';
        }
        else if(islower(ch)) {
            ch = (ch + shift - 'a') % 26 + 'a';
        }
        message[i] = ch;
    }
    printf("Encrypted message: %s\n", message);
}
void decrypt_msg(char message[], int shift) {
    char ch;
    for(int i = 0; message[i] != '\0'; ++i) {
        ch = message[i];
        if(isupper(ch)) {
            ch = (ch - shift - 'A' + 26) % 26 + 'A';  // +26 to handle negative values
        }
        else if(islower(ch)) {
            ch = (ch - shift - 'a' + 26) % 26 + 'a';  // +26 to handle negative values
        }
        message[i] = ch;
    }
    printf("Decrypted message: %s\n", message);
}
int main() {
    char message[100];
    int shift;
    printf("Enter a message to encrypt: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = 0;
    printf("Enter shift (key): ");
    scanf("%d", &shift);
    if(shift< 1 or shift> 8)
    {
    	printf("The entered %d for shift key is non-available for supposition!", shift);
    	printf("\nCAESER CIPHER- FAILURE!");
	}
	else
	{
		printf("A)ENCRYPTION: \n");
    	encrypt_msg(message, shift);
    	printf("B)DECRYPTION: \n");
    	decrypt_msg(message, shift);
    	printf("CAESAR CIPHER- SUCCESSFUL!");
	}
    return 0;
}
