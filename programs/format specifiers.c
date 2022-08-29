#include <stdio.h>

int main(void) {
    // print a string
    printf("Hello World!\n");

    int a;

    int *ptr_to_a;

    ptr_to_a = &a;

    a = 5;
    printf("The value of a is %d\n", a);

    *ptr_to_a = 6;

    printf("The value of a is %d\n", a);
    printf("The value of ptr_to_a is %p\n", ptr_to_a);
    printf("It stores the value %d\n", *ptr_to_a);
    printf("The address of a is %p\n", &a);

    // Integer addition
    int d = 30;
    int e;
    int f;

    e = 500;
    f = d + e;
    printf("The sum of %d and %d is: %d\n", d, e, f);

    int k = 0;

    if (k == 0) {
        printf("K is equal to zero\n");
    } else {
        printf("K is not equal to zero\n");
    }

    // Do while loop
    int x = 0;

    do {
        printf("x=%d\n", x);
        x++;
    } while (x < 10);

    // While loop

    int z = 0;
    while (z < 100) {
        printf("Z=%d\n", z);
        z++;
    }

    // Switch statement
    int p = 0;

    switch (p) {
        case 0:
            printf("p is equal to 0\n");
            break;
        case 1:
            printf("p is equal to 1\n");
            break;
        default:
            printf("p is greater than 1\n");
    }

    /*
    Format specifiers in C
    %c	        Character
    %d	        Signed integer
    %e or %E	Scientific notation of floats
    %f	        Float values
    %g or %G	Similar as %e or %E
    %hi	        Signed integer (short)
    %hu	        Unsigned Integer (short)
    %i	        Unsigned integer
    %l or %ld or %li	Long
    %lf	        Double
    %Lf	        Long double
    %lu	        Unsigned int or unsigned long
    %lli or %lld	Long long
    %llu	    Unsigned long long
    %o	        Octal representation
    %p	        Pointer
    %s	        String
    %u	        Unsigned int
    %x or %X	Hexadecimal representation
    %n	        Prints nothing
    %%	        Prints % character

    */

    // Void pointers
    int intval = 255958283;
    void *vptr = &intval;

    // cast void ponter to int pointer
    printf("The value at vptr as an int is %d\n", *((int *)vptr));
    printf("The value at vptr as a char is %d\n", *((char *)vptr));

    // Integer array
    int arr[10];

    for (int i = 0; i < 10; i++) {
        arr[i] = i * 10 + i;
    }

    printf("arr %d", arr[9]);
}
