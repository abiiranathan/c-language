#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    // Parsing a string to number(strto family of functions)
    char str[] = "2010 name";
    // atoi : bad ignores white space, starts from first digit up to first
    // no-digit char has undefined behavior for large numbers. only handles base
    // 10

    char *endPtr;
    // Passing 0 as base guesses the correct base.
    // 0x -> hexadecimal
    // 0234 -> octal
    // Defined behavior for large integers: MAX_INT
    // If it exceed MAX_INT, it sets errorno, check it.
    long int x = strtol(str, &endPtr, 10);
    printf("The number is: %ld\n", x);

    /*
    strtod()
    strtof()
    strtold()
    strtoll()
    strtoul()
    strtoull()
    */

    return 0;
}