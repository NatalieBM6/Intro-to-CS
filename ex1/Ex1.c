#include <stdio.h>

void multi(); //function for case 1.
void divide(); //function for case 2.
void Fibonacci(); //function for case 3.
void minimal(); //function for case 4.
void sum(); //function for case 5.

/************************************************************************
*function name: main.
*The Input: -.
*The output: -.
*The Function operation: The function shows a menu that affords the user
*to choose between several missions.
*************************************************************************/
int main()
{
	int input;
	do {
		printf("Please select the assignment:\n");
		scanf("%d", &input);
		switch (input) {
		case 0:
			return 1;
		case 1:
			multi();
			break;
		case 2:
			divide();
			break;
		case 3:
			Fibonacci();
			break;
		case 4:
			minimal();
			break;
		case 5:
			sum();
			break;
		default:
				printf("NO SUCH ASSIGNMENT!\n");
		}
	} while (input != 0);
}
/************************************************************************
*function name: Multi                                                   *
*The input: two numbers.                                                *
*The output:The multiplication table of the two numbers.                *
*The Function operation: The function asks from the user two numbers,   *
*then, creates the multiplication table of the two numbers and prints it.*                                            *
*************************************************************************/
void multi() {
	int num1, num2, temp, i, j;
	printf("Please enter two numbers for the multiplication table:\n");
	scanf("%d %d", &num1, &num2);
	//Making sure that num1 will always be smaller than num2 or equal.
	if (num1 > num2) {
		temp = num1;
		num1 = num2;
		num2 = temp;
	}
	//Creating the multiplication table.
	for (i = num1; i <= num2; i++) {
		for (j = num1; j <= num2; j++) {
			printf("%4d", i*j);
		}
		printf("\n");
	}
}
/************************************************************************
*function name: divide                                                   *
*The Function operation: The function asks from the user two dividers,   *
*one number and a key. Then it prints, depends on the key that was given, *
*all the numbers in n that can be divided by one or both of the dividers.*
*************************************************************************/
void divide() {
	int n, div1, div2, i;
	char key;
	printf("Please enter n:\n");
	scanf("%d", &n);
	printf("Please enter two dividers:\n");
	scanf("%d %d", &div1, &div2);
	printf("Please enter the key:\n");
	scanf(" %c", &key);
	//When the user enters the key 'o' or 'O'.
	if (key == 'o' || key == 'O') {
		for (i = 1; i <= n; i++) {
			if (i % div1 == 0 || i % div2 == 0) {
				printf("%d ", i);
			}
		}
		printf("\n");
	}
	//When the user enters the key 'a' or 'A'.
	else if (key == 'a' || key == 'A') {
		for (i = 1; i <= n; i++) {
			if (i % div1 == 0 && i % div2 == 0) {
				printf("%d ", i);
			}
		}
		printf("\n");
	}
	else {
		printf("ERROR IN KEY\n");
	}
}
/************************************************************************
*function name: Fibonacci                                                *
*The Function operation: The function asks from the user one number.     *
*Then it prints a sequence of numbers according to the"Fibonacci sequence"*
* rules that say:Fn+2 = Fn+Fn+1,F1=1, F2=1.                              *
*************************************************************************/
void Fibonacci() {
	int n, i, num1 = 1, num2 = 1, temp;
	printf("Please enter n:\n");
	scanf("%d", &n);
	if (n < 1) {
		printf("INPUT ERROR\n");
	}
	else if (n == 1) {
		printf("%d\n", num1);
	}
	else if (n == 2) {
		printf("%d %d\n", num1, num2);
	}
	else {
		printf("%d ", num1);
		for (i = 0; i < n - 1; i++) {
			printf("%d ", num2);
			temp = num2;
			num2 += num1;
			num1 = temp;
		}
		printf("\n");
	}
}
/************************************************************************
*function name: minimal                                                 *
*The Function operation: The function recieves from the user a sequence  *
*of positive and or negative numbers. The sequence ends when one number  *
*from the sequence is -1. Then the function prints the two smallest      *
*and positive numbers of the sequence.                                   *
*************************************************************************/
void minimal() {
	int num, min1 = -1, min2 = -1, temp;
	printf("Please enter your sequence:\n");
	do {
		scanf("%d", &num);
		if (num > 0) {
			if (min1 == -1 || min2 == -1) {
				min1 = num;
				min2 = num + 1;
			}
			if (num < min1) {
				temp = min1;
				min1 = num;
				min2 = temp;
			}
			if (num > min1 &&num < min2) {
				min2 = num;
			}
		}
	} while (num != -1);
	printf("%d %d\n", min1, min2);
}
/************************************************************************
*function name: sum                                                      *
*The Function operation: The function recieves from the user a number    *
*from the type: unsigned long. Then it prints the sum of the number's    *
*digits.                                                                 *
*************************************************************************/
void sum() {
	unsigned long num;
	int sum = 0;
	printf("Please enter your number:\n");
	scanf("%u", &num);
	while (num != 0) {
		sum += num % 10;
		num /= 10;
	}
	printf("%d\n", sum);
}