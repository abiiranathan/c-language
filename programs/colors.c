// Print in color
// Abiira Nathan
// Date: 2019-11-18
#include <stdio.h>
#include <stdlib.h>

// Define colors
#define BLACK "\033[0;30m"
#define BOLDBLACK "\033[1;30m"
#define RED "\033[0;31m"
#define BOLDRED "\033[1;31m"
#define GREEN "\033[0;32m"
#define BOLDGREEN "\033[1;32m"
#define YELLOW "\033[0;33m"
#define BOLDYELLOW "\033[1;33m"
#define BLUE "\033[0;34m"
#define BOLDBLUE "\033[1;34m"
#define PURPLE "\033[0;35m"
#define BOLDPURPLE "\033[1;35m"
#define CYAN "\033[0;36m"
#define BOLDCYAN "\033[1;36m"
#define WHITE "\033[0;37m"
#define BOLDWHITE "\033[1;37m"
#define BOLDWHITE "\033[1;37m"
#define RESET "\033[0m"

void print(char *color, char *string)
{
	printf("%s%s%s", color, string, RESET);
}

int main()
{
	// Print in colors
	print(BOLDBLACK, "This is black\n");
	print(BOLDRED, "This is red\n");
	print(BOLDGREEN, "This is green\n");
	print(BOLDYELLOW, "This is yellow\n");
	print(BOLDBLUE, "This is blue\n");
	print(BOLDPURPLE, "This is purple\n");
	print(BOLDCYAN, "This is cyan\n");
	print(BOLDWHITE, "This is white\n");
	return 0;
}
