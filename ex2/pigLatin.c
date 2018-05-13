
#include <string.h>
#include <stdio.h>
#include "pigLatin.h"
#define SIZE 50
#define WORD 15
/************************************************************************
*function name: pigLatin.                                               *
*The input: -.                                                          *
*The output:-.                                                          *
*The Function operation: The function translates a sentence to the pig  *
*latin language.                                                        *
*************************************************************************/
void pigLatin() {
	char sentence[SIZE];
	char word[WORD];
	char partOne[WORD];
	char partTwo[WORD];
	char yesOrNo, dummy;
	const char seperator[4] = " \n\t";
	char *token;
	char way[4] = "way";
	char ay[3] = "ay";
	int i, j, k, length, check = 0;
	do {
		printf("Please enter a sentence in English:\n");
		scanf("%c", &dummy);
		gets(sentence);
		token = strtok(sentence, seperator);
		while (token != NULL) {
			check = 0;
			//Copying the token to the string "word".
			strcpy(word, token);
			length = strlen(word);
			//Changing the word into lower case.
			for (i = 0; i < WORD - 1; i++) {
				word[i] = tolower(word[i]);
			}
			//if the word starts with a/e/i/o/u.
			if (word[0] == 'a' || word[0] == 'e' || word[0] == 'i' 
				|| word[0] == 'o' || word[0] == 'u') {
				strcat(word, way);
				printf("%s", word);
				printf(" ");
				++check;
			}
			else if (word[0] != 'a' || word[0] != 'e' || word[0] != 'i'
				|| word[0] != 'o' || word[0] != 'u') {
				for (i = 0; i < length; i++) {
					//if the word has an a/e/i/o/u in it.
					if (word[i] == 'a' || word[i] == 'e' || word[i] == 'i'
						|| word[i] == 'o' || word[i] == 'u' || (word[i] == 'y'&&i != 0)) {
						for (j = i; j < length; j++) {
							printf("%c", word[j]);
						}
						for (k = 0; k < i; k++) {
							printf("%c", word[k]);
						}
						printf("ay ");
						i = length;
						++check;
					}
				}
			}
			//If the word doesn't have a/e/i/o/u in it.
			if (check == 0) {
				strcat(word, ay);
				printf("%s", word);
				printf(" ");
			}
			token = strtok(NULL, seperator);
		}
		printf("\n");
		printf("Do you want to translate another sentence?(y/n)\n");
		scanf(" %c", &yesOrNo);
	} while (yesOrNo != 'n');
}