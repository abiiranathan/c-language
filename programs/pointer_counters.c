// Using pointers as counters

int main(int argc, char const *argv[])
{

  // Zero-ing out memory, normal way...
  int *array;

  int i;
  for (i = 0; i < 10; i++)
    array[i] = 0;

  // Using pointers instead for speed
  void *end;
  for (end = &array[10]; array != end; array++)
    *array = 0;

  return 0;
}
