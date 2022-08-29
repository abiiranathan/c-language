// program to add two fractions and print results
// compile with gcc -o fracadder fracadder.c
// run with ./fracadder
// Author: Dr. Abiira Nathan J.K
// Date: May, 2022

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
  // initialize variables, numerators and denominators
  int num1, den1, num2, den2, num3, den3;

  // Accept both fractions from user seperated by + sign
  printf("Enter first fraction to add: ");
  scanf("%d/%d + %d/%d", &num1, &den1, &num2, &den2);

  // Add fractions
  num3 = num1 * den2 + num2 * den1;
  den3 = den1 * den2;

  // Simplify the fraction by dividing by the greatest common divisor
  int gcd = 1;
  for (int i = 2; i <= den3; i++)
  {
    if (den3 % i == 0 && num3 % i == 0)
    {
      gcd = i;
    }
  }

  // Print the result
  // if num3 > den3, print the fraction as a mixed fraction
  if (num3 > den3)
  {
    printf("%d/%d + %d/%d is %d/%d = %d %d/%d\n", num1, den1, num2, den2, num3 / gcd, den3 / gcd, num3 / den3, num3 % den3, den3 / gcd);
  }
  else if (num3 < den3)
  {
    // if num3 < den3, print the fraction as is
    printf("%d/%d + %d/%d = %d/%d\n", num1, den1, num2, den2, num3 / gcd, den3 / gcd);
  }
  else
  {
    // if num3 == den3, print the fraction as a whole number
    printf("%d/%d + %d/%d = %d\n", num1, den1, num2, den2, num3 / den3);
  }

  return 0;
}
