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


/*
 * Function Name: initList
 *
 * Input: None
 *
 * Output: Returns an initialized linked list struct.
 *
 * Description: Allocates memory for a linked list struct. Head and tail
 * pointers are set to NULL, and size is set to 0.
 */
LinkedList* initList() {

	LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));

	list -> head = NULL;
	list -> tail = NULL;
	list -> size = 0;

	return list;
}

/*
 * Function Name: isEmpty
 *
 * Input:
 * Param1(list) - the linked list for which this function applies to
 *
 * Output: Returns 1 if the list has no nodes. Returns 0 if the list has at
 * least 1 node.
 *
 * Description: Expresses whether or not the provided list is empty by checking
 * the head pointer for a node.
 */
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

/*
 * Function Name: insertFirst
 *
 * Input:
 * Param1(list) - the linked list for which this function applies to
 * Param2(coefficient) - the coefficient of the term to be inserted
 * Param3(exponent) - the exponent of the term to be inserted
 *
 * Output: None - changes are reflected in the input linked list.
 *
 * Description: Creates a node with the provided components and inserts it at
 * the beginning of the given linked list. This node becomes the new head of the
 * list.
 */
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

/*
 * Function Name: insertLast
 *
 * Input:
 * Param1(list) - the linked list for which this function applies to
 * Param2(coefficient) - the coefficient of the term to be inserted
 * Param3(exponent) - the exponent of the term to be inserted
 *
 * Output: None - changes are reflected in the input linked list.
 *
 * Description: Creates a node with the provided components and inserts it at
 * the end of the given linked list. This node becomes the new tail of the list.
 */
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

/*
 * Function Name: insertAfter
 *
 * Input:
 * Param1(list) - the linked list for which this function applies to
 * Param2(coefficient) - the coefficient of the term to be inserted
 * Param3(exponent) - the exponent of the term to be inserted
 * Param4(coefficientToFind) - the coefficient of the term for which the new
 * term will be inserted after
 * Param5(exponentToFind) the exponent of the term for which the new term will
 * be inserted after
 *
 * Output: None - changes are reflected in the input linked list.
 *
 * Description: Iterates through the given list, searching for the first
 * instance of a node that contains the provided components. If found, a new
 * node is created with the other given values, and it is inserted after the
 * found node.
 */
void insertAfter(LinkedList* list, int coefficient, int exponent, int coefficientToFind, int exponentToFind) {

	if (!isEmpty(list)) {

		Node* current = list -> head;

		while (current != NULL && (current -> coefficient != coefficientToFind || current -> exponent != exponentToFind)) {
			current = current -> next;
		}

		if (current != NULL) {

			Node* node = (Node*)malloc(sizeof(Node));

			node -> coefficient = coefficient;
			node -> exponent = exponent;

			if (current == list -> tail) {
				list -> tail = node;
			}
			node -> next = current -> next;
			current -> next = node;

			list -> size++;
		}
	}
}

/*
 * Function Name: insertSorted
 *
 * Input:
 * Param1(list) - the linked list for which this function applies to
 * Param2(coefficient) - the coefficient of the term to be inserted
 * Param3(exponent) - the exponent of the term to be inserted
 *
 * Output: None - changes are reflected in the input linked list.
 *
 * Description: Creates a node with the provided components and inserts it into
 * the given linked list. The node is inserted so that all preceding nodes have
 * greater exponents, and all successive nodes have smaller exponents.
 */
void insertSorted(LinkedList* list, int coefficient, int exponent) {

    Node* node = (Node*)malloc(sizeof(Node));
    node->coefficient = coefficient;
    node->exponent = exponent;
    node->next = NULL;

    if (isEmpty(list)) {
        list->head = node;
        list->tail = node;
    }
    else if (exponent > list->head->exponent) {
        node->next = list->head;
        list->head = node;
    }
    else {
        Node* current = list->head;
        Node* prev = NULL;

        while (current != NULL && exponent <= current->exponent) {
            prev = current;
            current = current->next;
        }

        node->next = current;
        if (prev != NULL) {
            prev->next = node;
        }

        // If inserted at the end, update tail
        if (node->next == NULL) {
            list->tail = node;
        }
    }

    list->size++;


}


/*
 * Function Name: deleteFirst
 *
 * Input:
 * Param1(list) - the linked list for which this function applies to
 *
 * Output: None - changes are reflected in the input linked list.
 *
 * Description: Deletes the first node in the provided linked list.
 * Appropriately reassigns the head pointer.
 */
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

/*
 * Function Name: deleteLast
 *
 * Input:
 * Param1(list) - the linked list for which this function applies to
 *
 * Output: None - changes are reflected in the input linked list.
 *
 * Description: Deletes the last node in the provided linked list. Appropriately
 * reassigns the tail pointer.
 */
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

/*
 * Function Name: replaceElement
 *
 * Input:
 * Param1(list) - the linked list for which this function applies to
 * Param2(coefficientToReplace) - the coefficient of the term(s) to be replaced
 * Param3(exponentToReplace) - the exponent of the term(s) to be replaced
 * Param4(newCoefficient) - the coefficient of the term(s) to be inserted
 * Param5(newExponent) - the exponent of the term(s) to be inserted
 *
 * Output: None - changes are reflected in the input linked list.
 *
 * Description: Iterates through the given linked list, finding all instances of
 * nodes with the specified attributes, and replacing them with different
 * defined attributes.
 */
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

/*
 * Function Name: deleteElement
 *
 * Input:
 * Param1(list) - the linked list for which this function applies to
 * Param2(coefficient) - the coefficient of the term to be deleted
 * Param3(exponent) - the exponent of the term to be deleted
 *
 * Output: None - changes are reflected in the input linked list.
 *
 * Description: Traverses the given list and deletes the first node containing
 * the same components as provided. If not found, nothing happens.
 */
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

/*
 * Function Name: searchElement
 *
 * Input:
 * Param1(list) - the linked list for which this function applies to
 * Param2(coefficient) - the coefficient of the term to be found
 * Param3(exponent) - the exponent of the term to be found
 *
 * Output: Returns the node with the given coefficient and exponent. If no
 * matching node is found, NULL is returned.
 *
 * Description: Traverses the given list looking for a node that has the same
 * components as provided. If found, the first instance of the node is returned.
 */
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

/*
 * Function Name: containsElement
 *
 * Input:
 * Param1(list) - the linked list for which this function applies to
 * Param2(coefficient) - the coefficient of the term to be found
 * Param3(exponent) - the exponent of the term to be found
 *
 * Output: Returns 1 if a node is found containing the given coefficient and
 * exponent. If no matching node is found, 0 is returned.
 *
 * Description: Expresses whether or not a term with the provided components
 * exists in the given list. The searchElement function is called to search for
 * the node, and the return value of this function is based on its successful
 * location.
 */
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

/*
 * Function Name: combineLikeTerms
 *
 * Input:
 * Param1(list) - the linked list for which this function applies to
 *
 * Output: None - changes are reflected in the input linked list.
 *
 * Description: Combines terms in the provided linked list by iterating through
 * nodes and combining the nodes for which their exponents are equal.
 */
void combineLikeTerms(LinkedList* list) {

	if (!isEmpty(list)) {
		Node* current = list -> head;

		while (current != NULL) {

			while (current -> next != NULL && (current -> next -> exponent == current -> exponent)) {

				current -> coefficient += current -> next -> coefficient;

				Node* toDelete = current -> next;

				if (toDelete == list -> head) {
					deleteFirst(list);
				}
				else if (toDelete == list -> tail) {
					deleteLast(list);
				}
				else {
					current -> next = current -> next -> next;
					free(toDelete);
					list -> size--;
				}
			}

			current = current -> next;
		}
	}
}

/*
 * Function Name: removeZeroCoefficients
 *
 * Input:
 * Param1(list) - the linked list for which this function applies to
 *
 * Output: None - changes are reflected in the input linked list.
 *
 * Description:
 */
void removeZeroCoefficients(LinkedList* list) {

	if (!isEmpty(list)) {

		Node* current = list -> head;
		while (current != NULL) {
			while (current -> next != NULL && current -> next -> coefficient == 0) {

				Node* toDelete = current -> next;

				if (toDelete == list -> head) {
					deleteFirst(list);
				}
				else if (toDelete == list -> tail) {
					deleteLast(list);
				}
				else {
					current -> next = current -> next -> next;
					free(toDelete);
					list -> size--;
				}
			}
			current = current -> next;
		}
	}
}

/*
 * Function Name: toString
 *
 * Input:
 * Param1(list) - the linked list for which this function applies to
 *
 * Output: Returns a string representing the list.
 *
 * Description: Provides a visual representation of the contents and order of
 * the given linked list. Nodes represent terms, and are structured as
 * (<coefficient>^<exponent>). The formatted string contains every node in the
 * order they were added, separated by + signs.
 */
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

	free(term);

	return str;
}

/*
 * Function Name: freeList
 *
 * Input:
 * Param1(list) - the linked list for which this function applies to
 *
 * Output: None - memory allocation is modified.
 *
 * Description: The purpose of this function is to free the memory allocated to
 * the given linked list. All nodes are iterated through and freed, and the
 * linked list struct is freed at the end.
 */
void freeList(LinkedList* list) {

	if (!isEmpty(list)) {

		Node* current = list -> head;
		Node* temp;

		while (current != NULL) {
			temp = current -> next;
			free(current);
			current = temp;
		}
	}

	free(list);
}

