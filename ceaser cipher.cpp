#include <stdio.h>
#include <string.h>
#include<conio.h>
#include <ctype.h>
int main()
{
	char plain[10], cipher[10];
	int key,i,length;
	int result;
	printf("\n plain text:");
	scanf("%s", plain);
	printf("\n key value:");
	scanf("%d", &key);
	printf("\nPLAIN TEXt: %s",plain);
	printf("\nencrypted: ");
for(i = 0, length = strlen(plain); i < length; i++)
{
	cipher[i]=plain[i] + key;
	if (isupper(plain[i]) && (cipher[i] > 'Z'))
	cipher[i] = cipher[i] - 26;
	if (islower(plain[i]) && (cipher[i] > 'z'))
	cipher[i] = cipher[i] - 26;
	printf("%c", cipher[i]);
}
printf("\n after: ");
for(i=0;i<length;i++)
{
	plain[i]=cipher[i]-key;
	if(isupper(cipher[i])&&(plain[i]<'A'))
	plain[i]=plain[i]+26;
	if(islower(cipher[i])&&(plain[i]<'a'))
	plain[i]=plain[i]+26;
	printf("%c",plain[i]);
}
getch();
}
