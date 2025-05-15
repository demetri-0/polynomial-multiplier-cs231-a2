/*
	Author: Demetri Karras
	Assignment Number: 2
	Date of Submission: May 15th, 2025

	File Name: polynomialMultiplication.c

	Description:
	This programs reads an input from a file containing one or more lines that
	each correspond to the multiplication of two polynomials. The input is
	received and passed to a function that performs the operation. The input
	string is broken up into two polynomials strings. These strings are parsed,
	and two link lists are used to store the respective terms of each
	polynomial. These lists are iterated through, and the multiplication
	operations are performed term-by-term. Product terms are stored in a result
	linked list. The terms of the result list are cleaned up, and an output
	message is sent to the console.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedList.h"

#define MAX_LINE_LENGTH 255 // maximum size of a single line read from the input file

void doPolynomialMultiplication(char* polynomialsStr);
void polynomialStringToLinkedList(LinkedList* polynomialList, char* polynomialStr);

int main() {

	setvbuf(stdout, NULL, _IONBF, 0);

	/*
	 * Print welcome message and obtain file name.
	 */
	char inputFileName[256];

	printf("Welcome to Polynomial Multiplication!\n");
	printf("Please enter the name of the file: ");
	scanf("%s", inputFileName);
	printf("\n");

	/*
	 * The specified file is opened. Each line is read as its own input and
	 * passed into the doPolynomialMultiplication function.
	 */
	FILE  *inputFile;
	inputFile = fopen(inputFileName, "r");
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

/*
 * Function Name: doPolynomialMultiplication
 *
 * Input:
 * Param1(polynomialsStr) - a line of input structured exactly as follows:
 * <coefficient1a>,<exponent1a>;<coefficient2a>,<exponent2a>* <coefficient1b>,<exponent1b>;<coefficient2b>,<exponent2b>
 *
 * Output: None - prints a string to the console.
 *
 * Description:
 * The input string is split on * into two polynomial strings. These strings are
 * passed into a function that parses them into linked lists. These polynomial
 * linked lists are iterated through together, effectively multiplying all
 */
void doPolynomialMultiplication(char* polynomialsStr) {

	LinkedList* polynomial1 = initList();
	LinkedList* polynomial2 = initList();

	char* poly1Str;
	char* poly2Str;

	/*
	 * Creates a pointer to the asterisk in the string of polynomials. Assigns
	 * poly2Str pointer to +2 from the asteriskToEnd pointer, which skips the
	 * asterisk and space "* " and points directly to the first element of the
	 * second polynomial.
	 */
	char* asteriskToEnd = strchr(polynomialsStr, '*');
	poly2Str = asteriskToEnd + 2;

	/*
	 * The length of the first polynomial string must be the address of the
	 * asterisk minus the address of the original string of polynomials, as it
	 * points to the first element of the first polynomial. Appropriate memory
	 * is allocated to store the poly1Str, and a substring from the beginning of
	 * the polynomialsStr to the asterisk becomes its value.
	 */
	int poly1StrLen = asteriskToEnd - polynomialsStr;
	poly1Str = (char*)malloc((poly1StrLen + 1) * sizeof(char));
	strncpy(poly1Str, polynomialsStr, poly1StrLen);
	poly1Str[poly1StrLen] = '\0';

	/*
	 * The strings of polynomials are parsed and the terms are inserted into
	 * respective linked lists.
	 */
	polynomialStringToLinkedList(polynomial1, poly1Str);
	polynomialStringToLinkedList(polynomial2, poly2Str);

	free(poly1Str);

	LinkedList* result = initList(); // stores the product of the polynomials
	Node* currentPoly1Node = polynomial1->head;
	Node* currentPoly2Node;
	int termCoefficient, termExponent; // stores the product coefficient and exponent of terms

	/*
	 * Iterates through all terms of the first polynomial and multiplying it by
	 * each term in the second polynomial. This term multiplication occurs by
	 * multiplying coefficients and adding exponents. The product values are ran
	 * through a function that creates a node and inserts it in the result list
	 * in a sorted manner.
	 */
	while (currentPoly1Node != NULL) {

		currentPoly2Node = polynomial2->head;

		while (currentPoly2Node != NULL) {

			/*
			 * Main logic of term multiplication.
			 */
			termCoefficient = currentPoly1Node->coefficient * currentPoly2Node->coefficient;
			termExponent = currentPoly1Node->exponent + currentPoly2Node->exponent;

			insertSorted(result, termCoefficient, termExponent);

			currentPoly2Node = currentPoly2Node->next;
		}

		currentPoly1Node = currentPoly1Node->next;
	}

	/*
	 * Like terms (terms of the same exponent) are combined, and terms with a
	 * coefficient of 0 are removed in the result linked list to provide a
	 * simplified solution.
	 */
	combineLikeTerms(result);
	removeZeroCoefficients(result);

	/*
	 * The proper string format of the two polynomials and their product are
	 * obtained, and a string is printed to the console expressing the
	 * multiplication.
	 */
	char* poly1OutputStr = toString(polynomial1);
	char* poly2OutputStr = toString(polynomial2);
	char* resultStr = toString(result);

	printf("Result: %s times %s is %s\n\n", poly1OutputStr, poly2OutputStr, resultStr);

	/*
	 * All remaining allocated memory is freed after these lines.
	 */
	free(poly1OutputStr);
	free(poly2OutputStr);
	free(resultStr);

	freeList(polynomial1);
	freeList(polynomial2);
	freeList(result);
}

/*
 * Function Name: polynomialStringToLinkedList
 *
 * Input:
 * Param1(polynomialList) - the linked list to have terms inserted into
 * Param2(polynomialStr) - a string representing a single polynomial of the
 * following format: <coefficient1a>,<exponent1a>;<coefficient2a>,<exponent2a>
 *
 * Output: None - changes are reflected in the input linked list.
 *
 * Description:
 * Parses the string representation of a polynomial term-by-term, and stores the
 * terms in a provided linked list.
 */
void polynomialStringToLinkedList(LinkedList* polynomialList, char* polynomialStr) {

	int termStart, termEnd = -1, termLength;
	int coefficient, exponent;
	int polynomialStrLength = strlen(polynomialStr);

	for (int i = 0; i < polynomialStrLength + 1; i++) {

		/*
		 * The index of the start of a term is obtained. The start of a singular
		 * term is either at the very beginning of the polynomial, or directly
		 * following a semicolon.
		 */
		if (i == 0 || i == termEnd + 1) {
			termStart = i;
		}
		/*
		 * The index of the end of a term is obtained. The end of a singular
		 * term is either marked by a semicolon or a null terminator.
		 */
		else if (polynomialStr[i] == ';' || polynomialStr[i] == '\0') {

			termEnd = i;

			/*
			 * The length of the term is calculated and used to allocate memory
			 * for a string that will hold it.
			 */
			termLength = termEnd - termStart;
			char* term = (char*)malloc((termLength + 1) * sizeof(char));

			/*
			 * The term is copied from the polynomial string into the term
			 * string.
			 */
			strncpy(term, &polynomialStr[termStart], termLength);
			term[termLength] = '\0';

			/*
			 * The coefficient and exponent from the term string are gathered
			 * and used to insert a new node into the polynomial linked list.
			 */
			sscanf(term, "%d,%d", &coefficient, &exponent);
			insertSorted(polynomialList, coefficient, exponent);

			free(term);
			term = NULL;
		}
	}
}



