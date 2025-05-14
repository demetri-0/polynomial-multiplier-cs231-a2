#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"

#define MAX_LINE_LENGTH 255

void doPolynomialMultiplication(char* polynomialsStr);

int main() {

	setvbuf(stdout, NULL, _IONBF, 0);

//	char inputFileName[256];
//
//	printf("Welcome to Polynomial Multiplication!\n");
//	printf("Please enter the name of the file: ");
//	scanf("%s", inputFileName);
//	printf("\n");

	FILE  *inputFile;
	inputFile = fopen("test.txt", "r");
	if (inputFile == NULL) {
		printf ("Input file could not be opened.\n");
		return 1;
	}
	else {
		char inputLine[MAX_LINE_LENGTH];

		while (fgets(inputLine, MAX_LINE_LENGTH, inputFile) != NULL) {
			int indexOfNewline = strcspn(inputLine, "\n");
			inputLine[indexOfNewline] = '\0';

			printf("Raw Input: %s\n", inputLine);

			doPolynomialMultiplication(inputLine);
		}
	}
	fclose(inputFile);

//	LinkedList* list = initList();
//	insertFirst(list, 3, 2);
//	insertFirst(list, 7, 3);
//	insertLast(list, 4, 4);
//	insertLast(list, 4, 4);
//	insertLast(list, 4, 4);
//	insertAfter(list, 5, 8, 3, 2);
//	replaceElement(list, 4, 4, 10, 10);
//	printf("%s\n", toString(list));
//
//	deleteFirst(list);
//	deleteLast(list);
//	printf("%s\n", toString(list));
//
//	printf("contains 3x^2? %d ||| contains 1x^1? %d\n", containsElement(list, 3, 2), containsElement(list, 1, 1));
//
//	LinkedList* sortedList = initList();
//	insertSorted(sortedList, 4, 5);
//	insertSorted(sortedList, 2, 6);
//	insertSorted(sortedList, 7, 1);
//	insertSorted(sortedList, 12, 11);
//	insertSorted(sortedList, 1, 3);
//	deleteElement(sortedList, 2, 6);
//	printf("%s\n", toString(sortedList));

	return 0;
}

void doPolynomialMultiplication(char* polynomialsStr) {

	LinkedList* polynomial1 = initList();
	LinkedList* polynomial2 = initList();

	char* poly1Str;
	char* poly2Str;

	char* asteriskToEnd = strchr(polynomialsStr, '*');
	poly2Str = asteriskToEnd + 2;

	int poly1StrLen = asteriskToEnd - polynomialsStr;
	poly1Str = (char*)malloc(poly1StrLen * sizeof(char));
	strcpy(poly1Str, polynomialsStr);
	poly1Str[poly1StrLen] = '\0';

	//printf("Polynomial 1: %s /// Polynomial 2: %s\n\n", poly1Str, poly2Str);
	int termStart, termEnd = -1, termLength;
	int coefficient, exponent;
	for (int i = 0; i < strlen(poly1Str) + 1; i++) {

		if (i == 0 || i == termEnd + 1) {
			termStart = i;
		}
		else if (poly1Str[i] == ';' || poly1Str[i] == '\0') {
			termEnd = i;

			termLength = termEnd - termStart;

			char* term = (char*)malloc((termLength + 1) * sizeof(char));

			strncpy(term, &poly1Str[termStart], termLength);
			term[termLength] = '\0';

			sscanf(term, "%d,%d", &coefficient, &exponent);
			insertSorted(polynomial1, coefficient, exponent);

			free(term);
		}
	}

	termEnd = -1;
	for (int i = 0; i < strlen(poly2Str) + 1; i++) {

		if (i == 0 || i == termEnd + 1) {
			termStart = i;
		}
		else if (poly2Str[i] == ';' || poly2Str[i] == '\0') {

			termEnd = i;

			termLength = termEnd - termStart;

			char* term = (char*)malloc((termLength + 1) * sizeof(char));

			strncpy(term, &poly2Str[termStart], termLength);
			term[termLength] = '\0';

			sscanf(term, "%d,%d", &coefficient, &exponent);
			insertSorted(polynomial2, coefficient, exponent);

			free(term);
		}
	}

	free(poly1Str);

//	printf("Poly1 before combining terms: %s\n", toString(polynomial1));
//	combineLikeTerms(polynomial1);
//	printf("Poly1 after combining terms: %s\n", toString(polynomial1));
//
//	printf("Poly2 before combining terms: %s\n", toString(polynomial2));
//	combineLikeTerms(polynomial2);
//	printf("Poly2 after combining terms: %s\n", toString(polynomial2));

	LinkedList* result = initList();
	Node* currentPoly1Node = polynomial1 -> head;
	Node* currentPoly2Node;
	int termCoefficient, termExponent;
	while (currentPoly1Node != NULL) {

		currentPoly2Node = polynomial2 -> head;
		while (currentPoly2Node != NULL) {
			termCoefficient = currentPoly1Node -> coefficient * currentPoly2Node -> coefficient;
			termExponent = currentPoly1Node -> exponent + currentPoly2Node -> exponent;

			insertSorted(result, termCoefficient, termExponent);

			currentPoly2Node = currentPoly2Node -> next;
		}

		currentPoly1Node = currentPoly1Node -> next;
	}

	combineLikeTerms(result);
	removeZeroCoefficients(result);
	//printf("Product: %s\n\n", toString(result));

	char* poly1OutputStr = toString(polynomial1);
	char* poly2OutputStr = toString(polynomial2);
	char* resultStr = toString(result);

	printf("Result: %s times %s is %s\n\n", poly1OutputStr, poly2OutputStr, resultStr);

	free(poly1OutputStr);
	free(poly2OutputStr);
	free(resultStr);

	freeList(polynomial1);
	freeList(polynomial2);
	freeList(result);
}



