
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include "GADT.h"
#define LEN 16

//declarations.
void StringMenu();
void PointMenu();
void InputString(ELM input);
void InputPoint(ELM input);
ELM CreateString();
ELM CreatePoint();
void CopyString(ELM elm1, ELM elm2);
void CopyPoint(ELM elm1, ELM elm2);
int StringCompare(ELM elm1, ELM elm2);
int PointCompare(ELM elm1, ELM elm2);
ELM AddStringToString(ELM elm1, ELM elm2);
ELM AddPointToPoint(ELM elm1, ELM elm2);
void PrintString(ELM elm);
void PrintPoint(ELM elm);
void FreeString(ELM elm);
void FreePoint(ELM elm);
void StringSep(char* input, char** elm1, char** elm2);

typedef struct Point_t {
	int x;
	int y;
} Point_t;
/************************************************************************
*function name:main.
*The Input: -.
*The Output: 0.
*The Function operation: The function recieves from the user a point or a
*string and then sends the string/point with their specific functions to
*a generic file.
*************************************************************************/
int main() {
	int x = 0;
	char dummy = '0';
	scanf("%d", &x);
	dummy = getc(stdin);
	//Main menu.
	switch (x) {
	case 0:
		StringMenu();
		break;
	case 1:
		PointMenu();
		break;
	default:
		break;
	}
	return 0;
}

  /****************************************************************************
  * function name: PointMenu												  *
  * the input: none															  *
  * the output: none														  *
  * the function operation: creates a list for points with initial point, then*
  * asks for a operation for the list.										  *
  * a - add element to the list												  *
  * d - remove element														  *
  * e - destroy the list													  *
  * l - print number of elements in the list								  *
  * p - print the elements of the list									   	  *
  * s - check if element is in the list										  *
  * t - add element to existing element										  *
  ****************************************************************************/
void PointMenu() {
	HEAD list = NULL;
	Point_t point, addPoint;
	char pX = '0', dummy = '0';
	//Recieving a point from the user.
	InputPoint(&point);
	dummy = getc(stdin);
	//Creating the head of a list of points.
	list = SLCreate(&point, CreatePoint, CopyPoint, PointCompare,
		FreePoint, PrintPoint, AddPointToPoint);
	do {
		scanf("%c", &pX);
		dummy = getc(stdin);
		//Main menu of the list of points.
		switch (pX) {
		//Add a point to the list.
		case 'a':
			InputPoint(&point);
			dummy = getc(stdin);
			SLAddListElement(&list, &point);
			break;
		//Removing a point from the list.
		case 'd':
			InputPoint(&point);
			dummy = getc(stdin);
			SLRemoveElement(&list, &point);
			break;
		case 'e':
			SLDestroy(&list);
			break;
		//Printing the length of the list.
		case 'l':
			SLPrintSize(list);
			break;
		//Printing the list.
		case 'p':
			SLPrintList(list);
			break;
		//Find a point on the list.
		case 's':
			InputPoint(&point);
			dummy = getc(stdin);
			//If point doesn't exist in the list.
			if (SLFindElement(list, &point) == 0)
				printf("FALSE\n");
			else
				//If point exists in the list.
				printf("TRUE\n");
			break;
		//Adding a point to a point on the list.
		case 't':
			scanf("(%d,%d) (%d,%d)", &point.x, &point.y,
				&addPoint.x, &addPoint.y);
			dummy = getc(stdin);
			SLAddToElement(&list, &point, &addPoint);
			break;
		default:
			break;
		} 
	} while ((list != NULL) && (pX != 'e')); //Run until user wants to exit or the list is empty.
	return;
} //end of function

  /****************************************************************************
  * function name: StringMenu												  *
  * the input: none															  *
  * the output: none														  *
  * the function operation: creates a list for strings with initial string,	  *
  * then asks for a operation for the list.									  *
  * a - add element to the list												  *
  * d - remove element														  *
  * e - destroy the list													  *
  * l - print number of elements in the list							      *
  * p - print the elements of the list										  *
  * s - check if element is in the list										  *
  * t - add element to existing element										  *
  ****************************************************************************/
void StringMenu() {
	char sX = '0', dummy = '0', inputStr[LEN] = { 0 };
	char *token1 = NULL, *token2 = NULL;
	HEAD list = NULL;
	//Recieving a string from the user.
	InputString(inputStr);
	//Creating a head to a list of strings.
	list = SLCreate(inputStr, CreateString, CopyString, StringCompare,
		FreeString, PrintString, AddStringToString);
	do {
		scanf("%c", &sX);
		dummy = getc(stdin);
		//Main menu for the recieved string.
		switch (sX) {
		//Add a string to the list.
		case 'a':
			InputString(inputStr);
			SLAddListElement(&list, &inputStr);
			break;
		//Removing a string from the list.
		case 'd':
			InputString(inputStr);
			SLRemoveElement(&list, &inputStr);
			break;
		case 'e':
			SLDestroy(&list);
			break;
		//Printing the length of the list.
		case 'l':
			SLPrintSize(list);
			break;
		//Printing the list.
		case 'p':
			SLPrintList(list);
			break;
		//Find string on the list.
		case 's':
			InputString(inputStr);
			//If string not on the list.
			if (SLFindElement(list, &inputStr) == 0)
				printf("FALSE\n");
			else
				//If string exists in the list.
				printf("TRUE\n");
			break;
		//Adding string to another string.
		case 't':
			InputString(inputStr);
			StringSep(inputStr, &token1, &token2);
			SLAddToElement(&list, token1, token2);
			break;
		default:
			break;
		}
	} while ((list != NULL) && (sX != 'e')); //Run until user wants to exit or the list is empty.
	return;
}

  /****************************************************************************
  * function name: InputString												  *
  * the input: ELM input													  *
  * the output: none														  *
  * the function operation: fgets for the new string. removes \0			  *
  ****************************************************************************/
void InputString(ELM input) {
	char *strPtr = NULL;
	strPtr = (char*)input;
	//Recieving a string from the user.
	fgets(strPtr, LEN, stdin);
	strPtr[strlen(strPtr) - 1] = '\0';
	return;
}

  /****************************************************************************
  * function name: InputPoint												*
  * the input: ELM input														*
  * the output: none															*
  * the function operation: scans new point in (x,y) format					*
  ****************************************************************************/
void InputPoint(ELM input) {
	Point_t *temp;
	temp = (Point_t*)input;
	//Recieving a point from the user.
	scanf("(%d,%d)", &temp->x, &temp->y);
	return;
}

/************************************************************************
*function name:CreateString.
*The Input: -.
*The Output: the allocated memory for a string.
*The Function operation: The function allocates memory for a string.
*************************************************************************/
ELM CreateString() {
	char *strSize = NULL;
	//Allocating memory.
	strSize = (char*)calloc(LEN, sizeof(char));
	//Making sure the allocation succeeded.
	if (strSize != NULL)
		return strSize;
	else
		return NULL;
}

/************************************************************************
*function name:CreatePoint.
*The Input: -.
*The Output: the allocated memory for a point.
*The Function operation: The function allocates memory for a point.
*************************************************************************/
ELM CreatePoint() {
	Point_t *pSize;
	//Allocating memory.
	pSize = (Point_t*)calloc(1, sizeof(Point_t));
	if (pSize == NULL)
		return NULL;
	return pSize;
}

  /************************************************************************
  *function name:CopyString.
  *The Input: two strings.
  *The Output: -.
  *The Function operation: The function copies a given string to the other
  *given string.
  *************************************************************************/
void CopyString(ELM elm1, ELM elm2) {
	char *ptrDest = NULL, *ptrSrc = NULL;
	//Casting the pointers.
	ptrSrc = (char*)elm1;
	ptrDest = (char*)elm2;
	//Copying the recieved value into it's place.
	strcpy(ptrDest, ptrSrc);
	return;
}

/************************************************************************
*function name:CopyPoint.
*The Input: two points.
*The Output: -.
*The Function operation: The function copies a given point to the other
*given point.
*************************************************************************/
void CopyPoint(ELM elm1, ELM elm2) {
	Point_t *pointSource;
	Point_t *pointToCopy;
	//Casting the pointers.
	pointSource = (Point_t*)elm1;
	pointToCopy = (Point_t*)elm2;
	//Copying the point to another point.
	pointToCopy->x = pointSource->x;
	pointToCopy->y = pointSource->y;
	return;
}

  /************************************************************************
  *function name: StringCompare.
  *The Input: two strings.
  *The Output: The relation between the two strings.
  *The Function operation: The function compares two strings and returns whether
  *they are equal or not.
  *************************************************************************/
int StringCompare(ELM elm1, ELM elm2) {
	int comp = 0;
	char *temp1 = NULL, *temp2 = NULL;
	//Casting the pointers.
	temp1 = (char*)elm1;
	temp2 = (char*)elm2;
	//Comparing the two strings.
	comp = strcmp(temp1, temp2);
	return comp;
}

/************************************************************************
*function name: PointCompare.
*The Input: two points.
*The Output: The relation between the two points.
*The Function operation: The function compares two points and returns whether
*they are equal or not.
*************************************************************************/
int PointCompare(ELM elm1, ELM elm2) {
	int position1 = 0, position2 = 0, distance = 0;
	Point_t *firstPoint;
	Point_t *secondPoint;
	//Casting the pointers.
	firstPoint = (Point_t*)elm1;
	secondPoint = (Point_t*)elm2;
	//The sum of the x and y of a point.
	position1 = abs(firstPoint->x) + abs(firstPoint->y);
	position2 = abs(secondPoint->x) + abs(secondPoint->y);
	distance = position1 - position2;
	return distance;
}

  /************************************************************************
  *function name:PrintString.
  *The Input: a pointer to the head of the list.
  *The Output: -.
  *The Function operation: The function prints all the strings on the list.
  *************************************************************************/
void PrintString(ELM elm) {
	printf("%s\n", elm);
	return;
}

/************************************************************************
*function name:PrintPoint.
*The Input: a pointer to the head of the list.
*The Output: -.
*The Function operation: The function prints all the points on the list.
*************************************************************************/
void PrintPoint(ELM elm) {
	Point_t *temp;
	//Casting the pointer.
	temp = (Point_t*)elm;
	//When both x and y are positive.
	if ((temp->x > -1) && (temp->y > -1)) {
		printf("%.03d|%.03d\n", temp->x, temp->y);
	}
	//When x is positive and y is negative.
	else if ((temp->x > -1) && (temp->y < 0)) {
		printf("%.03d|%.02d\n", temp->x, temp->y);
	}
	//When y is positive and x is negative.
	else if ((temp->x < 0) && (temp->y > -1)) {
		printf("%.02d|%.03d\n", temp->x, temp->y);
	}
	//When both x and y are negative.
	else if ((temp->x < 0) && (temp->y < 0)) {
		printf("%.02d|%.02d\n", temp->x, temp->y);
	}
	return;
}

  /************************************************************************
  *function name:AddStringToString.
  *The Input: two strings.
  *The Output: The new string created by the two strings.
  *The Function operation: The function creates a new string from two strings.
  *************************************************************************/
ELM AddStringToString(ELM elm1, ELM elm2) {
	char *temp1 = NULL, *temp2 = NULL, *newStr = NULL;
	//Casting the pointers.
	temp1 = (char*)elm1;
	temp2 = (char*)elm2;
	//Making sure the length of the new string is not bigger than LEN.
	if (LEN >= (strlen(temp1) + strlen(temp2))) {
		newStr = CreateString();
		CopyString(temp1, newStr);
		//adding the two strings.
		strcat(newStr, temp2);
	}
	else
		return NULL;
	return newStr;
}

/************************************************************************
*function name:AddPointToPoint.
*The Input: two points.
*The Output: The new point created by the two points.
*The Function operation: The function creates a new [point from two points.
*************************************************************************/
ELM AddPointToPoint(ELM elm1, ELM elm2) {
	Point_t *firstPoint;
	Point_t *secondPoint;
	Point_t *newPoint;
	//Casting the pointers.
	firstPoint = (Point_t*)elm1;
	secondPoint = (Point_t*)elm2;
	newPoint = CreatePoint();
	//Adding one point values to another.
	newPoint->y = firstPoint->y + secondPoint->y;
	newPoint->x = firstPoint->x + secondPoint->x;
	return newPoint;
}

  /************************************************************************
  *function name:FreeString.
  *The Input: a pointer to the head of the list.
  *The Output: -.
  *The Function operation: The function frees the allocated memory of the strings.
  *************************************************************************/
void FreeString(ELM elm) {
	char **temp = NULL;
	temp = (char**)elm;
	free(*temp);
	return;
}

/************************************************************************
*function name:FreePoint.
*The Input: a pointer to the head of the list.
*The Output: -.
*The Function operation: The function frees the allocated memory of the points.
*************************************************************************/
void FreePoint(ELM elm) {
	Point_t **temp;
	//Casting the pointer.
	temp = (Point_t**)elm;
	//free to the point.
	free(*temp);
	return;
}

  /****************************************************************************
  * function name: StringSep												  *
  * the input: char* input, char **elm1, char **elm2						  *
  * the output: none														  *
  * the function operation: recieves two strings. Then seperates the two      *
  * different strings														  *
  ****************************************************************************/
void StringSep(char* input, char **elm1, char **elm2) {
	char seperator[2] = " ";
	*elm1 = strtok(input, seperator);
	*elm2 = strtok(NULL, seperator);
	return;
}