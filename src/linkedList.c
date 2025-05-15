/*
	Author: Demetri Karras
	Assignment Number: 2
	Date of Submission: May 15th, 2025

	File Name: linkedList.c

	Description:
	With regard to the linked list, this file is responsible for
	defining the linked list and node structure, implementing insertion,
	deletion, and search functionality, and providing a way to free all
	allocated memory. There are also a two functions specific to the
	polynomial-based implementation.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// represents a single term of a polynomial
typedef struct Node {
	int coefficient;
	int exponent;
	struct Node *next;
} Node;

// contains the terms of a single polynomial as nodes
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

	list->head = NULL;
	list->tail = NULL;
	list->size = 0;

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

	if (!list || list->head == NULL) {
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
	node->coefficient = coefficient;
	node->exponent = exponent;

	/*
	 * Assigns the node's next pointer to the current head, then makes the node
	 * the new head.
	 */
	node->next = list->head;
	list->head = node;

	if (list->tail == NULL) { // If the list is empty, the node also becomes the tail.
		list->tail = node;
	}

	list->size++;
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
	node->coefficient = coefficient;
	node->exponent = exponent;

	/*
	 * Assigns the current tail's next node as the new node. The tail pointer is
	 * then assigned to the new node, who's next node is set to NULL.
	 */
	if (!isEmpty(list)) {
		list->tail->next = node;
		list->tail = node;
		node->next = NULL;
	}
	else { // If the list is empty, the new node becomes the head and tail.
		list->head = node;
		list->tail = node;
		node->next = NULL;
	}

	list->size++;
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

		Node* current = list->head;

		/*
		 * Iterates through list until the specified node is found, reflected
		 * in current.
		 */
		while (current != NULL && (current->coefficient != coefficientToFind || current->exponent != exponentToFind)) {
			current = current->next;
		}

		/*
		 * Inserts the new node after the specified node, if it exists.
		 */
		if (current != NULL) {

			Node* node = (Node*)malloc(sizeof(Node));
			node->coefficient = coefficient;
			node->exponent = exponent;

			if (current == list->tail) { // Updates tail if needed.
				list->tail = node;
			}

			/*
			 * Assigns the new node's next node as current's next node, and
			 * assigns current's next node to the new node.
			 */
			node->next = current->next;
			current->next = node;

			list->size++;
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

    if (!isEmpty(list)) {

    	/*
    	 * If the exponent of the new node is greater than or equal to the
    	 * exponent of the head term, the new node becomes the head.
    	 */
    	if (list->head->exponent <= exponent) {
    		insertFirst(list, coefficient, exponent);
    	}
    	/*
    	 * If the exponent of the new node is less than or equal to the exponent
    	 * of the tail term, the new node becomes the tail.
    	 */
    	else if (list->tail->exponent >= exponent) {
    		insertLast(list, coefficient, exponent);
    	}
    	/*
    	 * Handles case where the sorted node falls in the middle of the list.
    	 */
    	else {

    		Node* node = (Node*)malloc(sizeof(Node));
			node->coefficient = coefficient;
			node->exponent = exponent;

    		/*
    		 * Iterates through a non-empty list using prev and current as
    		 * pointers to nodes. If the new node has an exponent that is
    		 * greater than or equal to the current node, it is inserted before
    		 * it.
    		 */
			Node* prev = NULL;
    		Node* current = list->head;

    		/*
    		 * Finds new node's insertion point.
    		 */
    		while (current != NULL && (exponent < current->exponent)) {
    			prev = current;
    			current = current->next;
    		}

    		/*
    		 * Inserts new node between prev and current.
    		 */
    		prev->next = node;
    		node->next = current;

    		list->size++;
    	}
    }
    /*
     * If the list is empty, the new node becomes the head and tail.
     */
    else {

    	Node* node = (Node*)malloc(sizeof(Node));
		node->coefficient = coefficient;
		node->exponent = exponent;
		node->next = NULL;

    	list->head = node;
    	list->tail = node;

    	list->size++;
    }
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

		Node* toDelete = list->head;

		/*
		 * Handles case for multi-element list, assigning head to the current
		 * head's next node.
		 */
		if (list->head->next != NULL) {
			list->head = list->head->next;
		}
		/*
		 * Handles case for single-element list.
		 */
		else {
			list->head = NULL;
			list->tail = NULL;
		}

		free(toDelete);

		list->size--;
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

		Node* toDelete = list->tail;

		/*
		 * Handles case for a multi-element list, iterating to the node for
		 * which the next node is the tail, and assigning that node as the new
		 * tail.
		 */
		if (list->head->next != NULL) {

			Node* current = list -> head;

			while (current->next != list->tail) {
				current = current->next;
			}

			list->tail = current;
			current->next = NULL;
		}
		/*
		 * Handles case for a single-element list.
		 */
		else {
			list->head = NULL;
			list->tail = NULL;
		}

		free(toDelete);
		list->size--;
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

		Node* current = list->head;

		while (current != NULL) {

			if (current->coefficient == coefficientToReplace && current->exponent == exponentToReplace) {
				current->coefficient = newCoefficient;
				current->exponent = newExponent;
			}

			current = current->next;
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

		if ((list->head->coefficient == coefficient) && (list->head->exponent == exponent)) {
			deleteFirst(list);
		}
		else if ((list->tail->coefficient == coefficient) && (list->tail->exponent == exponent)) {
			deleteLast(list);
		}
		else {
			Node* current = list->head;

			while (current != list->tail && !(current->next->coefficient == coefficient && current->next->exponent == exponent)) {
				current = current->next;
			}

			if (current != list->tail) {
				Node* toDelete = current->next;

				current->next = current->next->next;

				free(toDelete);
				list->size--;
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

	/*
	 * Iterates through the list, stopping at the first node with the same
	 * coefficient and exponent as provided.
	 */
	Node* current = list->head;
	while (current != NULL && !(current->coefficient == coefficient && current->exponent == exponent)) {
		current = current->next;
	}

	if (current != NULL) {
		result = current;
	}
	else { // If current is NULL, the end of the list was reached, and the term wasn't found.
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

		Node* current = list->head;

		while (current != NULL) {

			while (current->next != NULL && (current->next->exponent == current->exponent)) {

				current->coefficient += current->next->coefficient;

				Node* toDelete = current->next;

				if (toDelete == list->tail) {
					current->next = current->next->next;
					list->tail = current;
					list->size--;
				}
				else {
					current->next = current->next->next;
					free(toDelete);
					list->size--;
				}
			}

			current = current->next;
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
 * Description: Deletes all terms from the provided linked list with
 * coefficients of zero.
 */
void removeZeroCoefficients(LinkedList* list) {

	if (!isEmpty(list)) {

		/*
		 * Iterates through a non-empty list using prev and current as pointers
		 * to nodes. If the coefficient of a node is 0, that node is removed.
		 * Cases for the head, tail, and middle nodes are all handled
		 * appropriately.
		 */
		Node* prev = NULL;
		Node* current = list->head;

		while (current != NULL) {

			if (current->coefficient == 0) {

				Node* toDelete = current;

				if (current == list->head) { // Handles head node.
					current = current->next;
					list->head = current;
				}
				else { // Handles all non-head nodes.
					prev->next = current->next;
					current = current->next;

					if (toDelete == list->tail) { // Reassigns tail.
						list->tail = prev;
					}
				}

				free(toDelete);
				list->size--;
			}
			else {
				prev = current;
				current = current->next;
			}
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
 * the given linked list. Nodes represent terms, and are generally structured as
 * <coefficient>^<exponent>. The formatted string contains every node in the
 * order they were added, separated by the appropriate sign.
 */
char* toString(LinkedList* list) {

	/*
	 * Initializes the string containing the representations of the linked
	 * list.
	 */
	const int maxTermLength = 25;
	char* str = (char*)malloc(((list->size) * maxTermLength) * sizeof(char));
	str[0] = '\0';

	if (!isEmpty(list)) {

		/*
		 * Initializes the string containing a term of the linked list. Term is
		 * structured as <coefficient>^<exponent>.
		 */
		Node* current = list->head;
		char* term = (char*)malloc(maxTermLength * sizeof(char));


		/*
		 * Iterates through every node in the list, assigning the term pointer
		 * to an appropriate string representation of the node.
		 */
		while (current != NULL) {

			/*
			 * If current is the head, leading operators are removed.
			 */
			if (current == list->head) {
				if (current->exponent == 0) {
					sprintf(term, "%d", current->coefficient);
				}
				else if (current->exponent == 1) {
					sprintf(term, "%dx", current->coefficient);
				}
				else {
					sprintf(term, "%dx^%d", current->coefficient, current->exponent);
				}
			}
			/*
			 * If the coefficient of current is positive, + is used to separate
			 * terms.
			 */
			else if (current->coefficient > 0){
				if (current->exponent == 0) {
					sprintf(term, " + %d", current->coefficient);
				}
				else if (current->exponent == 1) {
					sprintf(term, " + %dx", current->coefficient);
				}
				else {
					sprintf(term, " + %dx^%d", current->coefficient, current->exponent);
				}
			}
			/*
			 * If the coefficient of current is negative, - is used to separate
			 * terms.
			 */
			else {
				if (current->exponent == 0) {
					sprintf(term, " - %d", (current->coefficient) * -1);
				}
				else if (current->exponent == 1) {
					sprintf(term, " - %dx", (current->coefficient) * -1);
				}
				else {
					sprintf(term, " - %dx^%d", (current->coefficient) * -1, current->exponent);
				}
			}

			current = current->next;
			strcat(str, term);
		}

		free(term);
	}
	else { // If the list is empty, it represents 0.
		strcat(str, "0");
	}

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

	/*
	 * Iterates through each node of a non-empty list, effectively freeing them
	 * all.
	 */
	if (!isEmpty(list)) {

		Node* current = list->head;
		Node* temp;

		while (current != NULL) {
			temp = current->next;
			free(current);
			current = temp;
		}
	}

	list->head = NULL;
	list->tail = NULL;
	list->size = 0;

	free(list);
}

