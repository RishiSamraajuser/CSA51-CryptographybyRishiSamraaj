#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <math.h>
int extended_gcd(int a, int b, int *x, int *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }

    int x1, y1;
    int gcd = extended_gcd(b % a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcd;
}
int multiple_inv(int a, int b) {
    int x, y;
    int gcd = extended_gcd(a, b, &x, &y);

    if (gcd != 1) {
        printf("Inverse doesn't exist since GCD(%d, %d) != 1\n", a, b);
        return -1;
    } else {
        int res = (x % b + b) % b;
        return res;
    }
}

int main() {
    int a, b;

    printf("The inverse is of the form: a^-1 MOD b\n");
    printf("Enter Value of a: ");
    scanf("%d", &a);
    printf("Enter Value of b: ");
    scanf("%d", &b);

    int inv = multiple_inv(a, b);

    if (inv != -1) {
        printf("The multiplicative inverse of %d^-1 MOD %d is: %d\n", a, b, inv);
    }

    return 0;
}

