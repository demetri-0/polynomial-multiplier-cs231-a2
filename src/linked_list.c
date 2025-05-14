#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	int coefficient;
	int exponent;
	struct Node *next;
} Node;

typedef struct LinkedList {
	Node* head;
	Node* tail;
	int size;
} LinkedList;

LinkedList* initList() {

	LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));

	list -> head = NULL;
	list -> tail = NULL;
	list -> size = 0;

	return list;
}

int isEmpty(LinkedList* list) {

	int emptyStatus;

	if (list -> head == NULL) {
		emptyStatus = 1;
	}
	else {
		emptyStatus = 0;
	}

	return emptyStatus;
}

void insertFirst(LinkedList* list, int coefficient, int exponent) {

	Node* node = (Node*)malloc(sizeof(Node));

	node -> coefficient = coefficient;
	node -> exponent = exponent;
	node -> next = list -> head;
	list -> head = node;

	if (list -> tail == NULL) {
		list -> tail = node;
	}

	list -> size++;
}

void insertLast(LinkedList* list, int coefficient, int exponent) {

	Node* node = (Node*)malloc(sizeof(Node));

	node -> coefficient = coefficient;
	node -> exponent = exponent;

	if (!isEmpty(list)) {
		list -> tail -> next = node;
		list -> tail = node;
		node -> next = NULL;
	}
	else {
		list -> head = node;
		list -> tail = node;
		node -> next = NULL;
	}

	list -> size++;
}

void insertAfter(LinkedList* list, int coefficient, int exponent, int coefficientToFind, int exponentToFind) {

	Node* node = (Node*)malloc(sizeof(Node));
	int inserted = 0;

	node -> coefficient = coefficient;
	node -> exponent = exponent;

	if (!isEmpty(list)) {

		Node* current = list -> head;

		while (current != NULL && (current -> coefficient != coefficientToFind || current -> exponent != exponentToFind)) {
			current = current -> next;
		}

		if (current != NULL) {

			if (current == list -> tail) {
				list -> tail = node;
			}
			node -> next = current -> next;
			current -> next = node;

			inserted = 1;
			list -> size++;
		}
	}

	if (!inserted) {
		free(node);
	}
}

void insertSorted(LinkedList* list, int coefficient, int exponent) {

	Node* node = (Node*)malloc(sizeof(Node));

	node -> coefficient = coefficient;
	node -> exponent = exponent;

	if (!isEmpty(list)) {

		Node* current = list -> head;

		if (node -> exponent > list -> head -> exponent) {
			node -> next = list -> head;
			list -> head = node;
		}
		else if (node -> exponent < list -> tail -> exponent) {
			list -> tail -> next = node;
			list -> tail = node;
			node -> next = NULL;
		}
		else {
			while (current != list -> tail && !((current -> exponent) >= (node -> exponent) && (current -> next -> exponent) <= (node -> exponent))) {
				current = current -> next;
			}

			node -> next = current -> next;
			current -> next = node;
		}
	}
	else {
		list -> head = node;
		list -> tail = node;
		node -> next = NULL;
	}

	list -> size++;
}

void deleteFirst(LinkedList* list) {

	if (!isEmpty(list)) {

		Node* toDelete = list -> head;

		if (list -> head -> next != NULL) {
			list -> head = list -> head -> next;
		}
		else {
			list -> head = NULL;
			list -> tail = NULL;
		}

		free(toDelete);

		list -> size--;
	}
}

void deleteLast(LinkedList* list) {

	if (!isEmpty(list)) {

		Node* toDelete = list -> tail;

		if (list -> head -> next != NULL) {

			Node* current = list -> head;

			while (current -> next != list -> tail) {
				current = current -> next;
			}

			list -> tail = current;
			current -> next = NULL;
		}
		else {
			list -> head = NULL;
			list -> tail = NULL;
		}

		free(toDelete);
		list -> size--;
	}
}

void replaceElement(LinkedList* list, int coefficientToReplace, int exponentToReplace, int newCoefficient, int newExponent) {

	if (!isEmpty(list)) {

		Node* current = list -> head;

		while (current != NULL) {

			if (current -> coefficient == coefficientToReplace && current -> exponent == exponentToReplace) {
				current -> coefficient = newCoefficient;
				current -> exponent = newExponent;
			}

			current = current -> next;
		}
	}
}

void deleteElement(LinkedList* list, int coefficient, int exponent) {

	if (!isEmpty(list)) {

		if ((list -> head -> coefficient == coefficient) && (list -> head -> exponent == exponent)) {
			deleteFirst(list);
		}
		else if ((list -> tail -> coefficient == coefficient) && (list -> tail -> exponent == exponent)) {
			deleteLast(list);
		}
		else {
			Node* current = list -> head;

			while (current != list -> tail && !(current -> next -> coefficient == coefficient && current -> next -> exponent == exponent)) {
				current = current -> next;
			}

			if (current != list -> tail) {
				Node* toDelete = current -> next;

				current -> next = current -> next -> next;

				free(toDelete);
				list -> size--;
			}
		}
	}
}

Node* searchElement(LinkedList* list, int coefficient, int exponent) {

	Node* result;

	Node* current = list -> head;
	while (current != NULL && !(current -> coefficient == coefficient && current -> exponent == exponent)) {
		current = current -> next;
	}

	if (current != NULL) {
		result = current;
	}
	else {
		result = NULL;
	}

	return result;
}

int containsElement(LinkedList* list, int coefficient, int exponent) {

	int result;

	if (searchElement(list, coefficient, exponent)) {
		result = 1;
	}
	else {
		result = 0;
	}

	return result;
}

char* toString(LinkedList* list);

void combineLikeTerms(LinkedList* list) {

	if (!isEmpty(list)) {
		Node* current = list -> head;

		while (current != NULL) {

			Node* comparisonCurrent = current -> next;
			while (comparisonCurrent != NULL && (comparisonCurrent -> exponent == current -> exponent)) {
				current -> coefficient += current -> next -> coefficient;
				deleteElement(list, comparisonCurrent -> coefficient, comparisonCurrent -> exponent);

				comparisonCurrent = comparisonCurrent -> next;
			}

			current = current -> next;
		}
	}
}

char* toString(LinkedList* list) {

	const int maxTermLength = 25;
	char* str = (char*)malloc(((list -> size) * maxTermLength) * sizeof(char));
	str[0] = '\0';

	Node* current = list -> head;
	char* term = (char*)malloc(maxTermLength * sizeof(char));
	sprintf(term, "(%dx^%d)", current -> coefficient, current -> exponent);
	current = current -> next;
	strcat(str, term);
	while (current != NULL) {
		sprintf(term, "+(%dx^%d)", current -> coefficient, current -> exponent);
		strcat(str, term);

		current = current -> next;
	}

	return str;
}

