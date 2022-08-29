// Program: sphere.c
#include <stdio.h>
#include <math.h>
#define PI 3.14159265358979323846

int main(void)
{
  float radius, volume;

  printf("Enter the sphere radius(cm): ");
  int ret = scanf("%f", &radius);
  if (ret != 1)
  {
    printf("Invalid input. Enter a valid radius!\n");
    return 1;
  }

  volume = (4.0f / 3.0f) * PI * radius * radius * radius;

  printf("Sphere volume: %.2f cm3\n", volume);
  return 0;
}
