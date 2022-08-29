#include <stdint.h>
#include <stdio.h>

// Generate random number
// Useful for features as stochastic ray_tracing
uint32_t f_randi(uint32_t seed)
{
  seed = (seed << 13) ^ seed;
  return ((seed * (seed * seed * 15731 + 789221) + 1376312589) & 0x7fffffff);
}

int main(int argc, char const *argv[])
{
  printf("%d\n", f_randi(100));
  return 0;
}
