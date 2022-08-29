/* print Fahrenheit-Celsius table */
#include <stdio.h>

#define LOWER 25  /* lower limit of table */
#define UPPER 300 /* upper limit */
#define STEP 1    /* step size */

int main() {
    int fahr;
    for (fahr = LOWER; fahr <= UPPER; fahr = fahr + STEP)
        printf("%3d %6.1f\n", fahr, (5.0 / 9.0) * (fahr - 32));

    return 0;
}