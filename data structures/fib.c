// Efficient non-recursive fibonnacci algorithm
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned long long fib(unsigned long long n)
{
  // Base case
  if (n <= 1)
    return n;

  // First 2 sequences
  unsigned long long a = 0;
  unsigned long long b = 1;

  // next sequence
  unsigned long long c = 0;

  for (int i = 2; i <= n; i++)
  {
    c = a + b;
    a = b;
    b = c;
  }

  return c;
}
