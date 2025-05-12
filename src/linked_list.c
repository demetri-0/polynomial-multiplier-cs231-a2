#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
	int val;
	struct Node *next;
} Node;

typedef struct LinkedList {
	Node* head;
	Node* tail;
} LinkedList;

LinkedList* initList() {

	LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));

	list -> head = NULL;
	list -> tail = NULL;

	return list;
}

void insertFirst(LinkedList* list, int num) {

	Node* node = (Node*)malloc(sizeof(Node));

	node -> val = num;
	node -> next = list -> head;
	list -> head = node;

	if (list -> tail == NULL) {
		list -> tail = node;
	}
}

void insertLast(LinkedList* list, int num) {

	Node* node = (Node*)malloc(sizeof(Node));

	node -> val = num;

	if (list -> tail != NULL) {
		list -> tail -> next = node;
		list -> tail = node;
		node -> next = NULL;
	}
	else {
		list -> head = node;
		list -> tail = node;
		node -> next = NULL;
	}
}
