#include <stdio.h>

// Callmax inverse square root
// It works, don't ask me why!!
float d_sqrt(float number)
{
  int i;
  float x, y;
  x = number * 0.5;
  y = number;

  i = *(int *)&y;
  i = 0x5f3759df - (i >> 1);
  y = *(float *)&i;
  y = y * (1.5 - (x * y * y));
  y = y * (1.5 - (x * y * y));

  return number * y;
}

int main(int argc, char const *argv[])
{

  printf("%.4f\n", d_sqrt(64));
  printf("%.4f\n", d_sqrt(36));
  printf("%.4f\n", d_sqrt(12));
  printf("%.4f\n", d_sqrt(6));
  printf("%.4f\n", d_sqrt(3));
  printf("%.4f\n", d_sqrt(1.5));
}
