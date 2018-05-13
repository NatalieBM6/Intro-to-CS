
#include <stdio.h>
#include <string.h>
#include "Matrix.h"
#include "pigLatin.h"
#define MAX 11
/************************************************************************
*function name: main.                                                   *
*The input: -.                                                          *
*The output:-.                                                          *
*The Function operation: The function operates the program.             *
*************************************************************************/
void main() {
	char input[MAX];
	int i;
	char dummy;
	do {
		printf("Main menu, choose between the options:\n");
		printf("Matrix Calculator\n");
		printf("PigLatin Translator\n");
		scanf("%s", input);
		//Changing the input into lower case.
		for (i = 0; i < MAX-1; i++) {
			input[i] = tolower(input[i]);
		}
		//Activate mission 1.
		if (strcmp(input, "calculator") == 0) {
			Matrix();
			scanf("%c", &dummy);
		}
		//Activate mission 2.
		else if (strcmp(input, "translator") == 0) {
			pigLatin();
			scanf("%c", &dummy);
		}
		else if ((strcmp(input, "quit") != 0) && (strcmp(input, "quit\n") != 0)
			&& (strcmp(input, "translator") != 0)
			&& (strcmp(input, "calculator") != 0))
			printf("This was not an option.\n");
	} while (strcmp(input, "quit")); //run until the user enters "quit".
}