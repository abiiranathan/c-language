// Polynomial evaluation with Horner's method

#include <stdio.h>
#include <stdlib.h>

// poly is an array of coefficients
// n is the degree of the polynomial + 1
// x is the value at which to evaluate the polynomial
//
// Returns value of poly[0]x(n-1) + poly[1]x(n-2) + .. + poly[n-1]
int horner(int poly[], int n, int x) {
    int result = poly[0];  // Initialize result

    // Evaluate value of polynomial using Horner's method
    for (int i = 1; i < n; i++) {
        result = result * x + poly[i];
    }

    return result;
}

// returns the power of x to the yth power
float power(float x, int y) {
    if (y == 0) return 1;

    float temp;
    temp = power(x, y / 2);
    if (y % 2 == 0)
        return temp * temp;
    else {
        if (y > 0)
            return x * temp * temp;
        else
            return (temp * temp) / x;
    }
}

int main() {
    int n, x, *c;

    printf("Enter the degree of the polynomial: ");
    scanf("%d", &n);
    c = (int *)malloc((n + 1) * sizeof(int));

    printf("Enter the coefficients of the polynomial: ");
    for (int i = 0; i <= n; i++) scanf("%d", &c[i]);

    printf("Enter the value of x: ");
    scanf("%d", &x);

    printf("\nThe value of the polynomial is %d\n", horner(c, n + 1, x));
    free(c);
    return 0;
}
