#include <stdio.h>
#include <math.h>

unsigned long long factorial(int n) {
    unsigned long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

double log2_approx(unsigned long long num) {
    return log(num) / log(2);  // log base 2
}

int main() {
    int n = 25;

    unsigned long long total_permutations = factorial(n);

    double power_of_two = log2_approx(total_permutations);

    double adjusted_power_of_two = power_of_two - 1;  

    printf("Total possible keys (ignoring identical keys): %.0f bits\n", power_of_two);
    printf("Effectively unique keys (accounting for identical keys): %.0f bits\n", adjusted_power_of_two);

    return 0;
}

